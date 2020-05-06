import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

    public static String getSmallestAndLargest(String s, int k) {
        String smallest = s.substring(0, k);
        String largest = s.substring(0, k);
        for (int i=1; i<=s.length()-k; i++) {
            String curr = s.substring(i, i+k);
            // System.out.println(curr + " " + i);
            if (curr.compareTo(largest) > 0) {
                largest = curr;
            }
            if (smallest.compareTo(curr) > 0) {
                smallest = curr;
            }
        }
        return smallest + "\n" + largest;
    }

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        String s = scan.next();
        int k = scan.nextInt();
        scan.close();

        System.out.println(getSmallestAndLargest(s, k));
    }
}
