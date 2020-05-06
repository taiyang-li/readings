import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

    public static void main(String[] args) {

        Scanner sc= new Scanner(System.in);
        int n=sc.nextInt();
        ArrayList<ArrayList<Integer> > matrix = new ArrayList<ArrayList<Integer> >();
        for(int i=0;i<n;i++){
            int m = sc.nextInt();
            ArrayList<Integer> vector = new ArrayList<Integer>();
            for (int j=0; j<m; ++j) {
                int v = sc.nextInt();
                vector.add(v);
            }
            matrix.add(vector);
        }

        n = sc.nextInt();
        for (int i=0; i<n; ++i) {
            int row = sc.nextInt() - 1;
            int col = sc.nextInt() - 1;

            if (row >= matrix.size() || row < 0) {
                System.out.println("ERROR!");
                continue;
            }

            ArrayList<Integer> vector = matrix.get(row);
            if (col >= vector.size() || col < 0) {
                System.out.println("ERROR!");
                continue;
            }

            System.out.println(vector.get(col));
        }
        sc.close();
    }
}
