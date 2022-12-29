/*
    Author: Nurullah Türkoğlu
    All content created by Nurullah Türkoğlu
 */

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.*;

public class algOdev {

    int[][] graph2D;
    int len;
    List<String> res;

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

    public void solution(){

        Set<Integer> visited = new HashSet<>();
        HashMap<Integer,Integer> hm = new HashMap<>();
        Queue<Integer> que = new LinkedList<>();
        res = new ArrayList<>();

        que.add(8);
        hm.put(8,-1);

        while(!que.isEmpty()){
            int temp = que.poll();
            for(int i=0;i<len;i++){
                if(graph2D[temp][i] == 1 && !visited.contains(i)){
                    hm.put(i,temp);
                    que.add(i);
                }
            }
            visited.add(temp);
        }

        visited.clear();
        visited.add(8);
        for(int i=0;i<len;i++){

            if(!visited.contains(i)){

                String yolbul = "";
                int bitis = i;
                while(hm.get(bitis) != -1){
                    visited.add(bitis);
                    yolbul = "<-"+bitis + yolbul;
                    bitis = hm.get(bitis);
                }
                yolbul = "8" + yolbul;
                res.add(yolbul);

            }

        }

        for(String a : res){
            System.out.println(a);
        }

    }


    public static void main(String[] args) throws FileNotFoundException {

        algOdev graf1 = new algOdev();
        graf1.initGraphModel();
        graf1.solution();

    }

}


