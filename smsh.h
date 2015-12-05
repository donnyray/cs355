/* 
 * File:   smsh.h
 * Author: travismoretz
 *
 * Created on November 30, 2015, 8:42 AM
 */

#ifndef SMSH_H
#define	SMSH_H

#ifdef	__cplusplus
extern "C" {
#endif


#define	YES	1
#define	NO	0
#define REFVAR  "$"
    

char	*next_cmd();
char	**splitline(char *);
void	freelist(char **);
void	*emalloc(size_t);
void	*erealloc(void *, size_t);
int	execute(char **);
void	fatal(char *, char *, int );

int	process();



#ifdef	__cplusplus
}
#endif

#endif	/* SMSH_H */

