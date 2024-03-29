import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {
    
    

    public static void insertIntoSorted(int[] ar) 
    {
        int numToInsert = ar[ar.length-1];
        int pos = ar.length-2;
        while(pos>=0){
            if(ar[pos]>numToInsert){
                ar[pos+1]=ar[pos];
                pos--;
                printArray(ar);
                
            }else{
                ar[pos+1]=numToInsert;
                printArray(ar);
                break;
            }
        }
        if(pos == -1){
            ar[0]=numToInsert;
            printArray(ar);
        }
        
    }
    
    
/* Tail starts here */
     public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int s = in.nextInt();
        int[] ar = new int[s];
         for(int i=0;i<s;i++){
            ar[i]=in.nextInt(); 
         }
         insertIntoSorted(ar);
    }
    
    
    private static void printArray(int[] ar) {
      for(int n: ar){
         System.out.print(n+" ");
      }
        System.out.println("");
   }
    
    
}
