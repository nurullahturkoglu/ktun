#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10
#define MAX_NAME 256

typedef struct node{

	char isim[MAX_NAME];
	int index;
	node * next;

}node;

typedef struct _Tablo{

	node satirlar[MAX_SIZE];
}Tablo;

Tablo hash_table;

void tabloyuBaslat(){

	for(int i = 0;i<MAX_SIZE;i++){
		hash_table.satirlar[i].index = -1;
		//strcpy("0",hash_table.satirlar[i].isim);
		//hash_table.satirlar[i].isim[i]= '\0';
		hash_table.satirlar[i].next = NULL;
	}

}


int lenghtOfChar(char* isim){ // İsimleri ascii karakter tablosundaki sayi karsiliklarina gore yazdirip toplayan fonksiyon

	int uzunluk = strlen(isim);
	unsigned int toplam = 0;
	for(int i = 0;i<uzunluk;i++){

		toplam += isim[i];
		// ayrica biraz daha gelistirip ifadeyi ascii sayisi ile carpabiliriz
		toplam *= isim[i];
		printf("%c : %d -> %u\n",isim[i],isim[i],toplam);

	}
	return toplam % MAX_SIZE;
}


unsigned int Hash(char* isim){ // İsimleri ascii karakter tablosundaki sayi karsiliklarina gore yazdirip toplayan fonksiyon

	int uzunluk = strlen(isim);
	int toplam = 0;
	for(int i = 0;i<uzunluk;i++){
		toplam += isim[i];
	}
	return toplam % MAX_SIZE;
}

void ekleLinkList(node * liste , node * index){
	
	node * iter = index;

	while(iter->next != NULL){
		iter = iter->next;
	}
	iter->next = liste;
	liste->next = NULL;

}

void ekle(char * isim){

	int sayi_index = Hash(isim);

	if(hash_table.satirlar[sayi_index].index == -1){

		hash_table.satirlar[sayi_index].index = sayi_index;
		strcpy(hash_table.satirlar[sayi_index].isim , isim);

	}else{ // collision varsa

		node * temp = (node*) malloc(sizeof(node));
		temp->index = sayi_index;
		strcpy(temp->isim ,isim);
		ekleLinkList(temp,&hash_table.satirlar[sayi_index]);

	}
}

void araHashTablosunda(char * isim){

	int sayi_index = Hash(isim);
	if(hash_table.satirlar[sayi_index].index != -1){

		if( strcmp(hash_table.satirlar[sayi_index].isim,isim) == 0 ){ // strcmp aynı ise 0 dondurur
			printf("%s hash tablosunda %d. indekste bulundu\n",isim,sayi_index);
		}else{

			node * temp = hash_table.satirlar[sayi_index].next;
			int flag = 1;
			while(temp != NULL){
				if( strcmp(temp->isim,isim) == 0 ){
					printf("%s hash tablosunda %d. indekste bulundu\n",isim,temp->index);
					flag = 0;
				}
				temp = temp->next;
			}
			if(flag == 1)
				printf("%s hash tablosunda bulunamadi!\n",isim);
		}

	}else{
		printf("%s hash tablosunda bulunamadi!\n",isim);
	}

}

void tabloyuListele(){

	char bos[] = "";
	for(int i = 0;i<MAX_SIZE;i++){
		if(hash_table.satirlar[i].index != -1){
			
			int flag = 1;
			printf("\t%d ---- %s",i,hash_table.satirlar[i].isim);
			node * temp = hash_table.satirlar[i].next;
			while(temp != NULL){
				flag = 0;
				if(strcmp(temp->isim,bos) != 0 )
					printf(" -- %s",temp->isim);
				temp = temp->next;
			}
			printf("\n");

		}else{
			printf("\t%d ---- \n",i);
		}
	}
}

void sil(char * isim){

	int sayi_index = Hash(isim);
	char bos[] = "";

	if(hash_table.satirlar[sayi_index].index == -1){ // indekste herhangi bir kayit yoksa direkt cik
		printf("%s hash tablosunda bulunamadi!\n",isim);
		return;
	}

	if( hash_table.satirlar[sayi_index].next == NULL && hash_table.satirlar[sayi_index].index != -1){ // o indekste sadece 1 tane kayit varsa

		if( strcmp(hash_table.satirlar[sayi_index].isim,isim ) == 0 ){
			hash_table.satirlar[sayi_index].index = -1;
			strcpy(hash_table.satirlar[sayi_index].isim , bos); // isim temizleme
			printf("%s hash tablosundan silindi\n",isim);
		}else printf("%s hash tablosunda bulunamadi!\n",isim);
		
	}else if (hash_table.satirlar[sayi_index].index != -1){ // indekste birden fazla kayıt varsa

		/* printf("%s sonucun hash table next'i nulldan farkli\n", isim); */
		
		if(strcmp(hash_table.satirlar[sayi_index].isim , isim) == 0){ // indekste birden fazla kayit varsa VE ilk kayıt silinmeye calisiliyorsa

			node * iter = hash_table.satirlar[sayi_index].next;
			strcpy(hash_table.satirlar[sayi_index].isim,iter->isim); // once 2. kayiti 1. kayita kopyalama
			while(iter->next != NULL){ // daha fazla kayıt varsa soldan saga dogru kopyalama
				strcpy(iter->isim,iter->next->isim);
				iter = iter->next;
			}
			strcpy(iter->isim , bos); // son kayıdı bosa cikartma
			printf("%s hash tablosundan silindi\n",isim);

			return;
			
		}

		node * iter = hash_table.satirlar[sayi_index].next;
		if(iter->next == NULL && strcmp(iter->isim,isim) == 0 ){ // iki kayıt varsa ve 2.si silinmeye calisiliyorsa
			hash_table.satirlar[sayi_index].next = NULL;
			printf("%s hash tablosundan silindi\n",isim);
			return;
		}
			
		if(strcmp(iter->isim,isim) == 0){ // 3 kayit varsa ve 2. kayıt silinmeye calisiliyorsa
			hash_table.satirlar[sayi_index].next = iter->next;
			printf("%s hash tablosundan silindi\n",isim);
			return;
		}

		while( iter->next != NULL && strcmp(iter->next->isim,isim) != 0 ){ // sona kadar git ve isimleri karsilastir
			iter = iter->next;
		}

		if(iter->next == NULL){ // sona geldiysen bulunamadi
			printf("%s hash tablosunda bulunamadi!\n",isim);
			return;
		}

		// arada bulunduysa swap yap
		node * temp = iter->next;
		iter->next = temp->next;
		free(temp);
		printf("%s hash tablosundan silindi\n",isim);
		return;
		
	}
}

	

int main(){

	tabloyuBaslat();

	char ahmet[] = "ahmet";
	char mehmet[] = "mehmet";
	char kerem[] = "kerem";
	char husamettin[] = "husamettin";
	char mustafa[] = "mustafa";
	char musa[] = "musa";
	char cetin[] = "cetin";
	char alihan[] = "alihan";
	char ayse[] = "ayse";
	char sedat[] = "sedat";
	char emin[] = "emin";
	char salih[] = "salih";
	char muhammet[] = "muhammet";
	char selen[] = "selen";
	char sude[] = "sude";
	char zahide[] = "zahide";
	char eren[] = "eren";
	char saadettin[] = "saadettin";

	
	ekle(musa);
	ekle(cetin);
	ekle(husamettin);
	ekle(ahmet);
	ekle(mehmet);
	ekle(kerem);
	ekle(alihan);
	ekle(ayse);
	ekle(mustafa);
	ekle(sedat);
	ekle(emin);
	ekle(muhammet);
	ekle(selen);
	ekle(sude);
	ekle(zahide);
	ekle(eren);
	ekle(eren);
	ekle(eren);
	ekle(eren);
	ekle(alihan);
	ekle(eren);
	ekle(musa);
	ekle(mustafa);

	tabloyuListele();

	
	
	sil(selen);
	tabloyuListele();
	sil(eren);
	tabloyuListele();
	
	sil(musa);
	tabloyuListele();
	sil(musa);
	tabloyuListele();
	sil(musa);
	tabloyuListele();
	/* sil(sedat);
	tabloyuListele();  */
	sil(mustafa);
	tabloyuListele();
	sil(sedat);
	tabloyuListele();
	sil(alihan);
	tabloyuListele();
	

	
}



