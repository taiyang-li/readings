import java.io.*;
import java.security.MessageDigest;
import java.util.*;

public class Solution {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String text = in.nextLine();
        in.close();

        try {
            MessageDigest md = MessageDigest.getInstance("MD5");
            md.update(text.getBytes());
            System.out.println(md.toString());
        } catch (Exception e) {
            System.out.println()
        }
    }
}
