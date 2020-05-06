import java.io.*;
import java.util.*;

public class Solution {
    
    private static int[] frequency = new int[26];

    static boolean isAnagram(String a, String b) {
        a = a.toLowerCase();
        b = b.toLowerCase();
        for (int i=0; i<a.length(); ++i) {
            frequency[a.charAt(i) - 'a']++;
        }
        for (int i=0; i<b.length(); ++i) {
            frequency[b.charAt(i) - 'a']--;
        }
        
        for (int i=0; i<26; ++i) {
            if (frequency[i] != 0) {
                return false;
            }
        }
        return true;
    }

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        String a = scan.next();
        String b = scan.next();
        scan.close();
        boolean ret = isAnagram(a, b);
        System.out.println( (ret) ? "Anagrams" : "Not Anagrams" );
    }
}
