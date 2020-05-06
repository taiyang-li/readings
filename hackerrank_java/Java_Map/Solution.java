//Complete this code or write your own from scratch
import java.util.*;
import java.io.*;

class Solution{
   public static void main(String []argh)
   {
      Scanner in = new Scanner(System.in);
      HashMap<String, Integer> hashmap = new HashMap<String, Integer>();
      int n=in.nextInt();
      in.nextLine();
      for(int i=0;i<n;i++)
      {
         String name=in.nextLine();
         int phone=in.nextInt();
         in.nextLine();

         hashmap.put(name, phone);
      }
      while(in.hasNext())
      {
         String s=in.nextLine();
         if (hashmap.containsKey(s)) {
             System.out.printf("%s=%d\n", s, hashmap.get(s));
         } else {
             System.out.println("Not found");
         }
      }
   }
}
