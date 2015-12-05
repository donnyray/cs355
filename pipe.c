
/* 
 * File:   pipe.c
 *  travismoretz
 *  code from book
 * Created on November 14, 2015, 1:38 PM
 * 
 */

#include	<stdio.h>
#include        <stdlib.h>
#include        <unistd.h>
#include        <string.h>


#define	oops(m,x)	{ perror(m); exit(x); }

int do_pipe(char* cmd1, char* cmd2) {
	int	thepipe[2],			/* two file descriptors	*/
		newfd,				/* useful for pipes	*/
		pid;				/* and the pid		*/

	if ( cmd1 == NULL || cmd2 == NULL ){
		fprintf(stderr, "usage: pipe cmd1 cmd2\n");
		exit(1);
	}
	if ( pipe( thepipe ) == -1 )		/* get a pipe		*/
		oops("Cannot get a pipe", 1);

	/* ------------------------------------------------------------ */
	/*	now we have a pipe, now let's get two processes		*/

	if ( (pid = fork()) == -1 )			/* get a proc	*/
		oops("Cannot fork", 2);

	/* ------------------------------------------------------------ */
	/* 	Right Here, there are two processes			*/
	/*             parent will read from pipe			*/

	if ( pid > 0 ){			/* parent will exec cmd2	*/
		close(thepipe[1]);	/* parent doesn't write to pipe	*/

		if ( dup2(thepipe[0], 0) == -1 )
			oops("could not redirect stdin",3);

		close(thepipe[0]);	/* stdin is duped, close pipe	*/
		execlp( cmd2, cmd2, NULL);
		oops(cmd2, 4);
	}

	/*	 child execs cmd1 and writes into pipe			*/

	close(thepipe[0]);		/* child doesn't read from pipe	*/

	if ( dup2(thepipe[1], 1) == -1 )
		oops("could not redirect stdout", 4);

	close(thepipe[1]);		/* stdout is duped, close pipe	*/
	execlp( cmd1, cmd1, NULL);
	oops(cmd1, 5);
}

/**
 * return a boolean if the shell command contains a pipe
 * @param s command arg
 * @return 0 for fails 1 for ture
 */
int is_pipe_command(char *s) {
    return (strcmp(s, "|") == 0);
}

