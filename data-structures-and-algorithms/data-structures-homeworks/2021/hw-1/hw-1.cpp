#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    Author: Nurullah Türkoğlu
    All content created by Nurullah Türkoğlu
 */

struct Dugum {
 	int derece;
	int katSayi;
	struct Dugum* sonraki;
};

typedef Dugum polinom;

void bastir(polinom* r){ // listeyi görmek için ekstra bastir fonksiyonu
	
	while(r != NULL){
		printf("%d %d\n",r->derece,r->katSayi);
		r = r->sonraki;
	}
	printf("\n");
}


polinom * ekleSirali(polinom* r,int derece,int katsayi){

	polinom * ara = r;
	int flag = 0;

	while(ara != NULL){ // flag koyarak gelen derecenin daha önce olup olmadigini kontrol ediyoruz

		if(ara->derece == derece){
			flag = 1;
			break;
		}
		ara = ara->sonraki;
	}

	if(flag == 1){
		printf("eklemeye calistiginiz %d dereceli polinomu daha once eklediniz.\n",derece);
		return r;
	}else{

		if(r == NULL){ // ilk eleman yoksa , gelen dereceyi ilk eleman yap
			
			r = (polinom*)malloc(sizeof(polinom));
			r->derece = derece;
			r->katSayi = katsayi;
			r->sonraki = NULL;
			return r;
			
		}else if (derece > r->derece){ // gelen derece degeri ,ilk dereceden buyukse , gelen degeri ilk eleman yap
			
			polinom * temp = (polinom*)malloc(sizeof(polinom));
			temp->derece = derece;
			temp->katSayi = katsayi;
			temp->sonraki = r;
			return temp;
			
		}
		
		polinom * iter = r;
		
		while( iter->sonraki != NULL and iter->sonraki->derece > derece){ // "iter->sonraki != NULL" = sona geldiyse(ekleme yapacagimiz son elemandan once duruyoruz.)
																			// "iter->sonraki->derece > deger" = araya ekleme ( gelen deger kucukse devam et , degilse dur!)
			
			iter = iter->sonraki;
			
		}
			
		if(iter->sonraki == NULL){  // sona geldiyse en kucuk derece gelmiştir. Sona ekleme yapiyoruz
			
			iter->sonraki = (polinom*)malloc(sizeof(polinom));
			iter->sonraki->derece = derece;
			iter->sonraki->katSayi = katsayi;
			iter->sonraki->sonraki = NULL;
			return r;
		}else{ // son durum olarak araya ekleme kaldi . Gelen dereceyi araya ekleme yapiyoruz
			
			polinom * temp = (polinom*)malloc(sizeof(polinom));
			temp->derece = derece;
			temp->katSayi = katsayi;
			temp->sonraki = iter->sonraki; // once yeni degerin sonrakini , iterin sonraki yap
			iter->sonraki = temp; // iterin sonrakini temp yap
			return r;
		}
	}
}

polinom * sil(polinom* r,int silinecekDerece){

	if(r == NULL){ // liste bos ise
		printf("Liste bos\n");
		return r;
	}

	if ( r->derece == silinecekDerece ){ // silinecek derece ilk elemansa

		polinom * temp = r;
		r = r->sonraki;
		free(temp);
		return r;
		
	}

	polinom * iter = r;

	while(iter->sonraki != NULL and iter->sonraki->derece != silinecekDerece){

		iter = iter->sonraki;

	}
	if(iter->sonraki == NULL){ // silinecek derece bulunmadigi durum
		printf("silinecek olan %d dereceli polinom bulunamadi\n",silinecekDerece);
		return r;
		
	}else{ // silinecek derece arada ise

		polinom * temp = iter->sonraki;
		iter->sonraki = iter->sonraki->sonraki;
		free(temp);
		return r;

	}


}

void yazdirPolinom(polinom* r){

	if(r == NULL){
		printf("Liste bos\n");

	}else{
		printf("\n");
		polinom * iter = r;
		while(iter != NULL){
			printf("%d %d\n",iter->derece,iter->katSayi);
			iter = iter->sonraki;
		}
		
		polinom * temp = r;
		while(temp != NULL){
			if(temp->katSayi != 0){
				if(temp->sonraki == NULL){ 
					if(temp->katSayi >= 0){ // katsayi 0'dan kucukse - parantezine al if'i

						printf("%dX^%d",temp->katSayi,temp->derece);

					}else printf("(%d)X^%d",temp->katSayi,temp->derece);

				}else{ // eger yazilacak deger sondaysa + işareti koyma

					if(temp->katSayi >= 0){
						printf("%dX^%d + ",temp->katSayi,temp->derece);
					}else printf("(%d)X^%d + ",temp->katSayi,temp->derece);

				}

			}
				
			temp = temp->sonraki;
		}
		printf("\n");
	}
}

void hesaplaPolinom(polinom * r, int x){

	if(r == NULL){
		printf("Liste bos\n");

	}else{

		int sonuc = 0;

		polinom * iter = r;

		while(iter != NULL){
			
			sonuc += (iter->katSayi * pow(x,iter->derece));
			
			iter = iter->sonraki;

		}

		printf("bulunan sonuc: %d\n",sonuc);
	}
}

void dosyaYazdir(polinom * r){

	FILE * fp;
	fp = fopen("bagli_liste.txt","w");
	if(fp == NULL){
		printf("Dosya acilamadi");
		exit(1);

	}else{
		
		while(r != NULL){
			fprintf(fp,"%d %d\n",r->derece,r->katSayi);

			r = r->sonraki;
		}
		printf("dosya basariyla yazdilirdi\n");

	}

	fclose(fp);
}

/*int main(){ -> denemek icin olusturulmus main blogu
	
	polinom * root = NULL;
	
	//root = ekleSirali(root,5,-1);
	//root = ekleSirali(root,2,2);
	//root = ekleSirali(root,7,0);
	root = ekleSirali(root,9,4);
	//root = ekleSirali(root,8,4);
	//root = ekleSirali(root,7,4);
	bastir(root);
	root = ekleSirali(root,3,-6);
	bastir(root);
	yazdirPolinom(root,10);


	root = sil(root,3); // -> aradan silme
	bastir(root);
	//root = sil(root,2); // -> sondan silme
	bastir(root);
	root = sil(root,9); // -> bastan silme
	bastir(root);
	root = sil(root,15);  // -> olmayan derece

	yazdirPolinom(root,5);
	hesaplaPolinom(root,5);
	
	
	
	
	//bastir(root);
	free(root);
	
}*/

int main(){

	polinom * poli = NULL;
	int derece,katsayi,sayi,num;

	while(true){
		printf("\nEkleme(1)\nSilme(2)\nYazdirma(3)\nHesapla(4)\nCikis(5)\n");
		printf("Kullanmak istediginiz islemin yanindaki sayiyi giriniz: ");
		scanf("%d",&sayi);

		switch(sayi){

			case 1:
				printf("\nEkleme islemine hosgeldiniz.\nEklemek istediginiz polinomun derecesini giriniz: ");
				scanf("%d",&derece);
				printf("polinomun katsayisini giriniz:");
				scanf("%d",&katsayi);
				poli = ekleSirali(poli,derece,katsayi);
				break;
			
			case 2:
				printf("Silmek istediginiz polinomun derecesini giriniz: ");
				scanf("%d",&derece);
				poli = sil(poli,derece);
				break;

			case 3:
				yazdirPolinom(poli);
				break;

			case 4:
				printf("Hesaplamak istediginiz P(x)'in x degerini giriniz: ");
				scanf("%d",&num);
				hesaplaPolinom(poli,num);
				break;

			case 5:
				dosyaYazdir(poli);
				exit(0);
				break;

		}
	}

}