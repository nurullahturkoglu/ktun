import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/*
    Author: Nurullah Türkoğlu
    All content created by Nurullah Türkoğlu
 */

public class algOdev {

    int[][] graph2D;
    int len;

    public void initGraphModel(){

        try {

            Scanner scan = new Scanner(new BufferedReader(new FileReader("graf.txt")));
            List<Integer> gList = new ArrayList<>();

            while(scan.hasNextInt()){
                gList.add(scan.nextInt());
            }
            scan.close();

            this.len = (int)Math.sqrt(gList.size());
            graph2D = new int[len][len];
            int k=0;

            for(int row=0;row<len;row++)
                for(int col=0;col<len;col++)
                    graph2D[row][col] = gList.get(k++);

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    public void printGraph(){
        for(int row=0;row<len;row++){
            for(int col=0;col<len;col++){
                System.out.print(graph2D[row][col]+" ");
            }
            System.out.println("");
        }
        System.out.println("");
    }

    public void findGirisCikis(int n){

        if(n>=len && n < 0){
            System.out.println("dugum bulunamadi");
            return;
        }

        int giris = 0;
        int cikis = 0;

        for(int i = 0;i<len;i++){
            for(int j=0;j<len;j++){
                if(j == n && graph2D[i][j] != 0){
                    giris++;
                }
                if(i == n && graph2D[i][j] != 0){
                    cikis++;
                }
            }
        }
        System.out.println(n+". dugum'e giris derecesi:"+giris+" , cikis derecesi:"+cikis);
        System.out.println("");
    }

    public int findToplamKenar(){

        int kenar=0;
        for(int i=0;i<len;i++)
            for(int j=0;j<len;j++)
                if(graph2D[i][j] != 0)
                    kenar++;

        return kenar;
    }

    public void findKenarMaliyet(){

        int toplam =0;
        for(int i=0;i<len;i++)
            for(int j=0;j<len;j++)
                if(graph2D[i][j] != 0)
                    toplam += graph2D[i][j];

        System.out.println("Kenar maliyetleri toplamı:"+toplam);
        System.out.println("");
    }

    public void findKomsuveMaliyet(int n){

        if(n>=len && n < 0){
            System.out.println("dugum bulunamadi");
            System.out.println("");
            return;
        }

        int flag=0;
        int i=0;
        System.out.println(n+". düğümün komşuları:");
        while(i < len){
            if(graph2D[n][i] != 0){
                flag = 1;
                System.out.println(i+". dugum,maliyet:"+graph2D[n][i]);
            }
            i++;
        }
        if(flag == 0) System.out.print("bulunamadi");
        System.out.println("");

    }

    public boolean isFullyConnected(){

        if(findToplamKenar() == len * len)
            return true;

        return false;


    }

    public boolean isSymmetric(){

        for(int i=0;i<len;i++)
            for(int j=i+1;j<len;j++)
                if(graph2D[i][j] != graph2D[j][i])
                    return false;

        return true;
    }

    public static void main(String[] args) throws FileNotFoundException {

        algOdev graf1 = new algOdev();
        graf1.initGraphModel();
        Scanner read = new Scanner(System.in);
        int dugum;
        int sayi;

        while(true){

            System.out.printf("Matris icerigini listele(1)\nGiris-Cikis Hesapla(2)\nToplam Kenar Sayisi Bul(3)\n" +
                    "Toplam Kenar Maliyeti Bul(4)\nKomsu Dugum ve Kenar Maliyeti Hesapla(5)\n" +
                    "Grafin Tam Bagli Olup Olmadigini Ogren(6)\nGrafin Yonlu Olup Olmadigini Ogren(7)\nCikis Yap(8)\n" +
                    "Seciminiz:");
            sayi = read.nextInt();
            if(sayi == 8)
                break;

            switch (sayi){
                case 1:
                    graf1.printGraph();
                    break;

                case 2:
                    System.out.print("Hesaplanacak dugum:");
                    dugum = read.nextInt();
                    graf1.findGirisCikis(dugum);
                    break;

                case 3:
                    System.out.println("Toplam kenar sayisi:"+graf1.findToplamKenar());
                    System.out.println("");
                    break;

                case 4:
                    graf1.findKenarMaliyet();
                    break;

                case 5:
                    System.out.print("Hesaplanacak dugum:");
                    dugum = read.nextInt();
                    graf1.findKomsuveMaliyet(dugum);
                    break;

                case 6:
                    if(graf1.isFullyConnected())
                        System.out.println("Graf tam bagli");
                    else System.out.println("Graf tam bagli degil!");
                    System.out.println("");
                    break;

                case 7:
                    if(graf1.isSymmetric())
                        System.out.println("Graf -> Yonsuz");
                    else System.out.println("Graf -> Yonlu");
                    System.out.println("");
                    break;

            }
        }

    }

}


