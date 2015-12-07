/* 
 * File:   mycat.c
 * Author: travismoretz
 *
 * Created on September 30, 2015, 8:24 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <unistd.h>

/*
 * 
 */
int mycat(int argc, char** argv) {

    int fd;
    char buff[512];
    size_t ch;
    struct stat st;
    int eFlag = 0, nFlag = 0, sFlag = 0;
    
    /* check to make sure file(s) are specified */
    if (argc < 1) {
        printf("No file specified\n");
        return(EXIT_FAILURE);
    }

    /* test args for flags/ options/ switches, what every you want to call them
     * and set the corresponding flags */
        for(int i = 1; i < argc; i++) { 
            if((argv[i][0]) == '-'){
                for(int f = 0; f < strlen(argv[i]); f++) {
                    if(argv[i][f] == 'e')
                        eFlag = 1;
                    if(argv[i][f] == 'n')
                        nFlag = 1;
                    if(argv[i][f] == 's')
                        sFlag = 1;
                }
            } 
        }

    /* if flags are present processes the input with said flags */
    if(eFlag || nFlag || sFlag) {
        
        int scratch = 0;     /* counter for chars in the buffer */
        int prev = 0;

        for(int i = 1; i < argc; i++) {
            int lineCount = 1;  /* line counter for nFlag*/
            /* if the arg being checked is for applying flags, skip it */
            if(argv[i][0] == '-') {
                continue;
            }
            else {
                fd = open(argv[i], O_RDONLY);
                if (fd == -1) {
                    printf("error opening file: %s", argv[i]);
                }
                else {
                    if (nFlag)
                        printf("%d\t", lineCount);
                    

                    while ((ch = read(fd, buff, sizeof (char)))) {
                        if ((*buff < 32 || *buff == 127) && *buff != 10) {
                            continue;
                        }

                        if(sFlag) {
                            if(prev == '\n') {
                                if (*buff == '\n') {
                                        continue;
                                }
                            }
                        }
                       
                        if(*buff == '\n') {
                            if (eFlag) {
                                printf("$");
                                printf("%c", *buff);
                            }
                            if(nFlag) {
                                if(!eFlag)
                                    printf("%c", *buff);
                                printf("%d", ++lineCount);
                            }
                            
                        } 
                        else {
                            printf("%c", *buff);
                        }
                        

                        if (sFlag)
                            prev = *buff;
                        
                    }
                    printf("\n");
                }


            }
        }
    } /* if no flags just print the files as they are */
    else {
        for(int i = 1; i < argc; i++) {
            if(argv[1][0] == '-') {
                continue;
            }
            else {
                fd = open(argv[i], O_RDONLY);
                if (fd == -1) {
                    printf("error opening file: %s", argv[i]);
                }
                else {
                    while( (ch = read(fd, buff, sizeof(char)))) {
                       printf("%s", buff); 
                    }
                    putchar('\n');
                        
                }
            }
            
        }
        
    }
        return(3);
}
