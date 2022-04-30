/*
    Filename: functions.h
    Author: Karin Nielsen
    Date: 04/25/2022
    Description: 
        Header file to define functions

*/


/* Include statements */
#include <stdbool.h> 
#include "structs.h"


/* error handling functions */
void readErrorChk(int); 
void lseekErrorChk(unsigned long long); 


/* functions for reading clusters and checking for file signatures*/
void readClusters(int);
void checkSignature(struct entire_cluster * , unsigned int, unsigned long long);



// THIS IS FROM OTHER PROGRAM TO HELP WITH PASSING BUFFERS
//take entry number given and return a 1024 byte long buffer containing the entry data
unsigned char * getEntryBuf(int, unsigned long long, /*unsigned long long, */unsigned char *); 