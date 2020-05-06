import java.io.*;
        import java.util.*;

public class Solution {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        try {
            int left = in.nextInt();
            int right = in.nextInt();
            System.out.println(left/right);
        } catch (InputMismatchException ime) {
            System.out.println(ime.getClass().getName());
        } catch (ArithmeticException ae) {
            System.out.println(ae);
        }
        in.close();
    }
}
