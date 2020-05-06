import java.io.*;
import java.math.BigInteger;
import java.security.MessageDigest;
import java.util.*;

public class Solution {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String text = in.nextLine();
        in.close();

        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            md.update(text.getBytes());
            System.out.println(new BigInteger(1, md.digest()).toString(16));
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}

