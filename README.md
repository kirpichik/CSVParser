# Simple CSV Parser

Простой header-only парсер CSV на рекурсивных шаблонах C++.

[Задание здесь.](https://docs.google.com/document/d/1FXmDYtpTG6WsjFtm9lysJbni3InftOnkLLeVQ8VwDVY/edit?ts=58423c1a)

## Создание парсера

```
csv::CSVParser<%типы колонок%> parser(stream, %кол-во строк%);
```

Типами колонок может быть любой тип, который имеет перегрузку оператора >>.

Первый аргумент конструктора это поток из которого парсер будет считывать таблицу, 
а второй это количество строк, которые будут пропущены в потоке перед тем, как начать
считывать таблицу.

## Предварительная настройка

Парсер имеет функции настройки для различных символов разделителей.

### Разделитель строк:

```
parser.setLineDelimiter(const char)
```

### Разделитель колонок:

```
parser.setColoumnDelimiter(const char)
```

### Символ экранирования:

Для того, чтобы можно было в колонке таблицы написать символы, которые эквиваленты
символам разделителей колонок, например:

Разделитель колонок: символ ','

Символ экранирования: символ '\'

Тогда колонка в парсере с символом разделителя будет записана:

test1\\, test2,test3\\, test4

```
parser.setEscapingSymbol(const char)
```

## Вывод значений таблицы

Итератор по парсеру.

```
for (std::tuple<std::string, int, int, std::string> line : parser) {
  std::cout << line << std::endl;
}
```

При первом проходе парсер считывает строки из потока и сохраняет их в буфер.

При последующих итерациях чтение происходить не будет.

