import java.util.ArrayList;
import java.util.Scanner;

public class creditBooks {
    private ArrayList<creditBook> mCreditBooks=new ArrayList<>();
    public void inputCreditBooks(Scanner sc){
        int i=0;
        while (sc.hasNext()) {
                mCreditBooks.add(new creditBook());
                mCreditBooks.get(i).inputCreditBook(sc);
                i++;
        }
    }
    public void printCreditBooks(){
        for (creditBook i:mCreditBooks) {
            i.printCreditBook();
        }
    }
    public void excellentStudents(){
        for (creditBook i:mCreditBooks) {
            if(i.gradePointAverage()>=9&&i.dept==false){
                System.out.println(i.surname+" "+i.name+" "+i.patronymic+" ");//+i.gradePointAverage());
                System.out.printf("Средний балл: %3.1f%n", i.gradePointAverage());
            }
        }
    }
    public void findCreditBook(int num){
        for (creditBook i:mCreditBooks) {
            if(i.num==num){
                i.printCreditBook();
                System.out.printf("Средний балл: %3.1f%n", i.gradePointAverage());
                return;
            }
        }
        System.out.println("Not Found");
    }
    public void inputExam(Scanner sc){
        String examInformation=sc.nextLine();
        while (sc.hasNext()) {
            String surname = sc.next();
            for (creditBook i : mCreditBooks) {
                if (i.surname.equals(surname)) {
                    i.inputExamInCreditBook(examInformation,sc);
                }
            }
        }
    }

    public class creditBook {
        private int num;
        private String name;
        private String surname;
        private String patronymic;
        private String receiptDate;
        private boolean dept=false;
        private ArrayList<session> mSession=new ArrayList<>();
        public void inputCreditBook(Scanner sc){
            num=sc.nextInt();
            surname=sc.next();
            name=sc.next();
            patronymic=sc.next();
            receiptDate=sc.next();
            int i=0;
            while(sc.next().equals("Сессия")){
                mSession.add(new session());
                mSession.get(i).inputSession(sc);
                i++;
            }
        }
        public void printCreditBook(){
            System.out.println(num+" "+surname+" "+name+" "+patronymic+" "+receiptDate);
            for (session i:mSession) {
                i.printSession();
            }
            System.out.println("_________________________________________________");
        }
        public double gradePointAverage(){
            int numSession=0;
            double sum=0;
            for (session i:mSession) {
               sum+= i.gradePointAverageInSession();
               numSession++;
            }
            return sum/numSession;
        }
       public void inputExamInCreditBook(String examInformation,Scanner sc){
            Scanner sc2=new Scanner(examInformation);
            int sessionNum = sc2.nextInt();
            mSession.get(sessionNum-1).addExam(sc,sc2);
       }

        public class session {
            private int sessionNum;
            private int numExam;
            private int numCredit;
            private ArrayList<exam> mExam=new ArrayList<>();
            private ArrayList<credit> mCredit=new ArrayList<>();
            public void inputSession(Scanner sc ){
                sessionNum = sc.nextInt();
                sc.nextLine();
                numExam = sc.nextInt();
                sc.nextLine();
                int i=0;
                while(i<numExam) {
                    mExam.add(new exam());
                    mExam.get(i).inputExam(sc);
                    i++;
                }
                numCredit = sc.nextInt();
                sc.nextLine();
                int j=0;
                while(j<numCredit) {
                    mCredit.add(new credit());
                    mCredit.get(j).inputCredit(sc);
                    j++;
                }
            }
            public void printSession(){
                System.out.println("Сессия "+sessionNum);
                System.out.println("Экзамены:");
                for (exam i:mExam) {
                    i.printExam();
                }
                System.out.println("Зачёты:");
                for (credit i:mCredit) {
                    i.printCredit();
                }
            }
            public double gradePointAverageInSession(){
                double sum=0;
                for(int i=0;i<numExam;i++){
                    sum+=mExam.get(i).rating;
                }
                double rez=sum/numExam;
                return rez;
            }
            public void addExam(Scanner sc,Scanner sc2){
                exam newExam = new exam();
                newExam.subjectName=sc2.next();
                newExam.teacherName=sc2.next();
                newExam.rating=sc.nextInt();
                newExam.examDate=sc.next();
                mExam.add(newExam);
            }

            public class credit {
                private String subjectName;
                private String rating;
                private String teacherName;
                private String creditDate;
                public void inputCredit(Scanner sc){
                    subjectName=sc.next();
                    int buff=sc.nextInt();
                    if(buff==1){
                        rating=new String("Зачтено");
                    }
                    else{
                        rating=new String("Не зачтено");
                        dept=true;
                    }
                    teacherName=sc.next();
                    creditDate=sc.next();
                }
                public void printCredit(){
                    System.out.println(subjectName+" "+rating+" "+teacherName+" "+creditDate);
                }
            }

            public class exam {
                private String subjectName;
                private int rating;
                private String teacherName;
                private String examDate;
                public void inputExam(Scanner sc){
                    subjectName=sc.next();
                    rating=sc.nextInt();
                    if(rating<4){
                        dept=false;
                    }
                    teacherName=sc.next();
                    examDate=sc.next();
                }
                public void printExam(){
                    System.out.println(subjectName+" "+rating+" "+teacherName+" "+examDate);
                }
            }

        }

    }
}

