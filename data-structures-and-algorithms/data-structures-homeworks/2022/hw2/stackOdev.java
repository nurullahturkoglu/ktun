/*
    Author: Nurullah Türkoğlu
    All content created by Nurullah Türkoğlu
 */

import java.util.Stack;

public class stackOdev {


    public static void main(String[] args) {

        Stack<String> stack1 = new Stack<>();
        Stack<String> stack2 = new Stack<>();

//        String test_inp = "Kr4(OnNe(SOne3)2)2";
//        String test_inp = "Magara(OyHr)2";
//        String test_inp = "Hakan2Ev";
//        String test_inp = "Ha2Oy2Het3Magara4";
        String test_inp = "(Ha2Oy2)3";
        int len = test_inp.length();

        for(int i=0;i<len;i++){
            char c = test_inp.charAt(i);

            if(checkIsUpperCase(c)){
                String temp = ""+c;
                int j= i+1;
                while (j != len &&
                        !checkIsNumber(test_inp.charAt(j)) &&
                        !checkIsUpperCase(test_inp.charAt(j)) &&
                        !checkIsPharanthesis(test_inp.charAt(j))){

                    temp += test_inp.charAt(j);
                    j++;
                }
                temp += ":1";
                i = j-1;
                stack1.push(temp);
            }else if(checkIsNumber(c)){
                int num = Integer.valueOf(c)-48;
                if(stack2.isEmpty()){
                    String temp = stack1.pop();
                    StringBuilder s = new StringBuilder(temp);
                    String repeat = "";
                    int slen = s.length()-1;
                    while (slen >= 0){
                        if(checkIsNumber(s.charAt(slen))){
                            repeat = s.charAt(slen) + repeat;
                            s.deleteCharAt(slen);
                            slen--;
                        }else
                            break;
                    }
                    s.append(Integer.valueOf(repeat) * num);
                    stack1.push(s.toString());
                }else{
                    while(!stack2.isEmpty()){
                        String temp = stack2.pop();
                        StringBuilder s = new StringBuilder(temp);
                        String repeat = "";
                        int slen = s.length()-1;
                        while (slen >= 0){
                            if(checkIsNumber(s.charAt(slen))){
                                repeat = s.charAt(slen) + repeat;
                                s.deleteCharAt(slen);
                                slen--;
                            }else
                                break;
                        }
                        s.append(Integer.valueOf(repeat) * num);
                        stack1.push(s.toString());
                    }
                }
            }else if(c == '('){
                stack1.push("(");
            }else if(c == ')'){
                while(stack1.peek() != "("){
                    stack2.push(stack1.pop());
                }
                stack1.pop();
            }
        }

        System.out.println(stack1);

    }

    public static boolean checkIsUpperCase(char c){
        return (c >= 'A' && c <= 'Z' ) ? true : false;
    }

    public static boolean checkIsNumber(char c){
        return (c >= '0' && c <= '9' ) ? true : false;
    }

    public static boolean checkIsPharanthesis(char c){
        return (c == '(' || c == ')' ) true : false;           
    }

}

