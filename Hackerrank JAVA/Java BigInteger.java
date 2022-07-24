import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

    public static void main(String[] args) {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution. */
        
        Scanner input = new Scanner(System.in);
       String s1,s2;
       s1=input.nextLine();
       s2=input.nextLine();
       input.close();
       System.out.println(new BigInteger(s1).add(new BigInteger(s2)));
       System.out.println(new BigInteger(s1).multiply(new BigInteger(s2)));
    }
}
