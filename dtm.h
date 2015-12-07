/* 
 * File:   dtm.h
 * Author: travismoretz
 *
 * Created on December 6, 2015, 7:58 PM
 */

#ifndef DTM_H
#define	DTM_H

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


int	VLenviron2table(char **);
int	VLexport(char *);
char	*VLlookup(char *);
void	VLlist();
int	VLstore( char *, char * );
char	**VLtable2environ();
int	VLenviron2table(char **);

int getArgCount();
void setArgCount(int);

int myls1(int, char**);
int myfind(int, char**);
int prime();
int myprog();
int mycat(int, char**);






#ifdef	__cplusplus
}
#endif

#endif	/* DTM_H */

