import java.util.*;

public class Solution {
    public static boolean canWin(int leap, int[] game) {
        return doCanWin(leap, game, 0);
    }
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int q = scan.nextInt();
        while (q-- > 0) {
            int n = scan.nextInt();
            int leap = scan.nextInt();
            
            int[] game = new int[n];
            for (int i = 0; i < n; i++) {
                game[i] = scan.nextInt();
            }

            System.out.println( (canWin(leap, game)) ? "YES" : "NO" );
        }
        scan.close();
    }

    private static boolean doCanWin(int leap, int[] game, int index) {
        if (index < 0 )
            return false;

        if (index >= game.length)
            return true;

        if (game[index] == 1)
            return false;

        game[index] = 1;
        return doCanWin(leap, game, index+1) || doCanWin(leap, game, index-1)
                || doCanWin(leap, game, index+leap);
    }
}

