/* 
 * File:   main.c
 * Author: travismoretz
 *
 * Created on October 13, 2015, 8:19 AM
 */
#include <libc.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/dirent.h>
#include <sys/dir.h>


int aflag = 0;
void do_ls(char []);

int myls1(int ac, char *av[])
{
   
   if (ac < 1 && av[1][0] == '-') {
     aflag = 1; 
   }
   if (ac == 1) {
      do_ls( "." );
   }
   else if (ac == 2) {
       if(av[1][0] == '-')
           aflag = 1;
       do_ls(".");
   }
   else
      for(int i = 1; i <= ac; i++) {
         if(av[i][0] == '-') {
             continue;
         }
         do_ls(av[i]);
         break;
      }
   return 0;
}

void do_ls(char dirname[])
{
   DIR           *dir_ptr;      /* the directory */
   struct dirent *direntp;      /* each entry    */
   if ((dir_ptr = opendir(dirname)) == NULL)
      fprintf(stderr,"ls1: cannot open %s\n", dirname);
   else
   {
      while ((direntp = readdir(dir_ptr)) != NULL) {
        if(!aflag) {
             if(direntp->d_name[0] == '.')
             continue;
        }
         printf("%s\n", direntp->d_name);
      }
      
      closedir(dir_ptr);
   }
}

