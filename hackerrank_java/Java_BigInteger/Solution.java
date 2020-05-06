import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

    public static void main(String[] args) {

        Scanner sc= new Scanner(System.in);
        String a = sc.nextLine();
        String b = sc.nextLine();

        BigInteger bi_a = new BigInteger(a);
        BigInteger bi_b = new BigInteger(b);
        BigInteger sum = bi_a.add(bi_b);
        BigInteger product = bi_a.multiply(bi_b);

        System.out.println(sum.toString());
        System.out.println(product.toString());
    }
}
