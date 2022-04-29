/*
    Filename: structs.h
    Author: Karin Nielsen
    Date: 04/25/2022
    Description: 
        Header file to define structs
        8 bits = 1 byte ; 16 bits = 2 bytes ; 32 bits = 4 bytes ; 64 bits = 8 bytes
        
*/


typedef struct entire_cluster {
   __u8 cluster[4096]; 
} ENTIRE_cluster;
