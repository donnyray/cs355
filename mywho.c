
/* 
 * File:   mywho.c
 * Author: travismoretz
 *
 * Created on September 23, 2015, 9:55 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <utmpx.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define SHOWHOST /* include remotre machine on output */


void show_info ( struct utmpx *);
/*void showtime (struct timeval);
 *
 * 
 */
int mywho(int argc, char** argv) {
    
    struct utmpx current_record; /* read info into here */
    int utmpfd;
    int reclen = sizeof(current_record);
    
    if ((utmpfd = open(UTMPX_FILE, O_RDONLY)) == -1) {
        perror( UTMPX_FILE );
        exit(1);
    }
    
    while (read(utmpfd, &current_record, reclen) == reclen) {
        show_info(&current_record);
    }
    close(utmpfd);
    return 3; /* went okay */

}

void show_info( struct utmpx *utbufp) {

    char *puser= malloc(sizeof utbufp->ut_user);
    char *pline= malloc(sizeof utbufp->ut_line);
    
    puser = utbufp->ut_user;
    pline = utbufp->ut_line;
    
    printf("%-8.8s", puser);  /* the logname */
    printf(" ");
    printf("%-8.8s", pline);  /* tty         */
    printf(" ");
 //   printf("%-10ld", getutxid(utbufp)->ut_tv);     /* log in time */
    printf(" ");
  
#ifdef  SHOWHOST
    printf("(%s)", getutxid(utbufp)->ut_host);
#endif
    printf("\n");
    

}