/*
 * rbtree.c
 *
 *  Created on: 9 de nov de 2018
 *      Author: Dutra Xavier
 */

#include"RBTree.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


// Based on CLRS algorithm, use T_Nil as a sentinel to simplify code
struct RBElement T_Nil_Node;
RBElement* T_Nil = &T_Nil_Node;

//Node* Root = NULL;


RBTree* newRBTree(void)
{
    RBTree* tree   =  malloc(sizeof(RBTree));
    if(tree == NULL){
    	printf("** insufficient memory **");
    	 return NULL;
    }

    tree->root = T_Nil;


    return tree;
}


char *Alocate_String(int n)
{
	char *ch; // ponteiro para o vetor de carateres
	ch = malloc(n*sizeof(char));
	if (ch == NULL){
	   printf("** insufficient memory **");
	    	return (NULL);
	 }

	return ch;

}

char *Free_String(char *ch)
{
	if (ch == NULL){
	    	return (NULL);
	 }

    free(ch);
	return NULL;
}

// A utility function to create a new BST node
RBElement* newNode(char *key)
{
    RBElement *node   = (RBElement*) malloc(sizeof(RBElement));
    if (node == NULL) {
    	printf("** insufficient memory **");
    	return NULL;
    }

    node->key    = malloc(strlen(key)+1);

    if (node->key == NULL) {
    	free(node);
    	return NULL;
    }

    strcpy(node->key, key);
    node->color  = RED;
    node->left   = T_Nil;
    node->right  = T_Nil;
    node->parent = T_Nil;

    return node;
}

void RBFreeElement(RBElement* x){

   if (x != T_Nil){
	   RBFreeElement(x->left);
	   RBFreeElement(x->right);
	   free(x->key);
	   x->key = NULL;
/*      free(x);
      x = NULL;*/
   }
}

void RBFree(RBTree* T){

	RBElement* x = T->root;
	printf("\n====== Free Tree ========\n");
	RBFreeElement(x);
}


void Left_Rotate( RBTree* T, RBElement* x)
{
    RBElement *y  = x->right;    // set y
    x->right = y->left;     // turn y's left subtree into x's right subtree{
    if (y->left != T_Nil)
        y->left->parent = x;
    y->parent = x->parent;  // link x's parent to y
    if (x->parent == T_Nil)
        T->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left   = x;            // put x on y's left
    x->parent = y;
}

void  Right_Rotate(RBTree* T, RBElement* y)
{
    RBElement *x  = y->left;     // set x
    y->left  = x->right;    // turn x's right subtree into y's left subtree{
    if (x->right != T_Nil)
        x->right->parent = y;
    x->parent = y->parent;  // link y's parent to x
    if (y->parent == T_Nil)
        T->root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left  = x;
    x->right  = y;         // put y on x's right
    y->parent = x;
}

void RB_Insert_Fixup(RBTree* T, RBElement* z)
{
    RBElement* y;
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            y = z->parent->parent->right;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    Left_Rotate(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                Right_Rotate(T, z->parent->parent);
            }
        }
        else
        {
            y = z->parent->parent->left;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    Right_Rotate(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                Left_Rotate(T, z->parent->parent);
            }
        }
    }
    T->root->color = BLACK;
}

void RBInsert(RBTree* T, char *key)
{

    RBElement* z =  newNode(key);
    RBElement* y =  T_Nil;
    RBElement* x = T->root;

    // Find where to Insert new node Z into the binary search tree
    while (x != T_Nil) {
        y = x;
        if (strcmp(z->key, x->key) < 0)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == T_Nil){
    	 T->root = z;
    }

    else if (strcmp(z->key, y->key) < 0){
    	  y->left  = z;
    }

    else {
        y->right = z;
    }
    // Init z as a red leaf
    z->left  = T_Nil;
    z->right = T_Nil;
    z->color = RED;

    // Ensure the Red-Black property is maintained
    RB_Insert_Fixup(T, z);
}

#define MAX(a,b) (((a)>(b))?(a):(b))

int RBHeight(RBElement* node)
{
    int h = 0;

    if (node != NULL) {
        if (node == T_Nil)
            h = 1;
        else
        {
            int leftHeight  = RBHeight(node->left);
            int rightHeight = RBHeight(node->right);
            h = MAX(leftHeight, rightHeight) + 1;
        }
    }

    return h;
}
int RBBlackHeight(RBElement* n){
int h = 0;
int hl = 0;
int hr = 0;
        while (n->left != T_Nil){
            if (n->left->color == BLACK) {
            	hl++;
            }

            n = n->left;
        }

        while (n->right != T_Nil){
            if (n->right->color == BLACK) {
            	hr++;
            }

            n = n->right;
        }
        if (hl != hr){
        	printf("Black Height Error\n");
        }else{
        	h = hl + 1;
        }

        return h;

}

void RBInOrder(RBElement* x)
{

	if (x != T_Nil) {
		RBInOrder(x->left);
        printf("%s ", x->key);
        RBInOrder(x->right); }
}

void PrintColor(RBElement* x){
	if(x->color == BLACK)
		printf("black");
	else
		printf("red");
}

void PrintKey(RBElement* x){
	if(x != T_Nil)
		printf("%s", x->key);
	else
		printf("NIL");
}

void PrintParent(RBElement* x){
	if(x->parent != T_Nil)
		printf("%s", x->parent->key);
	else
		printf("NIL");
}

void PrintRight(RBElement* x){
	if(x->right != T_Nil)
		printf("%s", x->right->key);
	else
		printf("NIL");
}

void PrintLeft(RBElement* x){
	if(x->left != T_Nil)
		printf("%s", x->left->key);
	else
		printf("NIL");
}

void RBPreOrder(RBElement* x)
{
	int h;
	if (x != T_Nil) {
	//	h = RBBlackHeight(x);
		printf("(");
		PrintParent(x); printf(", ");
        PrintKey(x); printf(", ");
        PrintColor(x); printf(", ");
        PrintLeft(x); printf(", ");
        PrintRight(x); printf(")\n");
		RBPreOrder(x->left);
        RBPreOrder(x->right); }
}


void RBCheck(RBTree* T){
	RBElement* x = T->root;
	printf("\nRBCheck: \n");
	if (x != T_Nil){
		RBPreOrder(x);
		printf("\n");
	}
	else{
		printf("** empty tree **\n");
	}

}

void RBPrint(RBTree* T)
{
	RBElement* x = T->root;
	printf("\nRBPrin: ");
	if (x != T_Nil){
		RBInOrder(x);
		printf("\n");
	}
	else{
		printf("** empty tree **\n");
	}

}

RBElement* Tree_Minimum(RBElement* x)
{
	while(x->left != T_Nil){
		x = x->left;
	}

	return x;
}

RBElement* Tree_Maximum(RBTree* T)
{
	RBElement* x = T->root;
	while(x->right != T_Nil){
		x = x->right;
	}

	return x;
}

void RB_Transplant(RBTree* T, RBElement* z, RBElement* y){
	if (z->parent == T_Nil){
		T->root = y;
	}

	else if (z == z->parent->left){
		z->parent->left = y;
	}
	else {
		z->parent->right = y;
	}

		 y->parent = z->parent;


}

void RB_Delete_Fixup(RBTree* T, RBElement* x){
    RBElement* w;
    while (x != T->root && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                Left_Rotate(T, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK){
            	w->color = RED;
            	x = x->parent;
            }
            else {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    Right_Rotate(T, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                Left_Rotate(T, x->parent);
                x = T->root;
            }
        }
        else
        {
            w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                Right_Rotate(T, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK){
            	w->color = RED;
            	x = x->parent;
            }
            else {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    Left_Rotate(T, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                Right_Rotate(T, x->parent);
                x = T->root;
            }
        }
    }

    x->color = BLACK;

}

void RB_Delete(RBTree* T, RBElement* z){

	RBElement* x;
	RBElement* y = z;
    char y_original_color = y->color;
    if (z->left == T_Nil) {
    	x = z->right;
    	RB_Transplant(T, z, z->right);
    }
    else if (z->right == T_Nil) {
    		x = z->left;
    		RB_Transplant(T, z, z->left);
    }
    else{
    	y = Tree_Minimum(z->right);
    	y_original_color = y->color;
    	x = y->right;
    	if (y->parent == z)
    		x->parent = y;
    	else {
    		RB_Transplant(T, y, y->right);
    		y->right = z->right;
			y->right->parent = y;
    	}

		RB_Transplant(T, z, y);
    	y->left = z->left;
    	y->left->parent = y;
    	y->color = z->color;
    }

    free(z);
    z = NULL;

    if (y_original_color == BLACK)
     RB_Delete_Fixup (T, x);

	RBCheck(T);

}

RBElement* Search(RBTree* T, char *key){
        RBElement* x = T->root;

        while (x != T_Nil && strcmp(key, x->key) != 0){
            if (strcmp(key, x->key) < 0)
                x = x->left;
            else
            	x = x->right;
        }

        if(x != T_Nil){
        	printf("Key %s founded\n", x->key);
        }
        else{
        	printf("Key %s not found\n", key);
        }


        return x;
    }


int main(int argc, char *argv[])
{

	printf("\n**************************************************\n");
	printf("\nPOSTGRADUATE PROGRAM IN SYSTEM AND COMPUTING");
	printf("\nALGORITHMS AND DATA STRUCTURES: RED BLACK TREE");
	printf("\nPROFESSOR: BRUNO MOTTA");
	printf("\nSTUDENT: BRUNO XAVIER\n");
	printf("\n**************************************************\n");
	char *word;
	word = malloc(MAXCHARACTERS*sizeof(char));
	int options;

    RBTree* myTree = newRBTree();
    printf("\n======================= OFFLINE MODE =============================\n\n");

   	       FILE *fp;
   	       fp = fopen(argv[1], "r"); // read mode

   	       if (fp == NULL)
   	       {
   	          perror("Error while opening the file.\n");
   	          exit(EXIT_FAILURE);
   	       }

   	       printf("\nThe contents of %s file are:\n\n", argv[1]);


   	       while(fscanf(fp,"%s %d", word, &options) !=EOF){
   	  	   if(options == 0){
   	  		   RBElement* n = Search(myTree,word);
   	  		   if (n != T_Nil){
   	  		   printf("Removing %s\n", word);
   	  		   RB_Delete(myTree, n);
   	  		   RBPrint(myTree);
   	  		   RBCheck(myTree);
   	  		   }
   	  		   else {printf("\tThe word %s does not exist in the tree to be removed\n", word);
   	  		   RBPrint(myTree);
   	  		   RBCheck(myTree);}
   	  	   }
   	  	   else if(options == 1){
   	  		RBElement* n = Search(myTree,word);
   	  		   	  if (n == T_Nil){
   	  		        printf("Inserting %s\n", word);
   	  		     	RBInsert(myTree, word);
   	  	       	   }
   	  		   	  else {printf("\tThe word %s has already been inserted\n", word); } }
   	  	   else{
   	  		   printf("Wrong option: %d\n", options);
   	  	   }

   	       }


   	free(word);
   	word = NULL;

    fclose(fp);

 if (argc != 2) {
	      printf("Please, enter with correct parameters\n", argv[0]);
	      printf("Example: %s dictionary.txt\n", argv[0]);
	        return 0;
	    }

char line[MAXCHARACTERS];
RBElement* s;
printf("\n===================== INTERACTVE MODE ============================\n\n");

do {
	printf("Enter a word with a maximum of 20 characters: ");
	//stop = scanf("%s", line);
	gets(line);
	printf("%s\n", line);
	s = Search(myTree, line);
} while (strlen(line) != 0);

	  RBPrint(myTree);
	  RBCheck(myTree);

      RBFree(myTree);
      RBPrint(myTree);

	 return 0;

}





