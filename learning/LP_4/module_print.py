from collections import defaultdict


def print_currency(dictionary_currency):
    number = 0
    print(' '+'name' + '            ', 'market' + '               ', 'price')
    for item in dictionary_currency.items():
        number += 1
        print(str(number) + ')', *item)

    