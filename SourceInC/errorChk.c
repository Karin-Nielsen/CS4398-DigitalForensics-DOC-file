/*
    Filename: errorChk.c
    Author: Karin Nielsen
    Date: 03/12/2022
    Description: 

        Contains functions for frequent error checks in the rest of the program's code.

*/

/* Include statements */
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"


/* Function declarations */
void readErrorChk(int retVal) {
    if (retVal < 0)  {
        fprintf(stdout, "ERROR: unable to read disk, retVal = %d, exiting program\n\n", retVal);
        exit(0);
    }
}


void lseekErrorChk(unsigned long long curLoc) {
    if (curLoc < 0) {
        fprintf(stdout, "ERROR: unable to lseek on disk, curLoc = %lld, exiting program\n\n", curLoc);
        exit(0);
    }
}