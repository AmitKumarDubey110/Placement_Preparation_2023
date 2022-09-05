import java.io.*;
import java.util.*;
interface PerformOperation {
 boolean check(int a);
}
class MyMath {
 public static boolean checker(PerformOperation p, int num) {
  return p.check(num);
 }

   // Write your code here
   
   public PerformOperation isOdd() {
  return (a) -> {
   return (a % 2 == 1);
  };
 }

public PerformOperation isPrime() {
  return (a) -> {
   for (int i = 2; i <= a / 2; i++) {
    if (a % i == 0)
     return false;
   }
   return true;
  };
 }
 public PerformOperation isPalindrome() {
  return (a) -> {
   int rev = 0;int r = 0;int n = a;
   while (n != 0) {
    r = n % 10;
    rev = rev * 10 + r;
    n /= 10;
   }
   return (rev == a);
  };
 }
}

public class Solution {

 public static void main(String[] args) throws IOException {
  MyMath ob = new MyMath();
  BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
  int T = Integer.parseInt(br.readLine());
  PerformOperation op;
  boolean ret = false;
  String ans = null;
  while (T--> 0) {
   String s = br.readLine().trim();
   StringTokenizer st = new StringTokenizer(s);
   int ch = Integer.parseInt(st.nextToken());
   int num = Integer.parseInt(st.nextToken());
   if (ch == 1) {
    op = ob.isOdd();
    ret = ob.checker(op, num);
    ans = (ret) ? "ODD" : "EVEN";
   } else if (ch == 2) {
    op = ob.isPrime();
    ret = ob.checker(op, num);
    ans = (ret) ? "PRIME" : "COMPOSITE";
   } else if (ch == 3) {
    op = ob.isPalindrome();
    ret = ob.checker(op, num);
    ans = (ret) ? "PALINDROME" : "NOT PALINDROME";

   }
   System.out.println(ans);
  }
 }
}
