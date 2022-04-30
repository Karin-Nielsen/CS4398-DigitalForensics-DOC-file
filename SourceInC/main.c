
/*
    Filename: main.c
    Author: Karin Nielsen
    Date: 04/26/2022
    Description: 
        Main method. 
                Error handle args passed from command line. 
                Open the disks named in argv[1] (read only).
                Call SOME METHOD() to read in clusters and check for 
                Close disks. 
*/


/* Include statements */
#include <stdio.h>      // printf(), fprintf()
#include <fcntl.h>      // open() 
#include <unistd.h>     // close()
#include "functions.h"
//#include "structs.h"


/* Function(s) */
int main(int argc, char** argv) {

        printf("\n---------------------------------------\n\n");

        /* Define variables */
        int fd; 


        /* Error handling */
        /* Check for 2 arguments and opened partition successfully */
        if(argc != 2) {
           fprintf(stderr, "(0)USAGE: %d arg count: \n", argc);
           return(0);
        }
  
        /* Open and write only */
        printf("Opening read disk...\n");
        fd = open(argv[1], O_RDONLY);
        if ( fd < 0 ) {
            fprintf(stderr, "device not opened = %s. Exiting program. \n", argv[1] );
            return(0);
        }

        fprintf(stdout, "Read disk opened successfully!\n\n");
  

        fprintf(stdout, "Calling readClusters()\n");
        readClusters(fd);
  
  
 /* ---------------- Close disk(s) and end program ---------------- */

        fprintf(stdout,"\n---------------------------------------\n\n");
        fprintf(stdout, "Closing disk and exiting program.\n\n");
        close(fd);
  
}
