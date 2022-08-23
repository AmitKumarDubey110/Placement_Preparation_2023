import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

    public static void main(String[] args) {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution. */
        
        Scanner scan = new Scanner(System.in);
        
        try {
            int x = scan.nextInt();
            int y = scan.nextInt();
            System.out.println(x / y);
        } 
        catch(InputMismatchException e) {
            // ensure that "java.util.InputMismatchException" is printed only.
            System.out.println(e.getClass().toString().replaceFirst("class ", ""));
        }
        catch(ArithmeticException e) {
            // Print exception
            System.out.println(e);
        }
        scan.close();
    }
}
