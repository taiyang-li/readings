import java.io.*;
import java.util.*;

public class Solution {

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        String s = scan.nextLine();

        String delim = "[!,?._'@ ]+";
        String[] tokens = s.split(delim);

        int n = tokens.length;
        if (tokens.length > 0 && tokens[0].isEmpty()) 
            n--;
        if (tokens.length > 1 && tokens[tokens.length-1].isEmpty())
            n--;
        System.out.println(n);
        for (String token : tokens) {
            if (! token.isEmpty()) {
                System.out.println(token);
            }
        }
        scan.close();
    }
}

