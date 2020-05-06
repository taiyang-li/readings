import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int bits = in.nextInt();
        int ops = in.nextInt();

        BitSet bitset1 = new BitSet(bits);
        BitSet bitset2 = new BitSet(bits);
        BitSet[] bitsets = new BitSet[3];
        bitsets[1] = bitset1;
        bitsets[2] = bitset2;

        for (int i=0; i<ops; ++i) {
            String op = in.next();
            int num1 = in.nextInt();
            int num2 = in.nextInt();

            switch (op) {
                case "AND":
                    bitsets[num1].and(bitsets[num2]);
                    break;
                case "OR":
                    bitsets[num1].or(bitsets[num2]);
                    break;
                case "XOR":
                    bitsets[num1].xor(bitsets[num2]);
                    break;
                case "FLIP":
                    bitsets[num1].flip(num2);
                    break;
                case "SET":
                    bitsets[num1].set(num2);
                    break;
                default:
                    System.out.println("Wrong input");
            }
            System.out.printf("%d %d\n", bitsets[1].cardinality(), bitsets[2].cardinality());
        }
        in.close();
    }
}
