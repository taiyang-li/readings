import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

    public static void main(String[] args) {

        Scanner sc=new Scanner(System.in);
        int n=sc.nextInt();            
        String ans="";
        if(n%2==1){
            ans = "Weird";
        }
        else{
            if (n >= 2 && n <= 5) {
                ans = "Not Weird";
            } else if (n >=6 && n <= 20) {
                ans = "Weird";
            } else if (n > 20) {
                ans = "Not Weird";
            }
        }
        System.out.println(ans);

    }
}
