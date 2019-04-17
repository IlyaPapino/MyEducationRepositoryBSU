import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class findInHTML {
    private ArrayList<String> tegList;
    private Pattern teg;
    public findInHTML(){
        tegList = new ArrayList<>();
        teg = Pattern.compile("[<</]+[a-z]+>");
    }
    public void findTegList(String text){
        Matcher matcher=teg.matcher(text);
        if(matcher.matches()) {
            int start = matcher.start();
            int end = matcher.end();
            String teg = text.substring(start, end);
            tegList.add(teg);
        }
        else
            return;
    }
    public String deleteTegs(String text){
        String finalText=new String(text.replaceAll("[<</]+[a-z]+>",""));
        return finalText;
    }
    public String missingWords(String text,String fileName){
        String missingWord=new String();
        Scanner sc = null;
        try {
            Pattern p= Pattern.compile("((; )|\r\n)+");
            sc = new Scanner(new File(fileName)).useDelimiter(p);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        while(sc.hasNext()) {
            String searchWord=sc.next();
            if(!text.contains(searchWord)) {
                missingWord=missingWord+searchWord+" ";
            }
        }
        return missingWord;
    }
    public void printTegs(){
        for (String i:tegList) {
            System.out.print(i+" ");
        }
    }
}
