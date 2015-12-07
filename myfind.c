/* 
 * File:   myfind.c
 * Author: travismoretz
 *
 * Created on November 3, 2015, 4:05 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>

void do_ls(char[]);
void dostat(char *);
void show_file_info(char *, struct stat *);
void mode_to_letters(int , char[]);

/* print the names that match*/
void compare_names( char [], char []);
int is_direc(char * );


/*
 * 
 */
int myfind(int argc, char** argv) {
    printf("In myfind\n");
    /* test for proper args input*/
    if( argc < 2) {
        perror("Error");
        exit(1);
    }
    else if( argc == 3) {
        /* if directory was specified start there */
        char *startdir = malloc(strlen(argv[2]));
        startdir = argv[2];
        chdir(startdir);
      compare_names(argv[1], ".");
      free(startdir);
    } /* if no directory was specified start in current */
    else
       compare_names(argv[1], ".");
    return (1);
}

/**
 * this will take in a "substring" (tofind) compare it to all file/ directories 
 * in the current or specified startpath and compare the substring to the names of each
 * file. If there is a match print it to the screen. 
 * If a directory is found add it to a list to search once this current directory
 * has been fully searched. 
 * 
 * @param tofind : string searching for
 * @param dir_name : starting directory
 */
void compare_names( char tofind[], char dir_name[]) {
    DIR             *dir_ptr;
    struct dirent   *dp;
    char dirpath[1024];
    char *dptr = dirpath;
    /* open the current directory to search for matching file names */
    if ( (dir_ptr = opendir(dir_name)) == NULL) {
        fprintf(stderr, "cannot open %s\n", dir_name);
       
    } 

    // while there is an entry in the directory read it
    while( (dp = readdir(dir_ptr)) != NULL ) {
        /* get current working directory */
        if (getwd(dirpath) == NULL ) {
               perror("directory path error"); 
            }
        
        /* test if it is another directory if it is add the full file path to 
         */ 
        if(is_direc(dp->d_name) == 0 ) {
            /* do not re-read current directory or move to parent directory */
            if(strcmp(dp->d_name,"." )  ==  0 || strcmp(dp->d_name,"..") == 0 )
                continue; 

            /* add a backslash then directory name to current directory path */
            strcat(dirpath, "/");
            strcat(dirpath, dp->d_name);
            /* change directory, recursively check that directory then change back */
            chdir(dirpath);
            compare_names(tofind, ".");
            chdir("..");
        }
        
        //if the substring matches part of the entry name print it
        else if ((strstr(dp->d_name, tofind)) != NULL ) {
            // if the directory path has not been printed print it. 
            printf("%s\n", dirpath);
            /* print file name */
            printf("   %s", dp->d_name );
            putchar(' ');
            /* print mode and permissions */
            dostat(dp->d_name);  
        }
    }
    closedir(dir_ptr);
    return;
}


/**
 * test if the entry in the directory is another directory 
 * @param filename
 * @return 0 if a directory
 */
int is_direc(char *filename) {
    struct stat info;

    if(stat(filename, &info) == 1 ) {
        perror(filename);
    }
    if (S_ISDIR(info.st_mode) !=0 ) {
        return (0);
    }
    
    return (-1);
}

/**
 * primer function for getting file mode
 * @param filename
 */
void dostat( char *filename) {
    struct stat info;
    
    if (stat(filename, &info) == -1 ) {
        perror("filename");
    }
    else
        show_file_info( filename, &info );
}
/**
 * print the file mode
 * @param filename
 * @param info_p
 */
void show_file_info (char *filename, struct stat *info_p ) {
    char *filemode();
    void mode_to_letters();
    char modestr[12];
    printf("(%d/", info_p->st_mode);
    mode_to_letters(info_p->st_mode, modestr);
    
    printf("%s\n", modestr);
}

/**
 * print the  letter representation of file mode 
 * @param mode
 * @param str
 */
void mode_to_letters(int mode, char str[]) {

    strcpy(str, "----------)");

    
    if (S_ISDIR(mode)) str[0] = 'd';
    if (S_ISREG(mode))  str[0] = '-';
    if (S_ISBLK(mode)) str[0] = 'b';
    
    if (mode & S_IRUSR) str[1] = 'r';
    if (mode & S_IWUSR) str[2] = 'w';
    if (mode & S_IXUSR) str[3] = 'x';
    
    if (mode & S_IRGRP) str[4] = 'r';
    if (mode & S_IWGRP) str[5] = 'w';
    if (mode & S_IXGRP) str[6] = 'x';
    
    if (mode & S_IROTH) str[7] = 'r';
    if (mode & S_IWOTH) str[8] = 'w';
    if (mode & S_IXOTH) str[9] = 'x';

}
