from collections import defaultdict


def search_currency(dictionary_currency):
    # запрос названия валюты
    print("Write need name of currency")
    search_name = str(input())
    if search_name in dictionary_currency:
        # вывод цены и маркета ,звёздочка ,чтобы не было глупых скобок
        print('market' + '       ' + 'price')
        print(*dictionary_currency[search_name])
    else:
        print("error: incorrectly name of currency")