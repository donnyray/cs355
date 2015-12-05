/* 
 * File:   marquee.c
 * Author: travismoretz
 *
 * Created on November 27, 2015, 10:15 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>

#define ERROR_MSG    "Error opening "

int setX(int, int, int);    /* set cursor x position */
int getTemp();              /* get temp value for moving cursor */
void setTemp(int);          /* set temp value for moving cursor */
void fileError(char *, char *);

void myalarm(int);          /* alarm signal handler */
int set_ticker(int);        /* timer for speed specification */


int temp = 0;               /* temp value for moving cursor */


/*
 * 
 */
int marquee(int argc, char** argv) {

    int fd;
    int *fd_reset;
    char ch = ' ';
    char *buff = malloc(sizeof(char));
    size_t c = 1;
    
    /*
     * set up window
     */
    WINDOW *window;
    window = initscr();
    clear();
    int maxCol = getmaxx(window);

    /*
     *  get file, length, row, col, speed from args     
     */
    char *file = argv[1];
    int length = atoi(argv[2]);
    int row =  atoi(argv[3]);
    int col = atoi(argv[4]);
    int speed = atoi(argv[5]);
    
    /*
     * test for valid inputs 
     */
    if(speed < 1 || speed > 99 || col > maxCol || col < 0 || length < 1) {
        printf("Usage:\n");
        printf("marquee [fileName] [row] [col] [speed (1-99)]");
    }
    
    /*
     * handle the alarm signal for the speed timer  
     */
    signal(SIGALRM, myalarm);
    

    /*
     * test opening the file, display error if issue
     * then close
     */
    if((fd = open(file, O_RDONLY)) == -1) {
        fileError(file, buff);
    } else { 
    
    refresh();
 //   signal(SIGALRM, myalarm);
    /*
     * set timer for printing speed
     */
    if (set_ticker(speed) == -1) {
        perror("set ticker");
    } else {
        /*
         * Loop until CNTL C, start curser at specified location and move
         * as specified 
         */
            while (1) {
                while (c != 0) {
                    c = read(fd, buff, sizeof (char));
                    if (c == 0)
                        break;
                    ch = *buff;
                    move(row, setX(col, length, maxCol));
                    addch(ch);
                    refresh();
                    pause();
                }
                /*
                 * restart file.
                 */
                close(fd);
                if((fd = open(file, O_RDONLY)) == -1) {
                    fileError(file, buff);
                }
                c = 1;
            }
        }
    }
    /*
     * clean up, reset window, exit
     */
    free(buff);
    endwin();
    return (0);
}

/**
 * calc new column to print it, loop to beginning of line
 *  if reached end of screen
 * @param col
 * @param length
 * @param temp
 * @return 
 */
int setX(int c, int l, int mCol) {
    setTemp(getTemp() + 1);
    if ( getTemp() <= l){
        
        if( mCol <= (getTemp() + c)) {
           return( (getTemp() + c) - ((mCol) ) ); 
        }
        
        return (getTemp() + c);
        
    } else {
        setTemp(0);
        return c;
    }          
}

/**
 * get the temp value
 * @return 
 */
int getTemp() {
    return temp;
}

/**
 * set the temp value
 * @param t
 */
void setTemp(int t) {
    temp = t;
}

/**
 * alarm signal handler.
 * no change.
 * @param signum
 */
void myalarm(int signum) {
    /* continue */
}

/**
 * sets timer for speed
 * @param n_msecs
 * @return 
 */
int set_ticker( int n_msecs )
{
        struct itimerval new_timeset;
        long    n_sec, n_usecs;

        n_sec = n_msecs / 1000 ;
        n_usecs = ( n_msecs % 1000 ) * 1000L ;

        new_timeset.it_interval.tv_sec  = n_sec;        /* set reload  */
        new_timeset.it_interval.tv_usec = n_usecs;      /* new ticker value */
        new_timeset.it_value.tv_sec     = n_sec  ;      /* store this   */
        new_timeset.it_value.tv_usec    = n_usecs ;     /* and this     */

	return setitimer(ITIMER_REAL, &new_timeset, NULL);
}

/**
 * if error opening file print error, clean-up, and exit
 * @param file
 * @param buff
 */
void fileError(char *file, char *buff) {
        char *msg = malloc((strlen(ERROR_MSG) + 1) + strlen(file));
        strcpy(msg, ERROR_MSG);
        strcat(msg, file);
        move(0,0);
        int r = addstr(msg);
        refresh();
        free(msg);
        sleep(3);
        free(buff);
        endwin();
        exit(1);   
}
