import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

    public static void main(String[] args) {
        int line_no = 1;
        Scanner in = new Scanner(System.in);
        while (in.hasNextLine()) {
            System.out.printf("%d %s\n", line_no++, in.nextLine());
        }
    }
}
