#include "mound.h"
#include <stdio.h>
#include <stdlib.h>

const int MOUND_SIZE = 50000;
const char filename[1024] = "data.txt";

int main(void) {
    FILE *fptr;
fptr = fopen(filename, "r");
    if (fptr == NULL) {
    printf("Error in opening the file\n");
    return 0;
    }
    MNODE mound = (MNODE)malloc(sizeof(MNode)*MOUND_SIZE);
    for(int i = 0; i < MOUND_SIZE; i++){
        mound[i].c = 0;
        mound[i].dirty = 0;
        mound[i].list=NULL;
    }
    char buffer[1024];
    int c = 0;
    while (fgets(buffer, 1024, fptr)) {
        int a = atoi(buffer);
        insertToMound(mound, a);
        // printf("%d\n", a);
        c++;
        // if(c==90000)
        //     break;
    }
    printMound(mound);
    int t = moundSize(mound);
    for(int i = 0; i < 24; i++){
        extractMin(mound);
    }
    // extractMin(mound);
    // printMound(mound);
    printf("Size: %d\n", moundSize(mound));
    // printMound(mound);
    destroyMound(mound);
    fclose(fptr);
    return 0;
}