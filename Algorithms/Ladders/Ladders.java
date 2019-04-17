/*
Лесенкой будем называть конструкцию из кубиков, в которой каждый следующий уровень состоит
из строго большего числа кубиков, чем предыдущий уровень, если считать уровни сверху вниз.

Необходимо подсчитать число лесенок, которые можно построить ровно из n кубиков.

Формат входных данных
В единственной строке записано число n (1 ≤ n ≤ 500).

Формат выходных данных
Выведите искомое число лесенок.
*/

import java.io.*;

public class Ladders {
    public static void main(String[] arg) throws IOException {
        FileReader fr = new FileReader("input.txt");
        BufferedReader br = new BufferedReader(fr);
        int cubNum = Integer.parseInt(br.readLine());
        long[][] table = new long[cubNum + 1][cubNum + 1];
        long numLadders = 0;
        for (int i = 1; i < cubNum + 1; i++) {
            table[i][i] = 1;
        }
        for (int i = 1; i < cubNum + 1; i++) {
            for (int j = 1; j <= i; j++) {
                if (i <= j * (j + 1) / 2) {
                    int r = 1;
                    while (r <= j - 1) {
                        table[i][j] += table[i - j][r];
                        r++;
                    }
                }
            }
        }
        for (int i = 1; i < cubNum + 1; i++) {
            numLadders += table[cubNum][i];
        }
        try (FileWriter fw = new FileWriter(new File("output.txt"))) {
            fw.write(Long.toString(numLadders));
        }
    }
}

    /*static long findNumLadders(int firstFloor, int cubNum) {
        if (cubNum == 0) {
            return 1;
        }
        long numLadders = 0;
            for (int i = 1; i < firstFloor; i++) {
                if ((cubNum - i) < 0) {
                    break;
                } else {
                    numLadders += findNumLadders(i, cubNum - i);
                }
            }
        return numLadders;
    }
}
*/

