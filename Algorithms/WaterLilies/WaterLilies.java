/*
В одном очень длинном и узком пруду по кувшинкам прыгает лягушка.
Кувшинки в пруду расположены в один ряд. Лягушка начинает прыгать с первой кувшинки ряда и
хочет закончить на последней. Но в силу вредности характера лягушка согласна прыгать только вперед через одну
или через две кувшинки. Например, с кувшинки номер 1 она может прыгнуть лишь на кувшинки номер 3 и номер 4.

На некоторых кувшинках сидят комарики. А именно, на i-й кувшинке сидят ai комаров.
Когда лягушка приземляется на кувшинку, она съедает всех комариков, сидящих на ней.
Лягушка хочет спланировать свой маршрут так, чтобы съесть как можно больше комаров.
Помогите ей: подскажите, какое максимальное число комаров она может съесть за своё путешествие.

Формат входных данных
Первая строка входа содержит число n кувшинок в пруду (1 ≤ n ≤ 1000). Вторая строка содержит n чисел,
разделённых одиночными пробелами: i-е число сообщает, сколько комаров сидит на i-й кувшинке.
Все числа целые, неотрицательные и не превосходят 1000.

Формат выходных данных
Выведите максимальное число комаров, которое может съесть лягушка. Если лягушка не может добраться до последней кувшинки, то выведите −1.
 */

import java.io.*;
import java.util.Scanner;

public class WaterLilies {
    public static void main(String[] arg) throws IOException {
        Scanner sc = new Scanner(new File("input.txt"));
        int length = sc.nextInt();
        int[] coordinate = new int[length];
        for(int i = 0; i < length; i++) {
            coordinate[i] = sc.nextInt();
        }
        try (FileWriter fw = new FileWriter(new File("output.txt"))) {
            fw.write(Long.toString(findMax(coordinate, length)));
        }
    }

    static long findMax(int[] coord, int length) {
        if(length > 4) {
            long[] maxNum = new long[length];
            maxNum[length - 1] = coord[length - 1];
            maxNum[length - 2] = 0;
            maxNum[length - 3] = coord[length - 1] + coord[length - 3];
            maxNum[length - 4] = coord[length - 4] + coord[length - 1];
            maxNum[length - 5] = coord[length - 5] + maxNum[length - 3];
            for (int i = length - 6; i >= 0; --i) {
                maxNum[i] = coord[i] + Math.max(maxNum[i + 2], maxNum[i + 3]);
            }
            return maxNum[0];
        }
        if(length == 4) {
            return coord[length - 4] + coord[length - 1];
        }
        if(length == 3) {
            return coord[length - 1] + coord[length - 3];
        }
        if(length == 1) {
            return coord[0];
        } else {
            return -1;
        }
    }
}
