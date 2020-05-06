import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;
import java.lang.reflect.*;
import static java.lang.System.*;

class Prime {
    public void checkPrime(int... args) {
        ArrayList<Integer> primes = new ArrayList<Integer>();
        for (int i=0; i<args.length; ++i) {
            BigInteger bi = new BigInteger(String.valueOf(args[i]));
            if (bi.isProbablePrime(100)) {
                primes.add(args[i]);
            }
        }

        if (primes.isEmpty()) {
            System.out.println();
            return;
        }

        for (int i=0; i<primes.size(); ++i) {
            if (i == 0) {
                System.out.print(primes.get(i));
            } else {
                System.out.printf(" %d", primes.get(i));
            }
        }
        System.out.println();
    }
}


public class Solution {

	public static void main(String[] args) {
		try{

		BufferedReader br=new BufferedReader(new InputStreamReader(in));
		int n1=Integer.parseInt(br.readLine());
		int n2=Integer.parseInt(br.readLine());
		int n3=Integer.parseInt(br.readLine());
		int n4=Integer.parseInt(br.readLine());
		int n5=Integer.parseInt(br.readLine());
		Prime ob=new Prime();
		ob.checkPrime(n1);
		ob.checkPrime(n1,n2);
		ob.checkPrime(n1,n2,n3);
		ob.checkPrime(n1,n2,n3,n4,n5);
		Method[] methods=Prime.class.getDeclaredMethods();
		Set<String> set=new HashSet<>();
		boolean overload=false;
		for(int i=0;i<methods.length;i++)
		{
			if(set.contains(methods[i].getName()))
			{
				overload=true;
				break;
			}
			set.add(methods[i].getName());

		}
		if(overload)
		{
			throw new Exception("Overloading not allowed");
		}
		}
		catch(Exception e)
		{
			System.out.println(e);
		}
	}

}


