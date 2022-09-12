#include <stdio.h>
#include <stdlib.h>


struct stack{

	int data;
	stack * next;

};


stack * ekleStack(stack *r,int x){ // stack yapısı klasik ekleme methodu

	if(r == NULL){

		r = (stack*) malloc(sizeof(stack));
		r->data = x;
		r->next = NULL;
		return r;

	}

	stack * iter = r;
	while(iter->next != NULL){
		iter = iter->next;
	}

	iter->next = (stack*) malloc(sizeof(stack));
	iter->next->data = x;
	iter->next->next = NULL;
	return r;

}

int  cikar(stack **r){

	if(r == NULL)
		printf("bos\n");

	if(r->next == NULL){
		int value = *r -> data;
		**r = NULL;
		return value;
	}

	stack * iter = *r;
	while(iter->next->next != NULL){
		iter = iter->next;
	}
	stack * temp = iter->next;
	int value = temp->data;
	iter->next = NULL;
	free(temp);
	return value;
	

}

void DecimalToBinary(stack * r,int decimalValue){

	// decimalValue = 41 --> 101001
	int toplam = 0;

	while(decimalValue != 0){

		int mod = decimalValue % 2;
		r = ekleStack(r,mod);
		decimalValue /= 2;
		toplam++;

	}
	for(int i = 0;i<toplam;i++){
		printf("cikarilan deger: %d\n",cikar(stack1));
	}
	puts("\n");

}

void bas(stack * r){

	if(r == NULL){
		printf("stack bos\n");
	}else{

		while(r != NULL){
			printf("%d ",r->data);
			r = r->next;
		}

		printf("\n");
	}

}

int main(){

	stack * stack1 = NULL;
	
	for(int i=0;i<5;i++){

		bas(stack1);
		stack1 = ekleStack(stack1,i*5);

	}

	for(int i=0;i<5;i++){

		
		printf("cikarilan deger: %d\n",cikar(*stack1));
		

	}

	

	

	

}