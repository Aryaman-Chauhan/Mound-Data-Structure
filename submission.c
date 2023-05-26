#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <math.h>

const int MOUND_SIZE = 50000;//Size of mound array
int size = 0;//DO NOT CHANGE
const int Threshold = 1000;//Threshold of insertion
char filename[1024] = "PQ_Data.txt";//Name of the file that needs to be tested
int extractSize = 105000;//The no. of times you want to run extractMin function. Part of main, can be avoided

typedef struct LNode {
    int value;
    struct LNode *next;
} LNode;
typedef LNode *LNODE;

typedef struct MNode {
    LNODE list;//Stores the first node of the list
    int dirty;//If 0, mound condition satisfied, otherwise the mound needs to be none
    int c;//Here, we have the count of Linked List nodes stored
} MNode;
typedef MNode *MNODE;

LNODE createNode(int val);
MNode insertToFirstLL(MNode mound, int val);
int moundVal(MNODE mound, int i);
void increaseMoundLevel(MNODE mound, int val);
void insertToMound(MNODE mound, int val);
int moundSize(MNODE mound);
void destroyMound(MNODE mound);
void destroyLinkedList(LNODE node);
void extractMin(MNODE mound);
void moundify(MNODE mound, int i);
void swapNode(MNODE mound, int i1, int i2);
void printMound(MNODE mound);

/// @brief Created a Linked List Node and stored it into a newly allocated memory, and returns pointer to this node with the input val stored as node value.
/// @param val Value of New Node
/// @return Linked List Node with value equals val
LNODE createNode(int val){
    LNODE node = (LNODE)malloc(sizeof(LNode));
    node->next=NULL;
    node->value = val;
    return node;
}

/// @brief Inserts the Linked List Node with value equals val to a mound location at the beginning of the list.
/// @param mound Mound Node
/// @param val Value to be inserted
MNode insertToFirstLL(MNode mound, int val){
    LNODE node = createNode(val);
    node->next = mound.list;
    mound.c++;
    mound.list = node;
    return mound;
}

/// @brief Returns the value present at the first Node of Linked List, which is the definition of mound value according to definition. In case the list is empty, return INT_MAX, which the paper justifies as max value being stored in the list.
/// @param mound Mound Node
/// @return Value of Node
int moundVal(MNODE mound, int i){
    if(mound[i].list==NULL)
        return INT_MAX;			
    return mound[i].list->value;
}

/// @brief Increases level of mound by 1, and intializes the values of these nodes, than recalls insertToMound function.
/// @param mound Mound Structure
/// @param val Value to be inserted
/// @return Returns the changed Mound Node
void increaseMoundLevel(MNODE mound, int val){
    int x = size;
    size = 2*size +1;//Gives the new size, for eg 0->1, 1->3, 3->7 and so on. The new size is new total no. of nodes after Level is added
    for(;x<size;x++){
        mound[x].c=0;
        mound[x].dirty=0;
        mound[x].list= NULL;
    }
    insertToMound(mound, val);
}

/// @brief Inserts value to the mound after checking various conditions as stated in the paper.
/// @param mound Mound Structure
/// @param val Value to be inserted
void insertToMound(MNODE mound, int val){
    int thr = Threshold;
    while(thr>0){
        if(size<=0){
            thr = 0;
            break;
        }
        int nd = (size+1)/2;//No of leaf nodes
        int l = (size - nd) + rand() % nd;//The index of leaf nodes is returned
        if(moundVal(mound,l)< val){
            thr--;//Unsatisfactory node, the code is run again
            continue;
        }
        else{
            thr--;
            if(l==0){
                thr=0;
                mound[l] = insertToFirstLL(mound[l],val);
                return;
            }
            int lft = 0, last = 0, rt = l, counter = 1;
            while(lft < rt){
                if(lft == last)
                    counter = 1;
                else
                    counter++;
                int level = (int)log2(rt + 1);//Returns the level of leaf node
                int m = (rt - 1)/(pow(2, (int)(level/pow(2, counter))));//Middle node index
                if(moundVal(mound, m) < val){
                    last = lft;
                    lft = 2 * m + 2;//The right child of mid element selected for left, this allows checking the while condition wether the tree is on left or right
                }
                else{
                    rt = m;
                }
            }
            mound[rt] = insertToFirstLL(mound[rt], val);
            return;
        }
    }
    if(thr<=0){
        increaseMoundLevel(mound, val);
    }
}

/// @brief Simpy returns the size of mound. In our case, since we only have a single mound structure, this function is simply to complete implementation which returns the global variable stored in size variable.
/// @param mound Mound Structure
/// @return No of Mound Nodes
int moundSize(MNODE mound){
    return size;
}

/// @brief Frees the memory allocated to mound and the internal Linked Lists as well.
/// @param mound Mound Structure
void destroyMound(MNODE mound){
    for(int i = 0; i < size; i++){
        if(mound[i].list!=NULL){
            destroyLinkedList(mound[i].list);
        }
    }
    free(mound);
}

/// @brief Frees the Linked List inputted by freeing all the nodes with memory allocation.
/// @param node A Linked List Node
void destroyLinkedList(LNODE node){
    while(node!=NULL){
        LNODE temp = node->next;
        free(node);
        node = temp;
    }
}

/// @brief Shows the minimum value in the whole mound, and removes it from the mound such that the mound property is maintained using the moundify function.
/// @param mound Mound Structure
void extractMin(MNODE mound){
    if(size==0){
        printf("Mound is empty\n");
        return;
    }
    else if (size == 1){//This check had to be inserted otherwise error of missing nodes may arise as the function may try to free NULL
        if(mound[0].list == NULL){
            printf("Mound is empty\n");
            return;
        }
        printf("Minimum Value: %d\n", mound[0].list->value);
        LNODE temp = mound[0].list;
        mound[0].list = mound[0].list->next;
        free(temp);//Freeing the minimum node
        if(mound[0].list == NULL){
            size = 0;
            return;
        }
        return;
    }
    printf("Minimum Value: %d\n", moundVal(mound,0));
    LNODE temp = mound[0].list;
    mound[0].list = mound[0].list->next;
    mound[0].c--;
    mound[0].dirty = 1;
    free(temp);
    moundify(mound, 0);
}

/// @brief Swaps the values of Node1 and Node2.
/// @param node1 A mound node
/// @param node2 A mound node
void swapNode(MNODE mound, int i1, int i2){
    LNODE temp = mound[i1].list;
    int ctemp = mound[i1].c;
    mound[i1].c = mound[i2].c;
    mound[i1].list = mound[i2].list;
    mound[i2].c = ctemp;
    mound[i2].list = temp;
}

/// @brief Called on a certain index, changes the mound values and swaps them, such that the mound property is finally satisfied. Basically, aims to make the dirty property 0.
/// @param mound Mound Structure
/// @param i Index of Mound Structure
void moundify(MNODE mound, int i){
    int a = (int)log2(size);//These entire set of statement check wether the leaf nodes are all empty or not. If empty, decreases size appropriately
    a = (int)pow(2, a);
    int check = 0;
    for(int k = size - a; k < size; k++){
        if(mound[k].list != NULL){
            check=1;
            break;
        }
    }
    if(check==0)
        size = size - a;
    
    if((2*i+2)< size){
        if(mound[2*i+1].dirty == 1)
            moundify(mound, 2*i+1);
        if(mound[i*2+2].dirty==1)
            moundify(mound, i*2+2);
    }
    
    int par=moundVal(mound,i);
    int chil1, chil2;
    if((2*i+2)< size){//If children are outside the mound, no need to check any further
        chil1=moundVal(mound,i*2+1);
        chil2=moundVal(mound,i*2+2);
    }
    else{
        chil1 = INT_MAX;
        chil2 = INT_MAX;
    }
    if(par <= chil1 && par <= chil2){
		mound[i].dirty=0;
	}
    else if(chil1 < par && chil1 <= chil2){
		swapNode(mound,i,i*2+1);
		mound[i].dirty=0;
		mound[i*2+1].dirty=1;
		moundify(mound, i*2+1);
	}
	else if(chil2 < par && chil2 <= chil1){
		swapNode(mound,i,i*2+2);
		mound[i].dirty=0;
		mound[i*2+2].dirty=1;
		moundify(mound, i*2+2);
	}
}

/// @brief prints the mound in binary tree format using pyramid like shape
/// @param mound Mound Structure
void printMound(MNODE mound){
    int c =1;
    int x = 0;
    printf("Size: %d\n", size);
    if(size == 0){
        printf("Mound is empty\n");
        return;
    }
    for(; c <= size;c = (2*c + 1)){
        for(int i = x; i < c; i++){
            LNODE temp = mound[i].list;
            while(temp!= NULL){
                printf("%d ->", temp->value);
                temp = temp->next;
            }
            printf("T    ");
        }
        printf("\n\n");
        x = c;
    }
}

//our mound is a type of min heap and so we implenet it using an array
//where children are present at n*2+1,n*2+2

int main(void) {
    FILE *fptr;
    printf("Enter File name: ");
    scanf("%s",filename);
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
    printf("Enter no. of Extractions: ");
    scanf("%d%*c", &extractSize);
    for(int i = 0; i < extractSize; i++){
        extractMin(mound);
    }
    // extractMin(mound);
    // printMound(mound);
    // printMound(mound);
    destroyMound(mound);
    fclose(fptr);
    return 0;
}