import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.regex.Pattern;

public class Main {
    public static void main(String[]arg){
        Scanner sc = null;
        try {
            Pattern p= Pattern.compile("((, )|\r\n)+");
            sc = new Scanner(new File("./src/inCreditBooks.txt")).useDelimiter(p);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        creditBooks A=new creditBooks();
        A.inputCreditBooks(sc);
        A.printCreditBooks();
        System.out.println("Отличники:");
        A.excellentStudents();
        Scanner sc3 = null;
        try {
            Pattern p= Pattern.compile("((, )|\r\n)+");
            sc3 = new Scanner(new File("./src/inExamVed.txt")).useDelimiter(p);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        A.inputExam(sc3);
        A.printCreditBooks();
        Scanner sc2=new Scanner(System.in);
        System.out.println("Введите номер зачётки для поиска");
        A.findCreditBook(sc2.nextInt());
    }
}
