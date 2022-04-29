/*
    Filename: functions.h
    Author: Karin Nielsen
    Date: 04/25/2022
    Description: 
        Header file to define functions

*/

/* error handling functions */
void readErrorChk(int); 
void lseekErrorChk(unsigned long long); 

/* functions for reading clusters and checking for file signatures*/
void readClusters(int fd);
