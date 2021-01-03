Main.java // это файл затри к хуям комментарий и сделай название как название файла

import java.io.IOException;
import java.util.Scanner;

public class Main {
    static AVL<String,String> Avl_Tree=new AVL<>();//Main.avl
    public static void main(String[] args) throws IOException {//!!!//мы создаем класс исключений происходящего от класса предка
        Boolean flag=true;
        Menu menuHead=new Menu();
        while(flag) {
            Scanner sc=new Scanner(System.in);
            menuHead.menuSpisock();
            Integer choice=sc.nextInt();
            if((choice>6)||(choice<0)){
                System.out.println("Write Normal Data");
                continue;
            }
            Menu menu=new Menu(choice);
            flag=menu.choiceMenu(menu.getChoice());
        }
    }
}


Menu.java // это файл затри к хуям комментарий и сделай название как название файла

import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;


public class Menu extends Words {
    private Integer choice;
    private BufferedReader br;
    private BufferedWriter bw;
    private BufferedWriter bwArrayList;
    private ArrayList<String> line=new ArrayList<>();

    public Menu(){
    }
    public Menu(Integer choice){
        this.choice=choice;
    }
    public Integer getChoice(){return this.choice;}

    //Реализация меню
    public void menuSpisock(){
        System.out.println("0-Считать");
        System.out.println("1-Добавление");
        System.out.println("2-Поиск");
        System.out.println("3-Вывод");
        System.out.println("4-Удаление");
        System.out.println("5-Очистить экран");
        System.out.println("6-Выход");
    }

    public Boolean choiceMenu(Integer choice) throws IOException {
        Boolean flag = true;
        switch (this.choice) {
            case 0:
                line.clear();
                this.fromFile();//!
                break;
            case 1:
                System.out.println("Writing Word (FORMAT: English-Russian): ");
                Scanner sc1=new Scanner(System.in);
                String listWordAdd=sc1.nextLine();
                this.inFile(listWordAdd);
                break;
            case 2:
                System.out.println("Writing word English: ");
                Scanner sc2=new Scanner(System.in);
                String englishWord=sc2.nextLine();
                System.out.println(Main.Avl_Tree.get(englishWord));
                break;
            case 3:
                Main.Avl_Tree.print();
                break;
            case 4:
                System.out.println("Writing delete word English: ");
                Scanner sc3=new Scanner(System.in);
                String englishDeleteWord=sc3.nextLine();
                line.remove(englishDeleteWord+'-'+Main.Avl_Tree.get(englishDeleteWord));
                this.deleteWord();
                Main.Avl_Tree.delete(englishDeleteWord);
                break;
            case 5:
                for(Integer otstyp=0;otstyp<25;otstyp++){
                    System.out.println('\n');
                }
                break;
            case 6:
                flag=false;
                break;
        }
        return flag;
    }

    @Override
    public void inFile(String word) {
        try {
            bw=new BufferedWriter(new FileWriter("C:\\Users\\Анна\\Desktop\\Имитатор машины Тьюринга_files\\WordEng.txt",true));
            bw.newLine();
            bw.write(word);
            bw.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void fromFile() {
        Integer iterator=0;
        try {
            br=new BufferedReader(new FileReader("C:\\Users\\Анна\\Desktop\\Имитатор машины Тьюринга_files\\WordEng.txt"));
            while(true){
                line.add(br.readLine());
                if(line.get(iterator)!=null) {
                    String[] divideStr = line.get(iterator).split("-");
                    Main.Avl_Tree.add(divideStr[0], divideStr[1]);
                    iterator++;
                } else break;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    void deleteWord() {
        try {
            bwArrayList=new BufferedWriter(new FileWriter("C:\\Users\\Анна\\Desktop\\Имитатор машины Тьюринга_files\\WordEng.txt"));
            for(String arrayLineNew: line){
                if (arrayLineNew==null) break;
                bwArrayList.write(arrayLineNew);
                bwArrayList.flush();
                bwArrayList.newLine();
                bwArrayList.flush();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


Words.java // это файл затри к хуям комментарий и сделай название как название файла


import java.util.ArrayList;

/**
 * Абстрактный класс
 * Оъекты не могут быть созданы
 * Реализация при Наследовании
 * Реализация Наследования и Чистых Виртуальных методов(как в си)-Полиморфизм
 */
public abstract class Words {
    abstract void inFile(String word);
    abstract void fromFile();
    abstract void deleteWord();
}

Node.java// это файл затри к хуям комментарий и сделай название как название файла


class AVL <Key extends Comparable<Key>, Value> {
    public class Node {
        private int h;
        private int balance;
        Key key;
        Value value;
        private Node left, right, father;
        public Node (Key key, Value value, Node father) {
            this.key = key;
            this.value = value;
            this.left = this.right = null;
            this.father = father;
            this.h = 1;
            this.balance = 0;
        }
        public Node next(){
            return getHigherNode(this.key);
        }
        public Node previus(){
            return getLowerNode(this.key);
        }
    }

    private Node root;

    private Node getHigherNode(Key key) {
        Node p = root;
        while (p != null) {
            int cmp = key.compareTo(p.key);
            if (cmp < 0) {
                if (p.left != null)
                    p = p.left;
                else
                    return p;
            } else {
                if (p.right != null) {
                    p = p.right;
                } else {
                    Node father = p.father;
                    Node ch = p;
                    while (father != null && ch == father.right) {
                        ch = father;
                        father = father.father;
                    }
                    return father;
                }
            }
        }
        return null;
    }
    private Node getLowerNode(Key key) {
        Node p = root;
        while (p != null) {
            int cmp = key.compareTo(p.key);
            if (cmp > 0) {
                if (p.right != null)
                    p = p.right;
                else
                    return p;
            } else {
                if (p.left != null) {
                    p = p.left;
                } else {
                    Node father = p.father;
                    Node ch = p;
                    while (father != null && ch == father.left) {
                        ch = father;
                        father = father.father;
                    }
                    return father;
                }
            }
        }
        return null;
    }

    public Node getFirstNode(){
        return min(root);
    }

    public Node getLastNode(){
        return max(root);
    }

    private int height(Node x, Node y){
        if(x == null && y == null) return 0;
        else if(x == null) return y.h;
        else if(y == null) return x.h;
        else return Math.max(x.h, y.h);
    }

    private int balance(Node x, Node y){
        if(x == null && y == null) return 0;
        else if(x == null) return - y.h;
        else if(y == null) return x.h;
        else return x.h - y.h;
    }

    private Node add (Node node,Key key, Value value, Node father){
        if (node == null) {
            Node newnode = new Node(key, value, father);
            return newnode;
        }
        int compareResult = key.compareTo(node.key);
        if (compareResult > 0){node.right = add(node.right, key, value, node); node.h = height(node.left, node.right) + 1;}
        else if(compareResult < 0){node.left = add(node.left, key, value, node); node.h = height(node.left, node.right) + 1;}
        else{
            node.value = value;
        }
        node.balance = balance(node.left, node.right);
        if(node.balance == -2){
            node = leftRotation(node);
        }else if(node.balance == 2){
            node = rightRotation(node);
        }
        return node;
    }

    private Node leftRotation(Node node) {
        if(node.right.right == null && node.right.left != null){
            node.right = rightRotation(node.right);
            node = leftRotation(node);
        }else if(node.right.left == null || node.right.left.h <= node.right.right.h){
            Node newnode = node.right;
            newnode.father = node.father;
            node.right = newnode.left;
            if(node.right != null)
                node.right.father = node;
            node.h = height(node.left, node.right)+1;
            node.father = newnode;
            node.balance = balance(node.left, node.right);
            newnode.left = node;
            node = newnode;
            node.balance = balance(node.left, node.right);
            node.h = height(node.left, node.right)+1;
        }else{
            node.right = rightRotation(node.right);
            node = leftRotation(node);
        }
        return node;
    }
    private Node rightRotation(Node node){
        if(node.left.right != null && node.left.left == null){
            node.left = leftRotation(node.left);
            node = rightRotation(node);
        }else if(node.left.right == null || node.left.right.h <= node.left.left.h){
            Node newnode = node.left;
            newnode.father = node.father;
            node.left = newnode.right;
            if(node.left != null)
                node.left.father = node;
            node.h = height(node.left, node.right)+1;
            node.father = newnode;
            node.balance = balance(node.left, node.right);
            newnode.right = node;
            node = newnode;
            node.balance = balance(node.left, node.right);
            node.h = height(node.left, node.right)+1;
        }else{
            node.left = leftRotation(node.left);
            node = rightRotation(node);
        }
        return node;
    }

    public void add(Key key, Value value) {
        root = add(root, key, value, null);
    }

    private Node delete(Node node, Key key){
        if(node == null) return null;
        int compareResult = key.compareTo(node.key);
        if(compareResult > 0){
            node.right = delete(node.right, key);
        }else if(compareResult < 0){
            node.left = delete(node.left, key);
        }else{
            if(node.right == null && node.left == null){
                node = null;
            }else if(node.right == null){
                node.left.father = node.father;
                node = node.left;
            }else if(node.left == null){
                node.right.father = node.father;
                node = node.right;
            }else{
                if(node.right.left == null){
                    node.right.left = node.left;
                    node.right.father = node.father;
                    node.right.father = node.father;
                    node.left.father = node.right;
                    node = node.right;
                }else{
                    Node res = min(node.right);
                    node.key = res.key;
                    node.value = res.value;
                    delete(node.right, node.key);
                }
            }
        }
        if(node != null) {
            node.h = height(node.left, node.right) + 1;
            node.balance = balance(node.left, node.right);
            if (node.balance == -2) {
                node = leftRotation(node);
            } else if (node.balance == 2) {
                node = rightRotation(node);
            }
        }
        return node;
    }

    public void delete(Key key) {
        root = delete(root, key);
    }

    public Key minKey(){
        return min(root).key;
    }

    public Key maxKey(){
        return max(root).key;
    }

    private Node min(Node node){
        if(node.left == null) return node;
        return min(node.left);
    }

    private Node max(Node node){
        if(node.right == null) return node;
        return min(node.right);
    }

    private Value get(Node node, Key key){
        if(node == null) return null;
        int compareResult = key.compareTo(node.key);
        if(compareResult == 0){
            return node.value;
        }else if(compareResult > 0){
            return get(node.right, key);
        }else{
            return get(node.left, key);
        }
    }

    public Value get(Key key) {
        return get(root, key);
    }

    private void print(Node node, int level) {
        if (node != null) {
            print(node.left,level+1);
            System.out.println(node.key + "-" + node.value);
            print(node.right,level+1);
        }
    }

    public void print() {
        print(root,0);
    }
}
