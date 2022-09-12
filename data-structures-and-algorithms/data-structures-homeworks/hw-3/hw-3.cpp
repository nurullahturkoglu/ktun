#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10

typedef struct{

    int ogr_no;
    char ad[20];
    int notu;

}Ogrenci;

Ogrenci veri_liste[MAX_SIZE];
int hash_tablo[MAX_SIZE][2];

void tabloyuBaslat(){

    for(int i =0; i<MAX_SIZE ; i++){
        
        for(int j =0; j < 2 ; j++){
            hash_tablo[i][j] = -1;
        }
    }

    for(int i =0; i<MAX_SIZE;i++){

        veri_liste[i].notu = -1;
        veri_liste[i].ogr_no = -1;

    } 
}

int Hash(int ogr_notu){

    return ogr_notu % MAX_SIZE;
}
// hash_tablo[x][0] = not
// hash_tablo[x][1] = next

void ogrenciEkle(int ogr_no , char * ad , int notu){

    int hash_index = Hash(notu);

    if( hash_tablo[hash_index][0] == -1 ){ // not degeri tanimlanmamis ise bostur -> direkt kaydet

        hash_tablo[hash_index][0] = notu;
        
        veri_liste[hash_index].ogr_no = ogr_no;
        strcpy( veri_liste[hash_index].ad , ad);
        veri_liste[hash_index].notu = notu;
        printf("%s isimli ogrenci eklendi!\n",ad);

    }else{ // o indekse not tanimlanmis ise collision meydana gelir

        int flag = 1;
        for(int i=0;i<MAX_SIZE;i++){

            if(hash_tablo[i][0] == -1){ // hash tablosunun i. degerinin notu bos ise
                flag = 0;
                hash_tablo[i][0] = notu; // i. indekse notu ekle

                veri_liste[i].ogr_no = ogr_no;
                strcpy( veri_liste[i].ad , ad);
                veri_liste[i].notu = notu;
                printf("%s isimli ogrenci eklendi!\n",ad);

                if(hash_tablo[hash_index][1] == -1){ // i. indeksin nexti baska yeri gostermiyor ise
                    
                    hash_tablo[hash_index][1] = i; // hash_index'in nexti i'yi gostersin

                }else{ // baska yeri gosteriyorsa
                    
                    int sonraki_index = hash_tablo[hash_index][1]; // sonraki indeksi tut
                    while( hash_tablo[sonraki_index][1] != -1){

                        if(hash_tablo[sonraki_index][0] != -1){

                            if( hash_tablo[sonraki_index][1] == -1){
                                hash_tablo[sonraki_index][1] = i;
                            }
                                
                            sonraki_index = hash_tablo[sonraki_index][1];

                        }  

                    }
                    
                    hash_tablo[sonraki_index][1] = i; // onceki satirin sonraki indeksi , ekleme yaptigimiz satiri gostersin
                }
               // printf("%d notu eklendi2\n",notu);
                break;
            } 
        }  

        if(flag == 1)
            printf("Ekleme yapilamadi , tablo dolu!\n");

    }

}


void ogrenciEkleSade(int notu){

    int hash_index = Hash(notu);

    if( hash_tablo[hash_index][0] == -1 ){ // not degeri tanimlanmamis ise bostur -> direkt kaydet

        hash_tablo[hash_index][0] = notu;
        printf("%d notu eklendi\n",notu);


    }else{ // o indekse not tanimlanmis ise collision meydana gelir
        int flag = 1;
        for(int i=0;i<MAX_SIZE;i++){

            if(hash_tablo[i][0] == -1){ // hash tablosunun i. degerinin notu bos ise
                flag = 0;
                hash_tablo[i][0] = notu; // i. indekse notu ekle

                if(hash_tablo[hash_index][1] == -1){ // i. indeksin nexti baska yeri gostermiyor ise
                    
                    hash_tablo[hash_index][1] = i; // hash_index'in nexti i'yi gostersin

                }else{ // baska yeri gosteriyorsa
                    
                    int sonraki_index = hash_tablo[hash_index][1]; // sonraki indeksi tut
                    while( hash_tablo[sonraki_index][1] != -1){

                        if(hash_tablo[sonraki_index][0] != -1){

                            if( hash_tablo[sonraki_index][1] == -1){
                                hash_tablo[sonraki_index][1] = i;
                            }
                                
                            sonraki_index = hash_tablo[sonraki_index][1];

                        }  

                    }
                   
                    hash_tablo[sonraki_index][1] = i; // onceki satirin sonraki indeksi , ekleme yaptigimiz satiri gostersin
                }

                printf("%d notu eklendi2\n",notu);
                break;
            } 
        }  

        if(flag == 1)
            printf("Ekleme yapilamadi , tablo dolu!\n");

    }

}

void tabloyuYazdir(){

    for(int i =0;i<MAX_SIZE;i++){
        printf("\t%d\t %d  |  %d\n",i,hash_tablo[i][0],hash_tablo[i][1]);
    }
}

int tablodaAra(int notu){

    int hash_index = Hash(notu);
    int toplam = 0;

    if(hash_tablo[hash_index][0] == -1){ // o indiste eleman yoksa , aranan deger bulunamamistir
        return -1;
    }else{

        if(hash_tablo[hash_index][0] == notu){ // ilk bakilan indekste ise
            
            printf("%d %s %d ogrenciye %d adimda ulasildi\n",veri_liste[hash_index].ogr_no,veri_liste[hash_index].ad,veri_liste[hash_index].notu,toplam+1);
            return ++toplam;

        }else{
            
            if(hash_tablo[hash_index][1] != -1){ // ilk bakilan indekste degil ise nextine bak

                toplam++;
                int sonraki_index = hash_tablo[hash_index][1];
                while(sonraki_index != -1){ // sonraki index -1 degil iken notlari kontrol et

                    if(hash_tablo[sonraki_index][0] == notu){
                        printf("%d %s %d ogrenciye %d adimda ulasildi!\n",veri_liste[sonraki_index].ogr_no,veri_liste[sonraki_index].ad,veri_liste[sonraki_index].notu,toplam+1);
                        return ++toplam;
                    }

                    toplam++;
                    sonraki_index = hash_tablo[sonraki_index][1];

                }

                if(hash_tablo[sonraki_index][0] == notu){ // while dongusunden ciktiysa o anki notu da kontrol et
                    printf("%d %s %d ogrenciye %d adimda ulasildi!\n",veri_liste[sonraki_index].ogr_no,veri_liste[sonraki_index].ad,veri_liste[sonraki_index].notu,toplam+1);
                    return ++toplam;
                }else return -1;

            }else return -1;
            
        }

    }

}

void ogrBilgileriListele(){

    for(int i =0;i<MAX_SIZE;i++){
        
        printf("\t%d\t- ",i);
        if(veri_liste[i].ogr_no != -1){
            printf("   %s  %d  %d\n",veri_liste[i].ad,veri_liste[i].ogr_no,veri_liste[i].notu);
        }else printf("\n");
            
    }

}

void txtEkle(){

    FILE * veri = fopen("veri.txt","r");
    if(veri == NULL){
        printf("dosya okunamadi!\n");
        fclose(veri);
        return;
    }
    int ogr_no;
    char isim[20];
    int notu;

    while(!feof(veri)){
        fscanf(veri,"%d %s %d\n",&ogr_no,isim,&notu);
        ogrenciEkle(ogr_no,isim,notu);
    }
    printf("Ogrenciler TXT dosyasindan basariyla okundu!\n");

    fclose(veri);
}

/* int main(){

    
    tabloyuBaslat();
    //tabloyuYazdir();

    /* ogrenciEkleSade(25);
    tabloyuYazdir();
    ogrenciEkleSade(40);
    tabloyuYazdir();
    ogrenciEkleSade(83);
    tabloyuYazdir();
    ogrenciEkleSade(31);
    tabloyuYazdir();
    ogrenciEkleSade(35);
    tabloyuYazdir();
    ogrenciEkleSade(37);
    tabloyuYazdir();
    ogrenciEkleSade(85);
    tabloyuYazdir();
    ogrenciEkleSade(55);
    tabloyuYazdir();
    ogrenciEkleSade(95);
    tabloyuYazdir();
    ogrenciEkleSade(21);
    tabloyuYazdir();
    ogrenciEkleSade(99);
    tabloyuYazdir(); 

   

    int ogr_no;
    char isim[20];
    int notu;

    printf("ogr no: ");
    scanf("%d",&ogr_no);
    fflush(stdin);
    printf("isim: ");
    gets(isim);
    printf("not: ");
    scanf("%d",&notu);

    ogrenciEkle(ogr_no,isim,notu);

    int ara = 55;
    
    if(tablodaAra(ara) != -1){

    }else printf("%d sonucu tabloda bulunamadi!\n",ara);


} */

int main(){

    tabloyuBaslat();
    int ogr_no;
    int notu;
    int sayi;
    int ara;

    while(true){
		printf("\nTXT Dosyadan Ogrenci Ekleme(1)\nManuel Ogrenci Ekleme(2)\nOgrenci Bilgilerini Listele(3)\nHash Tablosunu Listele(4)\nOgrenci Notu Ara(5)\nCikis(6)\n");
		printf("Kullanmak istediginiz islemin yanindaki sayiyi giriniz: ");
		scanf("%d",&sayi);
        if(sayi != 6){

            switch(sayi){

			case 1:
				
                txtEkle();
				break;
			
			case 2:
                char isim[20];
				printf("\nEkleme islemine hosgeldiniz.\nOgrenci no. : ");
                scanf("%d",&ogr_no);
                fflush(stdin);
                printf("Isim : ");
                gets(isim);
                fflush(stdin);
                printf("Not : ");
                scanf("%d",&notu);
                fflush(stdin);

                ogrenciEkle(ogr_no,isim,notu);
				break;

			case 3:
				ogrBilgileriListele();
				break;

			case 4:
				tabloyuYazdir();
				break;

			case 5:

				printf("\nArama islemine hosgeldiniz.\nAramak istediginiz notu giriniz : ");
                scanf("%d",&ara);
                if(tablodaAra(ara) == -1)
                    printf("bulunamadi!\n");
                break;
		    }

        }else break;

	}
}