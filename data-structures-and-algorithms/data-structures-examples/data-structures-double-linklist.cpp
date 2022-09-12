#include <stdio.h>
#include <stdlib.h>

struct ogrenciler{
	
	int x;
	ogrenciler* next;
	ogrenciler* prev;
	
};

typedef ogrenciler ogr;

void bastir(ogr* r){
	
	while(r != NULL){
		printf("%d ",r->x);
		r = r->next;
	}
	printf("\n");
}

void bastirTersten(ogr* r){

	while(r->next != NULL)
		r = r->next;

	printf("%d ",r->x);
	while(r->prev != NULL){
		printf("%d ",r->prev->x);
		r = r->prev;
	}
	printf("\n");
}

void bastirTersten2(ogr* r){

	while(r ->next != NULL){

		r = r->next;
		printf("%d ",r->prev->x);
	}
	printf("\n");
}

ogr * ekleSirali(ogr* r,int deger){
	
	if(r == NULL){ // ilk eleman yoksa , gelen de�eri ilk eleman yap
		
		r = (ogr*)malloc(sizeof(ogr));
		r->x = deger;
		r->next = NULL;
		r->prev = NULL;
		return r;
		
	}else if (deger < r->x){ // gelen de�er ilk elemandan k���kse , gelen de�eri ilk eleman yap
		
		ogr * temp = (ogr*)malloc(sizeof(ogr));
		temp->x = deger;
		temp->next = r;
		temp->prev = NULL;
		r->prev = temp;

		return temp;
		
	}
	
	ogr * iter = r;
	
	while( iter->next != NULL and iter->next->x < deger){ // "iter->next != NULL" = sona geldiyse(ekleme yapaca��m�z i�in son elemandan �nce duruyoruz.)
														  // "iter->next->x < deger" = araya ekleme ( gelen deger buyukse devam et , de�ilse dur!)
		
		iter = iter->next;
		
	}
		
	if(iter->next == NULL){  // sona geldiyse sona ekleme yap�yoruz

		ogr * temp = iter->next;
		temp = (ogr*)malloc(sizeof(ogr));

		temp->x = deger;
		temp->next = NULL;
		temp->prev = iter;
		iter->next = temp;

		return r;
	}else{ // son durum olarak arada sayi ekleme kaldi  . araya ekleme yapiyoruz
		
		ogr * temp = (ogr*)malloc(sizeof(ogr));
		temp->x = deger;
		temp->next = iter->next; // �nce yeni de�erin nextini , iterin nexti yap
		temp->next->prev = temp;
		temp->prev = iter;
		iter->next = temp; // iterin nextini temp yap
		
		return r;
	}
}

ogr * sil(ogr* r,int silinecekDeger){

	if ( r->x == silinecekDeger ){ // silinecek değer ilk elemansa

		ogr * temp = r;
		r = r->next;
		r->prev = NULL;
		free(temp);
		return r;
		
	}

	ogr * iter = r;

	while(iter->next != NULL and iter->next->x != silinecekDeger){

		iter = iter->next;

	}
	if(iter->next == NULL){
		printf("silinecek olan %d sayisi bulunamadi\n",silinecekDeger);
		return r;
		
	}else{

		ogr * temp = iter->next;
		iter->next = temp->next;

		if(iter->next != NULL)
			temp->next->prev = iter;
		
		free(temp);
		return r;

	}

	

}



int main(){
	
	ogr * root;
	root = NULL;
	bastir(root);
	bastir(root);
	bastir(root);

	
	
}
