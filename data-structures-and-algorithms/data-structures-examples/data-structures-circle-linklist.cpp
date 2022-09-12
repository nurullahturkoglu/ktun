#include <stdio.h>
#include <stdlib.h>

struct ogrenciler{
	
	int x;
	ogrenciler* next;
	
};

typedef ogrenciler ogr;

void bastir(ogr* r){

	ogr* iter = r;
	printf("%d ",iter->x);
	iter = iter->next;
	while(iter != r){
		printf("%d ",iter->x);
		iter = iter->next;
	}
	printf("\n");
}

ogr* ekle(ogr* r,int deger){

	ogr* iter = r;

	if(iter->next != r){

		iter = iter->next;
	}
	
	iter->next = (ogr*)malloc(sizeof(ogr));
	iter->next->x = deger;
	iter->next->next = r;
	return r;
	
}

ogr * ekleSirali(ogr* r,int deger){
	
	if(r == NULL){ // ilk eleman yoksa , gelen de�eri ilk eleman yap
		
		r = (ogr*)malloc(sizeof(ogr));
		r->x = deger;
		r->next = r; //circle
		return r;
		
	}else if (deger < r->x){ // gelen de�er ilk elemandan k���kse , gelen de�eri ilk eleman yap
		
		ogr * temp = (ogr*)malloc(sizeof(ogr));
		temp->x = deger;
		temp->next = r; // circle yaptık

		ogr * iter = r;
		while(iter->next != r); // son eleman artık r'yi değil temp'i göstermek zorunda (circle linklist)
			r = r->next;

		iter->next = temp; // son elemananın nexti tempi göstersin yaptık
		return temp;
		
	}
	
	ogr * iter = r;
	
	while( iter->next != r and iter->next->x < deger){ // "iter->next != r" = yapi tekrar r'yi gösterdiyse son elemana gelmiş ve sona eklenecektir.)
														  // "iter->next->x < deger" = araya ekleme ( gelen deger buyukse devam et , de�ilse dur!)
		
		iter = iter->next;
		
	}
		
	if(iter->next == r){  // sona geldiyse sona ekleme yap�yoruz
		
		iter->next = (ogr*)malloc(sizeof(ogr));
		iter->next->x = deger;
		iter->next->next = r;
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

		ogr * iter = r;

		while(iter->next != r){
			iter = iter->next;
		}

		iter->next = r->next;
		free(r);
		return iter->next;
		

	}

	ogr * iter = r;

	while(iter->next != r and iter->next->x != silinecekDeger){

		iter = iter->next;

	}
	if(iter->next == r){ // sona geldiyse sayı bulunamamistir. printf ile gosterilebilir.
		printf("aranan eleman bulunamadi\n");
		return r;
		
	}else{ // aradan silmede degisiklik yok

		ogr * temp = iter->next;
		iter->next = iter->next->next;
		free(temp);
		return r;

	}

}



int main(){
	
	ogr * root = NULL;
	ogr * dene = NULL;
	dene = ekle(dene,25);
	dene = ekle(dene,35);
	dene = ekle(dene,15);
	bastir(dene);
	
	/*root = ekleSirali(root,5); //Sirali ekleme fonksiyonu pointer turunden oldugundan return r dedigimizde esitlik gerektirir.
	root = ekleSirali(root,2);
	root = ekleSirali(root,7);
	root = ekleSirali(root,9);
	root = ekleSirali(root,8);
	root = ekleSirali(root,3);
	bastir(root);

	root = sil(root,3); // -> aradan silme
	bastir(root);
	root = sil(root,2); // -> baştan silme
	bastir(root);
	root = sil(root,9); // -> sondan silme
	bastir(root);
	root = sil(root,25);
	bastir(root);*/
	
	
	
	
	free(root);

	
	
}
