#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 50
typedef int elemType;
typedef struct BitNode{
	elemType data;
	struct BitNode *lchild,*rchild;
}BitNode;
void createBTree(BitNode **T,elemType a[],int len,int index){
	if(index >= len)
		return;
	*T = (BitNode *)malloc(sizeof(BitNode));
	if(a[index] == -1)
		(*T) = NULL;
	else{
		(*T)->data = a[index];
		(*T)->lchild = NULL;
		(*T)->rchild = NULL;
		createBTree(&((*T)->lchild),a,len,2 * index + 1);
		createBTree(&((*T)->rchild),a,len,2 * index + 2);
	}
}
//层次遍历
void levelOrder(BitNode *T){
	BitNode *Q[MAXSIZE];
	int low = 0,high = 0;
	BitNode *p;
	Q[high++] = T;
	while(low != high){
		p = Q[low++];
		printf("%d ",p->data);
		if(p->lchild != NULL)
			Q[high++] = p->lchild;
		if(p->rchild != NULL)
			Q[high++] = p->rchild;
	}
}
//先序非递归
void preOrderNonRec(BitNode *T){
	BitNode *p = T;
	BitNode *S[MAXSIZE];
	int top = -1;
	while(p || top != -1){
		while(p){
			printf("%d ",p->data);
			S[++top] = p;
			p = p->lchild;
		}
		if(top != -1){
			p = S[top--];
			p = p->rchild;
		}
	}
}
//中序非递归
void inOrderNonRec(BitNode *T){
	BitNode *p = T;
	BitNode *S[MAXSIZE];
	int top = -1;
	while(p || top != -1){
		if(p){
			S[++top] = p;
			p = p->lchild;
		}
		else{
			p = S[top--];
			printf("%d ",p->data);
			p = p->rchild;
		}
	}
}
//后序非递归
void postOrderNonRec(BitNode *T){
	BitNode *p = T;
	BitNode *S[MAXSIZE];
	BitNode *r = NULL;
	int top = -1;
	while(p || top!= -1){
		if(p){
			S[++top] = p;
			p = p->lchild;
		}
		else{
			p = S[top];
			if(p->rchild && p->rchild != r){
				p = p->rchild;
				S[++top] = p;
				p = p->lchild;
			}
			else{
				p = S[top--];
				printf("%d ",p->data);
				r = p;
				p = NULL;
			}
		}
	}
}
int max(elemType a,elemType b){
	return a > b ? a : b;
}
//统计二叉树结点个数
int btNodeCount(BitNode *T){
	if(T == NULL)
		return 0;
	int left,right;
	left = btNodeCount(T->lchild);
	right = btNodeCount(T->rchild);
	return (left + right + 1);
}
//求二叉树高度
int btDepth(BitNode *T){
	int left,right;
	if(T == NULL)
		return 0;
	left = btDepth(T->lchild);
	right = btDepth(T->rchild);
	return (max(left,right) + 1);
}
//统计二叉树叶节点个数
int btLeafCount(BitNode *T){
	int left,right;
	if(T == NULL)
		return 0;
	if(T->lchild == NULL && T->rchild == NULL)
		return 1;
	left = btLeafCount(T->lchild);
	right = btLeafCount(T->rchild);
	return (left + right);
}
//统计双分支结点个数
int btDoubleSonCount(BitNode *T){
	int left,right;
	if(T == NULL)
		return 0;
	left = btDoubleSonCount(T->lchild);
	right = btDoubleSonCount(T->rchild);
	if(T->lchild != NULL && T->rchild != NULL)
		return (left + right + 1);
	else
		return (left + right);
}
int main(){
	elemType a[] = {1,2,3,4,5,6,7,-1,8,-1,-1,-1,9,-1,10};
	int len = sizeof(a)/sizeof(a[0]);
	BitNode *T;
	int depth,bt_leafCount,btNodes,dsonNode;
	createBTree(&T,a,len,0);
	levelOrder(T);
	printf("\n");
	preOrderNonRec(T);
	printf("\n");
	inOrderNonRec(T);
	printf("\n");
	postOrderNonRec(T);
	printf("\n");
	depth = btDepth(T);
	printf("BTree depth: %d\n",depth);
	bt_leafCount = btLeafCount(T);
	printf("BTree leaf count: %d\n",bt_leafCount);
	btNodes = btNodeCount(T);
	printf("BTree node count: %d\n",btNodes);
	dsonNode = btDoubleSonCount(T);
	printf("Double son node count: %d\n",dsonNode);
}
