import os
import module_read as mr
import module_print as mp
import module_search as ms

def menu():
    print("1) Read data of currency from coinmarketcap")
    print("2) Search currency by name")
    print("3) Print data")
    print("9) Clear screen")
    print("0) Exit")


def start_programm():
    dictionary_currency = dict()
    while 1:
        menu()
        key_choise = int(input())
        if key_choise == 1:
            dictionary_currency=mr.read_currency(dictionary_currency)
        elif key_choise == 2:
            if(len(dictionary_currency) == 0):
                print("error: need read currency")
            else:
                ms.search_currency(dictionary_currency)
        elif key_choise == 3:
            if(len(dictionary_currency) == 0):
                print("error: need read currency")
            else:
                mp.print_currency(dictionary_currency)
        elif key_choise == 9:
            os.system('cls')
        elif key_choise == 0:
            break
        else:
            print("incorrectly choise")
            print("please input 1 or 2 or 3 or 9 or 0")

if __name__ == "__main__":
    start_programm()