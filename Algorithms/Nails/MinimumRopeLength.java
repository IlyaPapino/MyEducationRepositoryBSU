/*
Имеется деревянная планка, параллельная оси OX, в которую вбито n гвоздей.
Известны координаты xi этих гвоздей (1 ≤ i ≤ n), причём xi < xi + 1.
К гвоздям требуется привязать верёвочки таким образом, чтобы:
каждая верёвочка связывала ровно два гвоздя;
к каждому гвоздю была привязана хотя бы одна верёвочка;
суммарная длина веревочек была бы минимальна.
Формат входных данных
В первой строке записано целое число n (2 ≤ n ≤ 100).
В следующих строках (по одному числу в строке) указаны координаты гвоздей в порядке возрастания.
Координаты являются вещественными числами от 0 до 1000 включительно и
задаются не более чем с двумя знаками после десятичной точки.
Формат выходных данных
Выведите минимальную суммарную длину верёвочек (с двумя знаками после десятичной точки).
*/

import java.io.*;

public class MinimumRopeLength {
    public static void main(String[] arg) throws IOException {
            FileReader fr = new FileReader("in.txt");
            BufferedReader br = new BufferedReader(fr);
            int length = Integer.parseInt(br.readLine());
            double[] coordinate = new double[length];
            for(int i = 0; i < length; i++) {
                coordinate[i] = Double.parseDouble(br.readLine());
            }
            try (FileWriter fw = new FileWriter(new File("out.txt"))) {
                fw.write(String.format("%.2f",findMinRopeLen(coordinate, length)));
            }
    }

   static double findMinRopeLen(double[] coord, int length) {
       if(length > 2) {
           double ropeLen1 = coord[1] - coord[0];
           double ropeLen2 = coord[1] - coord[0] + coord[2] - coord[1];
           for (int i = 2; i < length - 1; i++) {
               double buff = ropeLen2;
               ropeLen2 = Math.min(ropeLen1 + coord[i + 1] - coord[i], ropeLen2 + coord[i + 1] - coord[i]);
               ropeLen1 = buff;
           }
           return ropeLen2;
       } else {
           return coord[1] - coord[0];
       }
   }
}
