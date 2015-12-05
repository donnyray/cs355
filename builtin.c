/* builtin.c
 * contains the switch and the functions for builtin commands
 */

#include	<stdio.h>
#include        <stdlib.h>
#include	<string.h>
#include	<ctype.h>
#include	"smsh.h"
#include	"varlib.h"

int assign(char *);
int okname(char *);
int VLdelete(char *);
int get_value(char*);
int get_var(char*);
int myfind(int, char**);

int builtin_command(char **args, int *resultp)
/*
 * purpose: run a builtin command 
 * returns: 1 if args[0] is builtin, 0 if not
 * details: test args[0] against all known builtins.  Call functions
 */
{

	int rv = 0;

	if ( strcmp(args[0],"set") == 0 ){	     /* 'set' command? */
		VLlist();
		*resultp = 0;
		rv = 1;
	}
        else if (strcmp(args[0], "myfind") == 0) {
            int count;
            while(args++) {
                count += 1;
            }
            myfind(count, args);
        }
	else if ( strchr(args[0], '=') != NULL ){   /* assignment cmd */
		*resultp = assign(args[0]);
		if ( *resultp != -1 )		    /* x-y=123 not ok */
			rv = 1;
	}
        else if ( strnstr(args[0],REFVAR, 1) != NULL ) {
            rv = get_var(args[0]);
             
        }
	else if ( strcmp(args[0], "export") == 0 ){
		if ( args[1] != NULL && okname(args[1]) ) {
			*resultp = VLexport(args[1]);
                }
		else
			*resultp = 1;
		rv = 1;
	}
        else if(strcmp(args[0], "unset") == 0) {
            rv = VLdelete(args[1]);
        }
        else if(strcmp(args[0], "read") == 0) {
            if ( args[1] != NULL ) {
                if( okname(args[1]) ) {
                    rv = get_value(args[1]);
                }
            }
        }
        else if ( strcmp(args[0], "exit") == 0 ) {
            exit(0); 
        }
	return rv;
}

int get_var( char * var) {
    int rv = 0;
    char *temp;
    
    if ( (temp = strsep(&var, REFVAR)) != NULL) {
                printf("%s\n", VLlookup(var) );
               
                rv = 1;
            }
    
    return rv;
}

int get_value( char *var ) {
    int rv = 1;
    char *prompt = "= ";
    char *value;
    
        if ( (value = next_cmd(prompt, stdin)) != NULL ) {
            rv = VLstore(var, value);
        }
    return rv;
}

int assign(char *str)
/*
 * purpose: execute name=val AND ensure that name is legal
 * returns: -1 for illegal lval, or result of VLstore 
 * warning: modifies the string, but retores it to normal
 */
{
	char	*cp;
	int	rv ;

	cp = strchr(str,'=');
	*cp = '\0';
	rv = ( okname(str) ? VLstore(str,cp+1) : -1 );
	*cp = '=';
	return rv;
}
int okname(char *str)
/*
 * purpose: determines if a string is a legal variable name
 * returns: 0 for no, 1 for yes
 */
{
	char	*cp;

	for(cp = str; *cp; cp++ ){
		if ( (isdigit(*cp) && cp==str) || !(isalnum(*cp) || *cp=='_' ))
			return 0;
	}
	return ( cp != str );	/* no empty strings, either */
}
