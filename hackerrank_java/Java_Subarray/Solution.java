import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int[] a = new int[n];
        for (int i=0; i<n; ++i) {
            a[i] = in.nextInt();
        }

        int count = 0;
        for (int i=0; i<n; ++i) {
            for (int j=i+1; j<=n; ++j) {
                int sum = 0;
                for (int k=i; k<j; ++k) {
                    sum += a[k];
                }
                if (sum < 0)  {
                    // System.out.printf("%d %d\n", i, j);
                    count++;
                }
            }
        }
        System.out.println(count);
    }
}
