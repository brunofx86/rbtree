/*
 * rbtree.h
 *
 *  Created on: 9 de nov de 2018
 *      Author: Dutra Xavier
 */

#ifndef RBTREE_H_
#define RBTREE_H_

#define RED   'R'
#define BLACK 'B'

#define MAXCHARACTERS 20

typedef struct RBElement {
    char             *key;
    char              color;
    struct RBElement *left;
    struct RBElement *right;
    struct RBElement *parent;
} RBElement;


typedef struct RBTree
{
    struct RBElement *root;
} RBTree;


RBTree* newRBTree(void);
RBElement* newNode(char *key);

void Left_Rotate( RBTree* T, RBElement* x);
void Right_Rotate(RBTree* T, RBElement* y);
void RB_Insert_Fixup(RBTree* T, RBElement* z);
void RBInsert(RBTree* T, char key[]);

RBElement* Tree_Minimum(RBElement* x);
RBElement* Tree_Maximum(RBTree* T);
void RB_Transplant(RBTree* T, RBElement* z, RBElement* y);
void RB_Delete_Fixup(RBTree* T, RBElement* x);
void RB_Delete(RBTree* T, RBElement* z);

RBElement* Search(RBTree* T, char *key);
void RBInOrder(RBElement* x);
void RBPreOrder(RBElement* x);
void RBPrint(RBTree* T);
void RBCheck(RBTree* T);



#endif /* RBTREE_H_ */
