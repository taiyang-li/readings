import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;
import java.lang.reflect.*;


class Singleton{
    public String str;
    private Singleton() {}

    private static final Singleton INSTANCE = new Singleton();

    public static Singleton getSingleInstance() {
        return INSTANCE;
    
}

