#include <stdio.h>
#include <stdlib.h>

struct ogrenciler{
	
	int x;
	ogrenciler* next;
	
};

typedef ogrenciler ogr;

void bastir(ogr* r){
	
	while(r != NULL){
		printf("%d ",r->x);
		r = r->next;
	}
}

void ekle(ogr* r,int deger){

	if(r == NULL){
		r = (ogr*)malloc(sizeof(ogr));
		r->x = deger;
		r->next = NULL;
	}else{

		while(r->next != NULL){
			r = r->next;
		}
		r->next = (ogr*)malloc(sizeof(ogr));
		r->next->x = deger;
		r->next->next = NULL;
	
	}
	
}

ogr * ekleSirali(ogr* r,int deger){
	
	if(r == NULL){ // ilk eleman yoksa , gelen de�eri ilk eleman yap
		
		r = (ogr*)malloc(sizeof(ogr));
		r->x = deger;
		r->next = NULL;
		return r;
		
	}else if (deger < r->x){ // gelen de�er ilk elemandan k���kse , gelen de�eri ilk eleman yap
		
		ogr * temp = (ogr*)malloc(sizeof(ogr));
		temp->x = deger;
		temp->next = r;
		return temp;
		
	}
	
	ogr * iter = r;
	
	while( iter->next != NULL and iter->next->x < deger){ // "iter->next != NULL" = sona geldiyse(ekleme yapaca��m�z i�in son elemandan �nce duruyoruz.)
														  // "iter->next->x < deger" = araya ekleme ( gelen deger buyukse devam et , de�ilse dur!)
		
		iter = iter->next;
		
	}
		
	if(iter->next == NULL){  // sona geldiyse sona ekleme yap�yoruz
		
		iter->next = (ogr*)malloc(sizeof(ogr));
		iter->next->x = deger;
		iter->next->next = NULL;
		return r;
	}else{ // son durum olarak arada sayi ekleme kaldi  . araya ekleme yapiyoruz
		
		ogr * temp = (ogr*)malloc(sizeof(ogr));
		temp->x = deger;
		temp->next = iter->next; // �nce yeni de�erin nextini , iterin nexti yap
		iter->next = temp; // iterin nextini temp yap
		return r;
	}
}

ogr * sil(ogr* r,int silinecekDeger){

	if ( r->x == silinecekDeger ){ // silinecek değer ilk elemansa

		ogr * temp = r;
		r = r->next;
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
		iter->next = iter->next->next;
		free(temp);
		return r;

	}

	

}



int main(){
	
	ogr * root;
	root = NULL;
	
	root = ekleSirali(root,5); //Sirali ekleme fonksiyonu pointer turunden oldugundan return r dedigimizde esitlik gerektirir.
	root = ekleSirali(root,2);
	root = ekleSirali(root,7);
	root = ekleSirali(root,9);
	root = ekleSirali(root,8);
	root = ekleSirali(root,3);


	root = sil(root,3); // -> aradan silme
	root = sil(root,2); // -> baştan silme
	root = sil(root,9); // -> sondan silme
	root = sil(root,15);
	
	
	
	
	bastir(root);
	free(root);

	
	
}
