import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;
import java.security.MessageDigest;
import java.util.Scanner;

public class Solution {

    public static void main( String[] args ) {
        /*
         * Enter your code here. Read input from STDIN. Print output to
         * STDOUT. Your class should be named Solution.
         */
        try {
            Scanner scanner = new Scanner( System.in );
            String word = scanner.nextLine();
            scanner.close();

            MessageDigest messageDigest = MessageDigest.getInstance( "SHA-256" );
            messageDigest.update( word.getBytes("UTF-8") );
            byte[] byteHash = messageDigest.digest();

            for ( byte b : byteHash ) {
                System.out.format( "%02x", b );
            }

        } catch ( Exception e ) {
            e.printStackTrace();
        }
    }
}
