/* 
 * File:   varlib.h
 * Author: travismoretz
 *
 * Created on November 30, 2015, 9:19 AM
 */

#ifndef VARLIB_H
#define	VARLIB_H

#ifdef	__cplusplus
extern "C" {
#endif


/*
 * header for varlib.c package
 */

int	VLenviron2table(char **);
int	VLexport(char *);
char	*VLlookup(char *);
void	VLlist();
int	VLstore( char *, char * );
char	**VLtable2environ();
int	VLenviron2table(char **);

#ifdef	__cplusplus
}
#endif

#endif	/* VARLIB_H */

