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

