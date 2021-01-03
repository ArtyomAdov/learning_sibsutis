import java.io.*;
import java.nio.Buffer;
import java.util.ArrayList;
import java.util.Scanner;

import static java.lang.Runtime.getRuntime;

public class Menu extends Words {
    private BufferedReader br;
    private BufferedWriter bw;
    private BufferedWriter bwArrayList;
    private ArrayList<String> line=new ArrayList<>();

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
        switch (choice) {
            case 0:
                line.clear();
                this.fromFile();
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
            bw=new BufferedWriter(new FileWriter("C:\\Users\\kitos\\IdeaProjects\\OOP-English-Russian-Word\\Words.txt",true));
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
            br=new BufferedReader(new FileReader("C:\\Users\\kitos\\IdeaProjects\\OOP-English-Russian-Word\\Words.txt"));
            while(true){
                line.add(br.readLine());
//                System.out.println(line);
                if(line.get(iterator)!=null) {
                    String divideStr[] = line.get(iterator).split("-");
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
            bwArrayList=new BufferedWriter(new FileWriter("C:\\Users\\kitos\\IdeaProjects\\OOP-English-Russian-Word\\Words.txt"));
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
