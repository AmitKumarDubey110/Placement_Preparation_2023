import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {
 public static void main(String[] args) {
  Scanner st = new Scanner(System.in);
  int n = st.nextInt();
  assert(n >= 1 && n <= 4000);
  LinkedList L = new LinkedList();
  for (int i = 0; i < n; i++) {
   int x = st.nextInt();
   L.add(i, x);

  }

  int q = st.nextInt();
  assert(q >= 1 && q <= 4000);

  for (int i = 0; i < q; i++) {
   String s = st.next();
   if (s.equals("Insert")) {

	int x = st.nextInt();
	int y = st.nextInt();
	L.add(x, y);
   } else {
	int y = st.nextInt();
	L.remove(y);
   }

  }
  Iterator < Integer > Iterator = L.iterator();
  boolean flag = false;
  while (Iterator.hasNext()) {
   if (flag) System.out.print(" ");
   flag = true;
   System.out.print(Iterator.next());
  }
  System.out.print("\n");
 }
}
