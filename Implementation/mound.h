#ifndef MOUND_H
#define MOUND_H

typedef struct LNode {
    int value;
    struct LNode *next;
} LNode;
typedef LNode *LNODE;

typedef struct MNode {
    LNODE list;
    int dirty;
    int c;
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

#endif