/* 
 * File:   main.c
 * Author: travismoretz
 *
 * Created on November 12, 2015, 3:36 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <math.h>
/*
 * 
 */
void save_restore_tty(int);
void set_new_tty();
void cntl_c(int);

static int largest_prime = 0;

int prime() {
    
    int i;
    save_restore_tty(0);            /* save tty settings */
    set_new_tty();                  /* set the tty to 1 c at time */
    signal(SIGINT, cntl_c );        /* handles CNTRL C */
    
 /* calculate prime numbers: store largest found prime in largest_prime
  * test all numbers from 2 to squareRoot of current number being checked
  * if none of the tested numbers are divisible evenly then its prime */   
    while(1) { 
        int k = floor(sqrt(i));         
        int temp = 0;
        for(int j = 2 ; j <= k ; j++) {
            
            if ((i % j) == 0) {
                temp++;             /* not prime */
            }
            
        }
        /* is prime: update the newly found largest prime */
        if (temp == 0) {
                largest_prime = i;
            }
        i++;
    }
    
    save_restore_tty(1);            /* restore tty settings */
    return (3);
}

/* handle when user tries interrupt the process */
void cntl_c(int signum) {
    
    int ch;
    
    /* get user input and put back on screen */
    printf("%d\tQuit [y/n]? ",largest_prime);
    ch = getchar();
    putchar(ch);
    putchar('\n');
    
    
    /* Restore tty settings if interupted and exit */
    if (ch == 'y' || ch == 'Y') {
        save_restore_tty(1);
        exit(3);
    }

}

/* 0 = save system default tty settings or if not 0, restore to saved */
void save_restore_tty(int how) {
    static struct   termios original_mode;
    /* save current system default tty settings */
    if(how == 0) {
        tcgetattr(0, &original_mode);
    }
    /* restore the defaults that were saved in orginal_mode */
    else {
        tcsetattr(0, TCSANOW, &original_mode);
    }   
}

/* set system tty to desired settings: single char, and no echo. */
void set_new_tty() {
    struct termios newttystate;
    
    tcgetattr(0, &newttystate);
    newttystate.c_lflag     &= ~ICANON;     /* switch cononical mode */
    newttystate.c_lflag     &= ~ECHO;       /* switch echo mode */
    newttystate.c_cc[VMIN]        = 1;
    tcsetattr(0, TCSANOW, &newttystate);
    
}
