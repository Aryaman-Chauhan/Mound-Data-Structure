# Implemention of Mound Data Structure
This repository has complete working code, and is now archived.
## Problem Statement
You need to implement the mound data structure explained in Section 2 of the paper. You don't need consider the other sections of the [paper](https://github.com/Aryaman-Chauhan/Mound-Data-Structure/blob/main/Mounds_Array-Based_Concurrent_Priority_Queues.pdf). Implement the mound and insert all the objects present in data.txt. Implement all other operations present in the paper. If there are any parameters to be chosen, you can choose them by your choice.

Then write a function that repeatedly performs removeMin() operation and prints the extracted object each time, until all the objects in the mound are exhausted.
## Steps To Run
1. Save and download "submission.c" file in your system
2. Save and download the dataset you want to use the code with
3. Open Terminal and locate the folder in which you have saved the c file as well as the dataset
4. Type in terminal *gcc submission.c -lm* press enter
5. Type in terminal *./a.out*
6. Give the file name of the dataset that you want to test the code press enter
7. The code will first populate the dataset and then print the mound formed.
8. The code then asks number of extract min operation the user wants and carries it out and prints the result

## Work on the Code
1. Code is thoroughly explained in a [presentation](https://github.com/Aryaman-Chauhan/Mound-Data-Structure/blob/main/DSA_PROJECT_PPT.pdf) format.
2. The code has been implemented with proper explanation through a multifile system in the implementation folder.
3. You can run the code by using the linux command "gcc -g -o mound.exe mound.c driver.c -lm" and then run "./mound.exe".
4. For windows, run the code by using the linux command "gcc -g -o mound.exe mound.c driver.c" and then run "mound.exe".
