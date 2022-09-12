#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <cstring>

#define N 25
int diziSayi[N];
char diziKarakter[N];
int indisINT = -1;
int indisCH = -1;

int intDiziBos(){

    if(indisINT == -1){
        return 1;
    }
    else return 0;

}

int intDiziDolu(){

    if(indisINT >= N){
        return 1;
    }else return 0;

}

char charDiziBos(){
    if(indisCH== -1)
        return 1;

    else return 0;
}

char charDiziDolu(){

    if(indisCH >= N){
        return 1;
    }return 0;

}

void ekleSayi(int dizi[] , int sayi){

    if(intDiziDolu()){

        printf("stack dolu");

    }else{

        dizi[++indisINT] = sayi;

    }
}

void ekleCh(char dizi[] , char ch){

    if(indisCH >= N){

        printf("stack dolu");

    }else{

        dizi[++indisCH] = ch;

    }
}


int cikarSayi(int dizi[]){

    if(intDiziBos()){

        return -1;

    }else{

        int value = dizi[indisINT];
        indisINT--;
        return value;

    }
}

char cikarCh(char dizi[]){

    if(indisCH == -1){
        
        return CHAR_MIN;

    }else{

        int chvalue = dizi[indisCH];
        indisCH--;
        return chvalue;

    }
}

void diziBasSayi(){

    if( indisINT == -1){
        printf("dizi bos");
    }else{

        for(int i = indisINT ;i>=0 ; i--){
            printf("%d\n",diziSayi[i]);
        }
    }
    printf("\n");

}


void diziBasCh(){

    if( indisCH == -1 ){
        printf("dizi bos");
    }else{

        for(int i = indisCH ; i>=0; i--){
            printf("%c\n",diziKarakter[i]);
        }
    }
    printf("\n");

}

int arrayLenght(char ch[]){
    
    int uzunluk = 0;

    for(int i = 0; ch[i] != '\0';i++){
        uzunluk++;
    }

    return uzunluk;

}

int parantezKontrolu(char dizi[]){

    int uzunluk = arrayLenght(dizi);
    int sayac =  0;

    for(int i = 0;i<uzunluk;i++){

        if(dizi[i] == '['){ // gelen ac parantez ise sayaci artir

             sayac++;
                
        }else{

            if(dizi[i] == ']'){ // gelen kapa parantez ise , sayaci kontrol et , 0 ise hata dondur degilse parantez bitmiştir(sayacı azalt)

                if(sayac == 0){
                    return -1;

                }else{

                sayac--;

                }

            }
        }
    }

    if(sayac != 0)// kontrolden sonra sayac 0'dan farkliysa '[' kalmistir. hata dondur
        return 0;
    else
        return 1;

}

/* char* subString(char gelen[],int bas,int son){

    char *donen = (char*) malloc(sizeof(char)*(son-bas+1));

    for(int i = bas; i<son+1 ;i++){

        donen[i-bas] = gelen[i];
    
    }
    donen[son+1] = '\0';
    printf("%s\n",donen);

    return donen;

} */

char * cogalticiFonksiyon(char dizi[],int adet){


    int uzunluk = arrayLenght(dizi);
    char * sonuc = (char*)malloc(sizeof(char)*(adet*uzunluk));
    int a = 0;

    for(int i = 0 ; i<adet ; i++){
        for(int j = 0;j<uzunluk;j++){
            sonuc[a] = dizi[j];
            a++;
        }
    }

    sonuc[a] = '\0';
    return sonuc;
}


char* donusturucu(char gelen[]){


    char *donen = (char*) malloc(sizeof(char)*30);
    int uzunluk = arrayLenght(gelen);
    int parantezhata = 0;

    for(int i = 0; i<uzunluk ; i++){

        if(gelen[i] == '['){  // -> parantez hatasi kontrolu 2[a3[]] -> parantez ici bosluk??

            if(gelen[i+1] == ']'){
                
                parantezhata = 1;

            }

        }

        if( (gelen[i] >= 48 && gelen[i] <= 57) && (gelen[i+1] == '[') ){ // -> gelen sayi ise ve sonraki '[' ise sayi stackina at ( 2[ab3cd] )

            ekleSayi(diziSayi,gelen[i]-48);

        }else{

            ekleCh(diziKarakter,gelen[i]);

        }

    }

    if(parantezhata != 1){

        // stacktan okuma kısma
        int sayac = 0;
        
        for(int i = indisCH ; i>=0;i--){ // [ab[d]]

            
            char okunandeger = cikarCh(diziKarakter);
            //printf("okunan deger: %c\n",okunandeger);

            if(okunandeger == ']') continue;

            if(okunandeger != '['){

                donen[sayac] = okunandeger;
                donen[sayac+1] = '\0';
                //printf("donen: %s sayac: %d\n",donen,sayac);
                sayac++;
                

            }if(okunandeger == '['){
                
                int adet = cikarSayi(diziSayi);
                
                donen = cogalticiFonksiyon(donen,adet);
                sayac = arrayLenght(donen);
                //printf("donen[[[]]]: %s sayac: %d\n",donen,sayac);
            
            }

        }

        //donen[sayac]= '\0';
        return donen;
        
    }else{
        printf("parantez hatasi");
        return 0;
    }


}



int main(){


    //char dene[50] = "2[aa5t]"; // -> t5aat5aa
    //char dene[50] = "2[ab3[d]]"; // -> dddbadddba
    //char dene[50] = "2[]"; // -> hata?
    //char dene[50] = "2[asd]]"; // -> hata?
    //char dene[50] = "3[e2[ab]]"; // -> babaebabaebabae
    //char dene[50] = "3[d]"; // -> ddd
    
    int value = parantezKontrolu(dene);
    if(value == 1){

        char * sonuc = donusturucu(dene);
        printf("\n%s\n",sonuc);

    }else{

         printf("parantez hatasi");
    }

    
}