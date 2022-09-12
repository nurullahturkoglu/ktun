#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct veri_yapilari_stack
{
	int data;
	veri_yapilari_stack * next;

};

typedef veri_yapilari_stack stack;

stack * sayilar1 = NULL;
stack * sayilar2 = NULL;

stack* ekle(stack * r,int x){

	if( r == NULL ){

		r = (stack*)malloc(sizeof(stack));
		r->data = x;
		r->next = NULL;
		return r;

	}

	stack *temp = (stack*)malloc(sizeof(stack));
	temp->data = x;
	temp->next = r;
	return temp;

}


int cikar(stack ** r){

	if(*r == NULL){
		printf("liste bos\n");
		return -1;
	}else{
		
		if((*r)->next == NULL){
			int value = (*r)->data;
			*r = NULL;
			return value;
		}

		stack * temp = *r;
		int cikansayi = temp->data;
		*r = (*r)->next;
		free(temp);
		return cikansayi;
	}
}

void bas(stack * r){

	if(r == NULL){
		printf("liste bos\n");
	}else{

		while( r != NULL){

			printf("%d",r->data);
			r = r->next;

		}
	}
}

int boyutHesapla(stack * r){

	int boyut = 0;
	while(r != NULL){
		boyut++;
		r = r->next;
	}
	return boyut;

}

stack * sayilariTopla(stack * result1,stack * result2){ // -> res1 -> 4 hane / res2 -> 4+1 hane (res2 daha buyuk olarak yazilmis fonk)

	stack * sayilarintoplami = NULL;

	int result1uzunluk = boyutHesapla(result1); // kucuk olan hane result uzunlugunu aliyoruz

	sayilarintoplami = ekle(sayilarintoplami,cikar(&result1)); // 86415 sayisindan 5 olani direkt ekliyoruz (370530 + 86415 -> son hane direkt 5 olarak baslar)
	cikar(&result2); // 370530 sayisindan 0'ı atarak basliyoruz

	int v1;
	int v2;
	int elde = 0;
	int eklenecekdeger;
	int toplam;

	for(int i=0;i<result1uzunluk-1;i++){ // result1'den son sayiyi hali hazirda pop etmiştik dolayisiyla -1 alarak basliyoruz

		v1 = cikar(&result1);
		v2 = cikar(&result2);

		toplam = v1+v2;

		if(toplam >= 10){

			elde = toplam/10;
			eklenecekdeger = toplam%10;
			sayilarintoplami = ekle(sayilarintoplami,eklenecekdeger);

		}else{

			elde = 0; // toplanan sayilar 10dan kucukse eldeyi 0 yapiyoruz
			sayilarintoplami = ekle(sayilarintoplami,toplam);

		}
	}

	sayilarintoplami = ekle(sayilarintoplami,(cikar(&result2) + elde)); // en son result2 de kalan degeri de elde ile toplayarak pop yapip sayilarin toplamina ekliyoruz.
	
	return sayilarintoplami;


}

stack * sayilariCarp(char values1[],char values2[]){

	// char gelen ifadeleri link liste(stack) ekliyoruz
	for(int i =0 ; i<strlen(values1);i++){
		sayilar1 = ekle(sayilar1,values1[i]-48); // 48 -> ascii table 0 sayisina denk ( gelen ifade string oldugundan dolayı stacke int'e cevirip atıyoruz)
	}

	for(int i =0; i<strlen(values2);i++){
		sayilar2 = ekle(sayilar2,values2[i]-48);
	}

	int value1;
	int value2;
	int sayilar1boyut = boyutHesapla(sayilar1);
	int sayilar2boyut = boyutHesapla(sayilar2);
	int elde=0; // elde var degeri icin tutulan int
	stack * result = NULL;
	stack * result2 = NULL;
	result2 = ekle(result2,0);

	// stacke attıgımız ifadeleri pop ederek carpma islemine tabi tutacagiz
	for(int i = 0;i<sayilar2boyut;i++){

		value2 = cikar(&sayilar2);
		for(int j = 0;j<i;j++){ // alt alta toplama olacagi icin sayinin gizli 0larini ekliyoruz
			result = ekle(result,0);
		}

		for(int i = 0;i<sayilar1boyut;i++){

			value1 = cikar(&sayilar1);

			int carpimdegeri = value1*value2;
			carpimdegeri += elde; // eger elde varsa carpilan degere ekle

			
			if(carpimdegeri >= 10){

				elde = carpimdegeri / 10; // en son durumdaki carpim degerinden yeni elde tut
				int eklenecekdeger = carpimdegeri % 10;
				result = ekle(result,eklenecekdeger);
				if(i == sayilar1boyut-1) // stackin sonuna gelindiyse elde tutulan sayiyi da ekle
					result = ekle(result,elde);


			}else{
					
				elde = 0; // sayi 10'dan kucukse tutulan eldeyi 0 yap
				result = ekle(result,carpimdegeri);
					
			}

		}

		if(i != 0){
			result2 = sayilariTopla(result,result2);
		}else result2 = sayilariTopla(result2,result);


		//result stackini sonraki for icin bosaltma islemi
		for(int i = 0;i<boyutHesapla(result);i++){
			cikar(&result);
		}
		

	}

	return result2;

}

int main(){

	/* char sayilar1[50] = "5301858469230152002541253";
	char sayilar2[50] = "8"; // -> sonuc 42414867753841216020330024 */

	char sayilar1[50] = "5301";
	char sayilar2[50] = "4"; // -> sonuc 21204 */


	stack * result = sayilariCarp(sayilar1,sayilar2);
	bas(result);
	





	/* sayilar = ekle(sayilar,sayilar1[0]);
	sayilar = ekle(sayilar,sayilar1[1]);
	sayilar = ekle(sayilar,sayilar1[2]);
	sayilar = ekle(sayilar,sayilar1[3]);


	bas(sayilar);
	int value = boyutHesapla(sayilar);
	printf("value: %d\n",value);

	for(int i = 0;i<5;i++){
		printf("popped : %c\n",cikar(&sayilar));
	} */

	


}