# библиотека ,которая помогает работать с ссылками ,а именно http
import requests
# для легкого добавления двух значений в словарь
from collections import defaultdict
# незаменимая фигня для парсинга ,которая помогает выбрать какой блок на сайте с помощью html и css
from bs4 import BeautifulSoup as BS


def read_currency(dictionary_currency):
    # использование импута для словарей
    dictionary_currency = defaultdict(list)
    # пишем ссылку главную страницу ,чтобы получить с неё html код
    r = requests.get('https://coinmarketcap.com')
    # тут выбираем ,что будем использовать
    html = BS(r.content, 'html.parser')
    # для выбора ,что будем выводить
    for el in html.select('.cmc-table-row'):
        # выбираем название крипто валют
        name = el.select('.cmc-table__column-name > a')
        # выбираем маркет
        market_cap = el.select('.cmc-table__cell--sort-by__market-cap')
        # выбираем цену
        price_cap = el.select('.cmc-table__cell--sort-by__price')
        dictionary_currency[name[0].text].append(market_cap[0].text)
        dictionary_currency[name[0].text].append(price_cap[0].text)
    return dictionary_currency