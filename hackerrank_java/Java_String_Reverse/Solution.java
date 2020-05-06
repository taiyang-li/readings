import java.io.*;
import java.util.*;

public class Solution {

    public static void main(String[] args) {

        Scanner sc=new Scanner(System.in);
        String A=sc.next();
        /* Enter your code here. Print output to STDOUT. */

        int i = 0;
        for (; i<A.length()/2; ++i) {
            if (A.charAt(i) != A.charAt(A.length()-1-i)) {
                break;
            }
        }

        if (i == A.length()/2) {
            System.out.println("Yes");
        } else {
            System.out.println("No");
        }
    }
}

