import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

    public static void main(String[] args) {

        Scanner sc= new Scanner(System.in);

        // load list
        int n=sc.nextInt();
        LinkedList<Integer> list = new LinkedList<Integer>();
        for (int i=0; i<n; ++i) {
            int v = sc.nextInt();
            list.add(v);
        }

        // load operations
        n = sc.nextInt();
        for (int i=0; i<n; ++i) {
            sc.nextLine();
            String op = sc.nextLine();
            if (op.equals("Insert")) {
                int index = sc.nextInt();
                int value = sc.nextInt();
                list.add(index, value);
            } else if (op.equals("Delete")) {
                int index = sc.nextInt();
                list.remove(index);
            }
        }

        sc.close();

        for (Integer x : list) {
            System.out.printf("%d ", x);
        }
    }
}

