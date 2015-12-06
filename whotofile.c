/* whotofile.c
 *  purpose: show how to redirect outputfor another program
 *     idea: fork, then in the child, redirect output, then exec
 */

#include    <stdio.h>
#include    <unistd.h>
#include    <stdlib.h>

main() {
    int     pid;
    int     fd;
    
    printf("About to run who into a file\n");
    
    /* create a new process or quit */
    if( (pid = fork()) == -1 ) {
        perror("fork");
        exit(1);
    }
    
    /* child does the work */
    if ( pid == 0 ) {
        close(1);                           /* close, */
        fd = creat( "userlist", 0644 );     /* the open */
        execlp( "who", "who", NULL );       /* and run */
        
        perror("execlp");
        exit(1);
    }
    
    /* parent waits then reports */
    if ( pid != 0 ) {
        wait(NULL);
        printf( "Done Running who.  results in userlist\n");
    }
}
