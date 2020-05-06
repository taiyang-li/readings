import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int arr[][] = new int[6][6];
        for(int i=0; i < 6; i++){
            for(int j=0; j < 6; j++){
                arr[i][j] = in.nextInt();
            }
        }

        int max_sum = -63;
        int cur_sum = 0;
        for (int i=1; i<=4; ++i) {
            for (int j=1; j<=4; ++j) {
                cur_sum = arr[i-1][j-1] + arr[i-1][j] + arr[i-1][j+1] 
                                        + arr[i][j]
                        + arr[i+1][j-1] + arr[i+1][j] + arr[i+1][j+1];
                if (cur_sum > max_sum) {
                    max_sum = cur_sum;
                }
            }
        }

        System.out.println(max_sum);
    }
}
