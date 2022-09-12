#include <stdio.h>
#include <stdlib.h>

struct veri_yapilari_stack
{
	int data;
	veri_yapilari_stack * next;

};

typedef veri_yapilari_stack stack;

stack* ekle(stack * r,int x){

	if( r == NULL ){

		r = (stack*)malloc(sizeof(stack));
		r->data = x;
		r->next = NULL;
		return r;
	}
	stack *iter = r;

	while(iter->next != NULL){

		iter = iter->next;

	}
	iter->next = (stack*)malloc(sizeof(stack));
	iter->next->data = x;
	iter->next->next = NULL;
	return r;

}


int cikar(stack ** r){

	if(*r == NULL){
		printf("liste bos");
		return -1;
	}else{
		
		if((*r)->next == NULL){
			int value = (*r)->data;
			*r = NULL;
			return value;
		}
		stack *iter = *r;
		while(iter->next->next != NULL){
			iter = iter->next;
		}

		stack * temp = iter->next;
		int cikansayi = temp->data;
		iter->next = NULL;
		free(temp);
		return cikansayi;
	}
}

void bas(stack * r){

	if(r == NULL){
		printf("liste bos\n");
	}else{

		while( r != NULL){

			printf("%d ",r->data);
			r = r->next;

		}
		printf("\n");
	}
}

int main(){

	stack * root = NULL;


	for(int i = 10;i<15;i++)
		root = ekle(root,i*10);
	
	bas(root);
	
	for(int i = 1;i<6;i++)
		printf("cikartilan deger: %d\n",cikar(&root));

	cikar(&root);
	bas(root);

	for(int i = 5;i<10;i++)
		root = ekle(root,i*10);

	bas(root);
}