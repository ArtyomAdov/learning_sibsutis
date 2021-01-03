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
