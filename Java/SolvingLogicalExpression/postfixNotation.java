import java.util.ArrayList;
import java.util.StringTokenizer;
import java.util.Stack;

public class postfixNotation {
    public ArrayList<String> postfix(String logicalNotation){
        StringTokenizer buff=new StringTokenizer(logicalNotation,(" ")) ;
        Stack<String> st=new Stack();
        st.push("0");
        String oneToken;
        ArrayList<String> logicalList=new ArrayList<>();
        while(buff.hasMoreTokens()){
            oneToken=buff.nextToken();
            switch(oneToken){
                case("("):
                    st.push(oneToken);
                    break;
                case(")"):
                        while (!st.peek().equals("(")) {
                            logicalList.add(st.pop());
                        }
                        st.pop();
                    break;
                case("true"):
                case ("false"):
                    logicalList.add(oneToken);
                    break;
                case("not"):
                        while (st.peek().equals("not")) {
                                logicalList.add(st.pop());
                    }
                    st.push(oneToken);
                    break;
                case("and"):
                        while (st.peek().equals("not") || st.peek().equals("and")) {
                                logicalList.add(st.pop());
                        }
                    st.push(oneToken);
                    break;
                case("or"):
                        while (st.peek().equals("not") || st.peek().equals("and") || st.peek().equals("or")) {
                                logicalList.add(st.pop());
                    }
                    st.push(oneToken);
                    break;
            }
        }
        while(!st.peek().equals("0")){
            logicalList.add(st.pop());
        }
        st.pop();
        return logicalList;
    }
    public String postfixResult(ArrayList<String> logicalList){
        Stack<String> st=new Stack<>();
        String result;
        for (String i:logicalList) {
            switch(i){
                case("true"):
                    st.push(i);
                    break;
                case("false"):
                    st.push(i);
                    break;
                case("not"):
                    if(st.peek().equals("true")){
                        st.pop();
                        st.push("false");
                    }
                    else{
                        st.pop();
                        st.push("true");
                    }
                    break;
                case("and"):
                    String firstValue=st.pop();
                    String secondValue;
                        secondValue = st.pop();
                    if(firstValue.equals(secondValue)){
                        st.push(firstValue);
                    }
                    else{
                        st.push("false");
                    }
                    break;
                case("or"):
                    String firstValue1=st.pop();
                    String secondValue1;
                        secondValue1 = st.pop();
                    if(firstValue1.equals(secondValue1)){
                        st.push(firstValue1);
                    }
                    else{
                        st.push("true");
                    }
                    break;
            }
        }
        result=st.pop();
        return result;

    }
}
