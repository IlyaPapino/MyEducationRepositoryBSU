import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] arg) throws FileNotFoundException {
        Scanner sc = new Scanner(new File("input.txt"));
        postfixNotation pn = new postfixNotation();
        ArrayList<String> al = pn.postfix(sc.nextLine());
        System.out.println(pn.postfixResult(al));
    }
}
