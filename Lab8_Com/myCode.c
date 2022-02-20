#include <stdio.h>
#include <stdlib.h>

int parentData; 
int firstControl=1;

enum nodeclr {
  kirmizi,
  siyah
};

struct SyhKrmzNode {
  int data;
  int clr;
  struct SyhKrmzNode *link[2];
};

struct SyhKrmzNode *root = NULL;

// Create a kirmizi-siyah tree
struct SyhKrmzNode *createNode(int data) {
  struct SyhKrmzNode *temp;
  temp = (struct SyhKrmzNode *)malloc(sizeof(struct SyhKrmzNode));
  temp->data = data;
  temp->clr = kirmizi;
  temp->link[0] = temp->link[1] = NULL;
  return temp;
}

// Insert an node
void insertNode(int data) {
  struct SyhKrmzNode *stack[98], *ptr, *temp, *Ptr_X, *Ptr_Y;
  int dir[98], length = 0, index;
  ptr = root;
  if (!root) {
    root = createNode(data);
    return;
  }

  stack[length] = root;
  dir[length++] = 0;
  while (ptr != NULL) {
    if (ptr->data == data) {
      printf("izin verilmedi \n");
      return;
    }
    index = (data - ptr->data) > 0 ? 1 : 0;
    stack[length] = ptr;
    ptr = ptr->link[index];
    dir[length++] = index;
  }
  stack[length - 1]->link[index] = temp = createNode(data);
  while ((length >= 3) && (stack[length - 1]->clr == kirmizi)) {
    if (dir[length - 2] == 0) {
      Ptr_Y = stack[length - 2]->link[1];
      if (Ptr_Y != NULL && Ptr_Y->clr == kirmizi) {
        stack[length - 2]->clr = kirmizi;
        stack[length - 1]->clr = Ptr_Y->clr = siyah;
        length = length - 2;
      } else {
        if (dir[length - 1] == 0) {
          Ptr_Y = stack[length - 1];
        } else {
          Ptr_X = stack[length - 1];
          Ptr_Y = Ptr_X->link[1];
          Ptr_X->link[1] = Ptr_Y->link[0];
          Ptr_Y->link[0] = Ptr_X;
          stack[length - 2]->link[0] = Ptr_Y;
        }
        Ptr_X = stack[length - 2];
        Ptr_X->clr = kirmizi;
        Ptr_Y->clr = siyah;
        Ptr_X->link[0] = Ptr_Y->link[1];
        Ptr_Y->link[1] = Ptr_X;
        if (Ptr_X == root) {
          root = Ptr_Y;
        } else {
          stack[length - 3]->link[dir[length - 3]] = Ptr_Y;
        }
        break;
      }
    } else {
      Ptr_Y = stack[length - 2]->link[0];
      if ((Ptr_Y != NULL) && (Ptr_Y->clr == kirmizi)) {
        stack[length - 2]->clr = kirmizi;
        stack[length - 1]->clr = Ptr_Y->clr = siyah;
        length = length - 2;
      } else {
        if (dir[length - 1] == 1) {
          Ptr_Y = stack[length - 1];
        } else {
          Ptr_X = stack[length - 1];
          Ptr_Y = Ptr_X->link[0];
          Ptr_X->link[0] = Ptr_Y->link[1];
          Ptr_Y->link[1] = Ptr_X;
          stack[length - 2]->link[1] = Ptr_Y;
        }
        Ptr_X = stack[length - 2];
        Ptr_Y->clr = siyah;
        Ptr_X->clr = kirmizi;
        Ptr_X->link[1] = Ptr_Y->link[0];
        Ptr_Y->link[0] = Ptr_X;
        if (Ptr_X == root) {
          root = Ptr_Y;
        } else {
          stack[length - 3]->link[dir[length - 3]] = Ptr_Y;
        }
        break;
      }
    }
  }
  root->clr = siyah;
}

int treeCount(struct SyhKrmzNode *root)
{
    int extremum;
    if (root!=NULL)
    {
        /* Finding the heiglength of left subtree. */
        int LeftSide = treeCount(root->link[0]);
        /* Finding the heiglength of riglength subtree. */
        int rightSideCount = treeCount(root->link[1]);
        if (LeftSide > rightSideCount)
        {
            extremum = LeftSide + 1;
            return extremum;
        }
        else
        {
            extremum = rightSideCount + 1;
            return extremum;
        }
    }
}



void RNLevel(struct SyhKrmzNode *root, int level,int isRiglength)
{
    if (root != NULL) 
    {
       if (level == 1)
        {
                if(firstControl==1){
                	if(root->clr==1)
                    		printf("%d B",root->data);
                    	else
                    		printf("%d R",root->data);
                    firstControl=0;
                }
                else
                    if(isRiglength==1)
                    	if(root->clr==1)
                        	printf("%d B (%d R) ",root->data,parentData);
                        else	
                        	printf("%d R (%d R) ",root->data,parentData);
                        
                    else 
                        if(root->clr==1)
                        	printf("%d B (%d L) ",root->data,parentData);
                        else	
                        	printf("%d R (%d L) ",root->data,parentData);
        }
        else if (level > 1) 
        { 
            parentData = root->data;
            RNLevel(root->link[0], level-1,0);
            RNLevel(root->link[1], level-1,1);
        }		
    }
}

void InOrder(struct SyhKrmzNode* tree){
    if(tree==NULL)return;
    
    InOrder(tree->link[0]);
    printf("%d\n",tree->data);
    InOrder(tree->link[1]);
}


int main(){

int data;
scanf("%d",&data);
    while(data!=-1){
    	insertNode(data);
    	scanf("%d",&data);
    }
    
    InOrder(root);
    printf("\n");

    int heiglength = treeCount(root);
    for(int i= 1; i <= heiglength; i++)      
    {
        RNLevel(root,i,0);
        printf("\n");
    }


    return 0;
}



