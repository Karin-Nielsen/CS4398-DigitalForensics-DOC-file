# README.md

### CS4398-DigitalForensics-DOC-file

# Description

**_This is the File Type Project for UTD CS4398 Digital Forensics._**

*A file type identification project (for a .doc type file) written in the C language designed to:*

**Requirements / Instructions**

  * Run on a Linux Operation System.
  * Scan an NTFS type partition. 
  * Check for file type signatures on each cluster of the partition and print the partition # when found. 
  * Do not stop the scanning the clusters when a signature is found, continue to search for signatures in the rest of the partition. 
  * Use a clean partition that has never had this file type on it. 
  * When you've successfully run the program for one .doc file, add another .doc file and your program should then print two cluster numbers.


## Compile the following files using gcc:

structs.h
functions.h
main.c
errorChk.c
helpers.c


**Example:**

* $ gcc structs.h functions.h main.c errorChk.c helpers.c -o findDoc


## Run the executable using the the following arg(s) (source/ name depends on how it appears on linux):

* $ ./findDoc /dev/sdb1