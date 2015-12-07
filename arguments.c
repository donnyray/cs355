/*
 * arguments.c
 * Author: Travis Moretz
 * 
 * This is for getting the number of arguments that are being passed to programs.
 * Made for integrating homework assignments into myshell
 * 
 * Get and Set argument count.
 * 
 */

static int ar = 0;

/**
 * 
 * @return ar  
 */
int getArgCount() {
    return ar;
}

/**
 * 
 * @param argsCount set ar
 */
void setArgCount(int argsCount ) {
    ar = argsCount;
}