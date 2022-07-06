import java.util.*;
import java.security.*;
public class IntToString {
	public static void main(String[] args) {
		
		Do_Not_Terminate.forbidExit();

		try{
			Scanner in = new Scanner(System.in);
			int n=in.nextInt();
      String s = Integer.toString(n);
      if(n==Integer.parseInt(s))
			{
				System.out.println("Good job");
			}
			else
			{
				System.out.println("Wrong answer.");
			}
		}
		catch (Do_Not_Terminate.ExitTrappedException e) {
			System.out.println("Unsuccessful Termination!!");
		}
	}
}
