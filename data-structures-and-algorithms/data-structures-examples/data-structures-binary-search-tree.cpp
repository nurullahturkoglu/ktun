#include <stdio.h>
#include <stdlib.h>

struct n{

	int data;
	n * sol;
	n * sag;

};

typedef n node;

node * agacaEkle( node * agac , int x){

	if( agac == NULL){
		agac = (node*)malloc(sizeof(node));
		agac->data = x;
		agac->sol = NULL;
		agac->sag = NULL;
		return agac;
	}
	if(agac->data < x){ // gelen deger agacın datasından buyukse
		agac->sag = agacaEkle(agac->sag,x);
		return agac;
	}

	agac->sol = agacaEkle(agac->sol,x); // gelen deger agacın datasından kucukse
	return agac;
	
	
}

void agactaDolas(node* agac){ // kucukten buyuge / LEFT - NODE - RIGHT

	if(agac==NULL)
		return;
	
	agactaDolas(agac->sol); // Sol agacın ; sol - node - sag
	printf("%d ",agac->data);
	agactaDolas(agac->sag); // Sag agacın ; sol - node - sag

}

int agactaAra(node * agac,int aranandeger){

	if(agac == NULL)
		return -1;
	
	if(agac->data == aranandeger)
		return 1;
	if(agactaAra(agac->sol,aranandeger) == 1)
		return 1;
	if(agactaAra(agac->sag,aranandeger) == 1)
		return 1;
	return -1;

}


int main(){
	
	node * binarytree = NULL;
	binarytree = agacaEkle(binarytree,5);
	binarytree = agacaEkle(binarytree,21);
	binarytree = agacaEkle(binarytree,-2);
	binarytree = agacaEkle(binarytree,6);
	binarytree = agacaEkle(binarytree,-4);
	binarytree = agacaEkle(binarytree,10);
	binarytree = agacaEkle(binarytree,8);
	binarytree = agacaEkle(binarytree,3);
	agactaDolas(binarytree);
	printf("\n");
	int any = 44;
	printf("agacta %d degeri bulundu mu: %d",any,agactaAra(binarytree,any));
	
}
