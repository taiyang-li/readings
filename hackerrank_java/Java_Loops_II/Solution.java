import java.util.*;
import java.io.*;

class Solution{
    public static void main(String []argh){
        Scanner in = new Scanner(System.in);
        int t=in.nextInt();
        for(int i=0;i<t;i++){
            int a = in.nextInt();
            int b = in.nextInt();
            int n = in.nextInt();

            int sum = a;
            int tmp = 1;
            for (int j=0; j<n; ++j) {
                sum += tmp * b;
                tmp *= 2;
                if (j == 0) {
                    System.out.printf("%d", sum);
                } else {
                    System.out.printf(" %d", sum);
                }
            }
            System.out.printf("\n");
        }
        in.close();
    }
}
