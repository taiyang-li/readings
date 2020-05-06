import java.util.*;
public class Solution {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        Deque<Integer> deque = new ArrayDeque<Integer>();
        HashSet<Integer> set = new HashSet<Integer>();
        int n = in.nextInt();
        int m = in.nextInt();
        int ret = 0;
        for (int i = 0; i < n; i++) {
            System.out.println(i);
            int num = in.nextInt();
            deque.add(num);
            set.add(num);

            if (deque.size() == m) {
                if (set.size() > ret)
                    ret = set.size();
                Integer first = deque.remove();
                if (! deque.contains(first)) {
                    set.remove(first);
                }
            }
        }
        System.out.println(ret);
    }
}

