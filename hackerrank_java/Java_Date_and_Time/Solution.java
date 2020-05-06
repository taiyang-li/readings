import java.util.Arrays;
import java.util.Calendar;
import java.util.List;
import java.util.Scanner;

public class Solution {
    public static String getDay(String day, String month, String year) {
        // cast string to int
        int i_day = 0;
        int i_month = 0;
        int i_year = 0;
        try {
            i_day = Integer.parseInt(day);
            i_month = Integer.parseInt(month);
            i_year = Integer.parseInt(year);
        } catch (NumberFormatException e) {
            System.out.println(e);
            System.exit(-1);
        }
        
        // get day
        Calendar cal = Calendar.getInstance();
        //cal.set(i_year, i_month, i_day);
        cal.set(Calendar.YEAR, i_year);
        cal.set(Calendar.MONTH, i_month-1);
        cal.set(Calendar.DAY_OF_MONTH, i_day);
        int day_of_week = cal.get(Calendar.DAY_OF_WEEK);
        switch (day_of_week) {
            case Calendar.SUNDAY:
                return "SUNDAY";
            case Calendar.MONDAY:
                return "MONDAY";
            case Calendar.TUESDAY:
                return "TUESDAY";
            case Calendar.WEDNESDAY:
                return "WEDNESDAY";
            case Calendar.THURSDAY:
                return "THURSDAY";
            case Calendar.FRIDAY:
                return "FRIDAY";
            case Calendar.SATURDAY:
                return "SATURDAY";
        }
        return "ERROR";
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String month = in.next();
        String day = in.next();
        String year = in.next();
        System.out.println(getDay(day, month, year));
    }
}

