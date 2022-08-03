import java.util.*;
import java.io.*;

class Solution{
    public static void main(String []argh)
    {
        HashMap<String, Integer> hash = new HashMap<>();
        Scanner in = new Scanner(System.in);
        int n=in.nextInt();
        in.nextLine();
        for(int i=0;i<n;i++)
        {
            String name=in.nextLine();
            int phone=in.nextInt();
            in.nextLine();
            hash.put(name,phone);
        }
        while(in.hasNext())
        {
            String s=in.nextLine();
            try
            {
                int out=hash.get(s);
                System.out.println(s+"="+out);
            }
            catch(Exception e)
            {
                System.out.println("Not found");
            }
        }


    }
}
