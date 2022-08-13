import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

    public static void main(String[] args) throws IOException  {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution. */
        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
        String s=br.readLine().trim();
        StringTokenizer st=new StringTokenizer(s);
        int N=Integer.parseInt(st.nextToken());
        int M=Integer.parseInt(st.nextToken());
        BitSet bit1=new BitSet(N);
        BitSet bit2=new BitSet(N);
        while(M-->0)
        {
           s=br.readLine().trim();
           st=new StringTokenizer(s);
           String ins=st.nextToken();
           int a=Integer.parseInt(st.nextToken());
           int b=Integer.parseInt(st.nextToken());
           switch(ins)
           {
               case "AND":
                    if(a==1)
                         bit1.and(bit2);
                    else
                        bit2.and(bit1);
                    break;
               case "OR":
                    if(a==1)
                        bit1.or(bit2);
                    else
                        bit2.or(bit1);
                    break;
               case "XOR":
                    if(a==1)
                        bit1.xor(bit2);
                    else
                        bit2.xor(bit1);
                    break;
               case "FLIP":
                    if(a==1)
                        bit1.flip(b);
                    else
                        bit2.flip(b);
                    break;
               case "SET":
                    if(a==1)
                        bit1.set(b);
                    else
                        bit2.set(b);
                    break;

           }
           System.out.println(bit1.cardinality()+" "+bit2.cardinality());

        }

    }
}
