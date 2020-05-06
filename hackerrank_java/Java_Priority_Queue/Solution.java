import java.awt.*;
import java.util.*;
import java.util.List;

class Student{
    private int id;
    private String name;
    private double cgpa;
    public Student(int id, String name, double cgpa) {
        super();
        this.id = id;
        this.name = name;
        this.cgpa = cgpa;
    }
    public int getId() {
        return id;
    }
    public String getName() {
        return name;
    }
    public double getCgpa() {
        return cgpa;
    }
}

class Checker implements Comparator<Student> {
    @Override
    public int compare(Student o1, Student o2) {
        if (o1.getCgpa() > o2.getCgpa()) {
            return -1;
        }
        else if (o1.getCgpa() == o2.getCgpa()) {
            int tmp = o1.getName().compareTo(o2.getName());
            if (tmp != 0)
                return tmp;

            if (o1.getId() < o2.getId())
                return -1;
            else if (o1.getId() == o2.getId())
                return 0;
            else
                return 1;
        } else {
            return 1;
        }
    }
}

class Priorities {
    public List<Student> getStudents(List<String> events) {
        PriorityQueue<Student> pqueue = new PriorityQueue<Student>(new Checker());
        for (String event: events) {
            Scanner in = new Scanner(event);
            String op = in.next();

            switch (op) {
                case "ENTER": {
                    String name = in.next();
                    float cgpa = in.nextFloat();
                    int id = in.nextInt();
                    Student stu = new Student(id, name, cgpa);
                    pqueue.add(stu);
                    break;
                }
                case "SERVED": {
                    pqueue.poll();
                    break;
                }
                default: {
                    System.out.println("wrong input");
                }
            }
            in.close();
        }

        List<Student> students = new LinkedList<Student>();
        while ( ! pqueue.isEmpty()) {
            students.add(pqueue.poll());
        }
        return students;
    }
}

public class Solution {
    private final static Scanner scan = new Scanner(System.in);
    private final static Priorities priorities = new Priorities();
    
    public static void main(String[] args) {
        int totalEvents = Integer.parseInt(scan.nextLine());    
        List<String> events = new ArrayList<>();
        
        while (totalEvents-- != 0) {
            String event = scan.nextLine();
            events.add(event);
        }
        
        List<Student> students = priorities.getStudents(events);
        
        if (students.isEmpty()) {
            System.out.println("EMPTY");
        } else {
            for (Student st: students) {
                System.out.println(st.getName());
            }
        }
    }
}
