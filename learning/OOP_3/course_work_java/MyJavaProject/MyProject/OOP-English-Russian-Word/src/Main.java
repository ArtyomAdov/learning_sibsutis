import java.io.IOException;
import java.util.Scanner;

public class Main {
    static AVL<String,String> Avl_Tree=new AVL<>();
    public static void main(String[] args) throws IOException {
        Boolean flag=true;
        Menu menu=new Menu();
        while(flag) {
            Scanner sc=new Scanner(System.in);
            menu.menuSpisock();
            Integer chois=sc.nextInt();
            flag=menu.choiceMenu(chois);
        }
    }
}
