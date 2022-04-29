
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
#include <stdio.h>
#include <stdlib.h> 


/* Function(s) */
int main(int argc, char** argv) {

        printf("\n---------------------------------------\n\n");

        /* Define variables */
        int fd; 
  
  
        /* Open and write only */
        printf("Opening read disk...\n");
        fd = open(argv[1], O_RDONLY);
        if ( fd < 0 ) {
            fprintf(stderr, "device not opened = %s. Exiting program. \n", argv[1] );
            return(0);
        }
        
        printf("Read disk opened successfully!\n\n");
  
        printf("Calling readClusters()\n");
  
  
  
 /* ---------------- Close disks and end program ---------------- */

        close(fd);
  
}
