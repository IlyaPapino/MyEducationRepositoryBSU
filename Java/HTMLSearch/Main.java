import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {
    public static void main(String[] arg){
        Scanner sc = null;
        try {
            sc = new Scanner(new File("./src/input.html"));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        String text = new String();
        while(sc.hasNext()) {
            text=text+sc.nextLine();
        }
        findInHTML fIHTML = new findInHTML();
        fIHTML.findTegList(text);
        fIHTML.printTegs();
        String finalText=fIHTML.deleteTegs(text);
        System.out.println(finalText);
        String missingWords=fIHTML.missingWords(finalText,"./src/inputForSearch.txt");
        try(FileWriter writer = new FileWriter("output.txt", false))
        {
            writer.write(missingWords);
        }
        catch(IOException ex){
            ex.printStackTrace();
        }
    }
}
