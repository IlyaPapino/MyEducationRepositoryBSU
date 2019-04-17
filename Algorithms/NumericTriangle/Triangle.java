/*
На рисунке показан числовой треугольник.

    7
   3 8
  8 1 0
 2 7 4 4
4 5 2 6 5

Необходимо определить максимальную сумму чисел, расположенных на пути,
который начинается с верхнего числа и заканчивается на каком-нибудь числе
в основании треугольника (максимум суммы среди всех таких путей).
На каждом шаге можно двигаться к соседнему по диагонали числу влево и вниз или вправо и вниз.
Число строк в треугольнике k. Все числа в треугольнике aij — целые в интервале между 0 и 99 включительно.

Формат входных данных
В первой строке записано число k строк треугольника (1 ≤ k ≤ 1000).
Следующие k строк входного файла задают сам треугольник. В i-й строке (1 ≤ i ≤ k),
описывающей треугольник, содержится i чисел, записанных через пробел.

Формат выходных данных
Выведите искомую максимальную сумму чисел.
 */

import java.io.*;
import java.util.Scanner;

public class Triangle {
    public static void main(String[] arg) throws IOException {
        Scanner sc = new Scanner(new File("input.txt"));
        int strNum = sc.nextInt();
        int[][] triangle = new int[strNum][strNum];
        for(int i = 0; i < strNum; i++) {
            for(int j = 0; j <= i; j++) {
                triangle[i][j] = sc.nextInt();
            }
        }
        long[][] sumTriangle = new long[strNum][strNum + 1];
        sumTriangle[0][1] = triangle[0][0];
        for(int i = 1; i < strNum; i++) {
            for(int j = 1; j <= i + 1; j++) {
                sumTriangle[i][j] = triangle[i][j - 1] + Math.max(sumTriangle[i - 1][j],sumTriangle[i - 1][j - 1]);
            }
        }
        long rez = findMax(sumTriangle[strNum - 1]);
        try (FileWriter fw = new FileWriter(new File("output.txt"))) {
            fw.write(Long.toString(rez));
        }
    }

    static long findMax(long[] mass) {
        long max = mass[0];
        int length = mass.length;
        for(int i = 1; i < length; i++) {
            if(mass[i] > max) {
                max = mass[i];
            }
        }
        return max;
    }
}
