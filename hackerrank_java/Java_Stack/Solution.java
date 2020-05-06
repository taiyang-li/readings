import java.util.*;

class Solution{

    public static void main(String []argh)
    {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNext()) {
            String input=sc.next();

            System.out.println(isMatch(input));
        }
    }

    private static boolean isMatch(String input) {
        if (input.isEmpty())
            return true;

        Stack<Character> stack = new Stack<Character>();
        for (int i=0; i<input.length(); ++i) {
            char c = input.charAt(i);
            if (c == '{' || c == '(' || c == '[') {
                stack.push(c);
            } else if (c == '}' || c == ')' || c == ']') {
                if (stack.empty())
                    return false;

                char p = stack.pop();
                if (p == '{' && c == '}' || p == '(' && c == ')'
                        || p == '[' && c == ']')
                    continue;
                else
                    return false;

            } else {
                return false;
            }
        }
        return stack.empty();
    }
}
