/*
    Filename: helpers.c
    Author: Karin Nielsen
    Date: 04/25/2022
    Description: 
        
        Contains functions: 
          - readClusters(): 
              * Loop reading one cluster into a buffer (4096 bytes) at a time
              
          - checkSignatures():
              * Loops byte by byte in the passed cluster buffer to identify .doc file signature, and in which cluster.
            
*/


/* Include statements*/
#include <stdio.h>      // fprintf()
#include <stdbool.h>    // bool types
#include <unistd.h>     // lseek()
#include <stdlib.h>     // malloc()
#include "functions.h"


/* Functions */
void readClusters(int fd) {

    fprintf(stdout, "Entering readClusters() function\n");

    /* Define variables */
    /* Cluster/buffer vars */
    struct entire_cluster clustStruct;         // cluster struct
    unsigned char * entireClustBuf;     // buffer to store entire 4096 cluster
    unsigned int clusterSize = sizeof(struct entire_cluster);  // 4096

    /* Disk location vars */
    unsigned long long curLoc;
    unsigned long long diskSize;

    /* Error checking boolean */
    bool retVal;

    /* Iteration variable(s) */
    unsigned long long clustCount = 0;


    /* Navigate to beginning of disk*/
    curLoc = lseek(fd, 0, SEEK_SET); 
    lseekErrorChk(curLoc);
    fprintf(stdout, "Ensure disk located at beginning of partition: %llu\n", curLoc);


    /* Check disk size and rest disk location back to beginning of partition */
    curLoc = lseek(fd, 0, SEEK_CUR);
    lseekErrorChk(curLoc);
    fprintf(stdout, "Test first disk location: %llu\n", curLoc);
    
    diskSize = lseek(fd, 0, SEEK_END);
    lseekErrorChk(diskSize);

    curLoc = lseek(fd, 0, SEEK_SET);
    lseekErrorChk(curLoc);
    fprintf(stdout, "Back to first disk location: %llu\n", curLoc);


    /* Allocate memory to prevent corrupted data */
    entireClustBuf = (unsigned char*)malloc(4096 * sizeof(unsigned char)); 
    entireClustBuf[0] = '\0';


    /* Loops by cluster; reading each cluster into a buffer to search for the signature  */
    fprintf(stdout, "Starting loop for each cluster in whole partition.\n\n");
    while (curLoc < diskSize) {
        //fprintf(stdout, "  -- ClusterCount: %llu --  ", clustCount);


        /* Read in clustStruct */
        entireClustBuf = (unsigned char *)&clustStruct; 
        retVal = read(fd, entireClustBuf, clusterSize); 
        readErrorChk(retVal); 

        /* lseek() to check correct current address for next cluster */
        curLoc = lseek(fd, 0, SEEK_CUR);
        lseekErrorChk(curLoc);
        //fprintf(stdout, "Check disk location for current cluster : %llu\n", curLoc); 


        /* Call function that reads each byte of cluster and checks for .doc file header signature */
        checkSignature(&clustStruct, clusterSize, clustCount);
        
        clustCount++; // iterate # of clusters we've read

    }

    fprintf(stdout,"Cluster loop complete.\n");

}



void checkSignature(struct entire_cluster * buf, unsigned int clusterSize, unsigned long long clustCount) {

    
    /* Define function iteration variable(s) */
    unsigned int i = 0;


    /*
        .doc header signature is 24 bytes long: 
            HEX:        0xD0, 0xCF, 0x11, 0xE0, 0xA1, 0xB1, 0x1A, 0xE1, followed by sixteen zeroes
            DECIMAL:    208, 207, 17, 224, 161, 177, 26, 225, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    */
    /* Loop through each byte in cluster, check for first byte in file signature */
    for (i = 0 ; i < clusterSize ; i++) {

        /* 
            If statement to check each byte to see if we have the 
            start of the header signature. Hex: 0xD0 ; Decimal: 208
        */
        if(buf->cluster[i]== 208) { 

            /* Now verify that the remaining 23 bytes match the .doc file signature */
            if (buf->cluster[i] == 208 &&       // Byte #1
                buf->cluster[i+1] == 207 &&     
                buf->cluster[i+2] == 17 &&
                buf->cluster[i+3] == 224 &&
                buf->cluster[i+4] == 161 &&     // Byte #5
                buf->cluster[i+5] == 177 &&     
                buf->cluster[i+6] == 26 &&
                buf->cluster[i+7] == 225 &&
                buf->cluster[i+8] == 0 &&
                buf->cluster[i+9] == 0 &&       // Byte #10
                buf->cluster[i+10] == 0 &&
                buf->cluster[i+11] == 0 &&
                buf->cluster[i+12] == 0 &&
                buf->cluster[i+13] == 0 &&
                buf->cluster[i+14] == 0 &&      // Byte #15
                buf->cluster[i+15] == 0 &&
                buf->cluster[i+16] == 0 &&
                buf->cluster[i+17] == 0 &&
                buf->cluster[i+18] == 0 &&
                buf->cluster[i+19] == 0 &&      // Byte #20
                buf->cluster[i+20] == 0 &&
                buf->cluster[i+21] == 0 &&
                buf->cluster[i+22] == 0 ) {     // Byte #24
                
                

                /* If so, print our hex values as validation */
                fprintf(stdout,"---------------------------------------\n\n");
                fprintf(stdout, ".doc file header signature:\n\n\t %llx %llx %llx %llx %llx %llx %llx %llx %llx %llx %llx %llx %llx %llx %llx %llx %llx %llx %llx %llx %llx %llx %llx \n\n", 
                        buf->cluster[i], buf->cluster[i+1], buf->cluster[i+2], buf->cluster[i+3], buf->cluster[i+4],
                        buf->cluster[i+5], buf->cluster[i+6], buf->cluster[i+7], buf->cluster[i+8], buf->cluster[i+9],
                        buf->cluster[i+10], buf->cluster[i+11], buf->cluster[i+12], buf->cluster[i+13], buf->cluster[i+14],
                        buf->cluster[i+15], buf->cluster[i+16], buf->cluster[i+17], buf->cluster[i+18], buf->cluster[i+19],
                        buf->cluster[i+20], buf->cluster[i+21]);


                /* Also print the cluster number where this was found */
                fprintf(stdout,".doc file signature found in cluster number: % llu\n\n", clustCount);
                fprintf(stdout,"---------------------------------------\n\n");
                    
            }
        } 
    } 
}
