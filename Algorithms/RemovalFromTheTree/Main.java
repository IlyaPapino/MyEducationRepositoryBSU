/*
По набору ключей постройте бинарное поисковое дерево.
Удалите из него ключ (правым удалением), если он есть в дереве.
Выполните прямой левый обход полученного дерева.

Формат входных данных
В первой строке записано целое число — ключ, который нужно удалить из дерева.
Вторая строка пустая.

Последующие строки содержат последовательность чисел — ключи вершин в порядке добавления в дерево.
Ключи задаются в формате по одному в строке. Дерево содержит хотя бы две вершины.

Напомним, что в поисковом дереве все ключи по определению уникальны, поэтому
при попытке добавить в дерево ключ, который там уже есть, он игнорируется.

Формат выходных данных
Выведите последовательность ключей вершин, полученную прямым левым обходом дерева.
 */

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Scanner;

public class Main implements Runnable {
    public static void main(String[] arg) {
        new Thread(null, new Main(), "", 64 * 1024 * 1024).start();
    }
    public void run() {
        try (Scanner sc = new Scanner(new File("tst.in"))) {
            BinarySearchTree tree = new BinarySearchTree();
            while (sc.hasNext()) {
                tree.insert(Long.parseLong(sc.next()));
            }
            FileWriter fW = new FileWriter("tst.out");
            ArrayList<Node> nodeList = new ArrayList<>();
            tree.findNodeList(tree.root, nodeList);
            if(nodeList.size() != 0 && nodeList.size() % 2 != 0) {
                tree.root = tree.delete(tree.root, tree.findMean(nodeList).key);
            }
            tree.straightLeftBypass(tree.getRoot(), fW);
            fW.close();

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    static class Node {
        Node left;
        Node right;
        int height;
        long key;
        Node(long _key) {
            key = _key;
            height = 0;
        }
    }

    static class BinarySearchTree {
        public Node root;

        public Node getRoot() {
            return root;
        }

        public void insert(long newKey) {
            if (root == null) {
                root = new Node(newKey);
                return;
            }
            Node buffNode = root;
            while (true) {
                if (buffNode.key > newKey) {
                    if (buffNode.left == null) {
                        buffNode.left = new Node(newKey);
                        return;
                    } else {
                        buffNode = buffNode.left;
                    }
                } else {
                    if (buffNode.key < newKey) {
                        if (buffNode.right == null) {
                            buffNode.right = new Node(newKey);
                            return;
                        } else {
                            buffNode = buffNode.right;
                        }
                    } else {
                        return;
                    }
                }
            }
        }

        public Node delete(Node startNode, long key) {
            if(startNode == null) {
                return null;
            }
            if (key < startNode.key) {
                startNode.left = delete(startNode.left, key);
                return startNode;
            } else {
                if (key > startNode.key) {
                    startNode.right = delete(startNode.right, key);
                    return startNode;

                }
            }
            if (startNode.left == null) {
                return startNode.right;
            }
            if (startNode.right == null) {
                return startNode.left;
            } else {
                long minKey = findMin(startNode.left).key;
                startNode.key = minKey;
                startNode.left = delete(startNode.left, minKey);
                return startNode;
            }
        }

        public Node findMin(Node startNode) {
            if(startNode.right != null) {
                return findMin(startNode.right);
            } else {
                return startNode;
            }
        }

        public void straightLeftBypass(Node startNode, FileWriter fW) throws IOException {
            if (startNode != null) {
                fW.write(startNode.key + "\n");
                straightLeftBypass(startNode.left, fW);
                straightLeftBypass(startNode.right, fW);
            }
        }

        public Node findMean (ArrayList<Node> nodeList) {
            nodeList.sort(new Comparator<Node>() {
                @Override
                public int compare(Node o1, Node o2) {
                    return (int) ((int)o1.key - o2.key);
                }
            });
            int meanNum = nodeList.size()/2;
            return nodeList.get(meanNum);
        }

        public void findNodeList (Node startNode, ArrayList<Node> nodeList) {
            if (startNode != null) {
                findNodeList(startNode.left, nodeList);
                findNodeList(startNode.right, nodeList);
                if(startNode.right != null && startNode.left != null) {
                    if (Math.abs(heightSearch(startNode.left) - heightSearch(startNode.right)) == 2) {
                        nodeList.add(startNode);
                    }
                } else {
                    if(startNode.left != null && startNode.right == null) {
                        if(Math.abs(heightSearch(startNode.left) + 1) == 2) {
                            nodeList.add(startNode);
                        }
                    }
                    if(startNode.right != null && startNode.left == null) {
                        if(Math.abs(heightSearch(startNode.right) + 1) == 2) {
                            nodeList.add(startNode);
                        }
                    }
                }
            }
        }

        public int heightSearch(Node startNode) {
            if(startNode.right == null && startNode.left == null) {
                return 0;
            } else {
                if(startNode.right != null && startNode.left == null) {
                    return 1 + heightSearch(startNode.right);
                }
                if(startNode.left != null && startNode.right == null) {
                    return 1 + heightSearch(startNode.left);
                } else {
                    return 1 + Math.max(heightSearch(startNode.right), heightSearch(startNode.left));
                }

            }
        }
    }
}
