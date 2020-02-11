# Parsing command line arguments

> ### GNU getopt
> [documentation](https://www.gnu.org/savannah-checkouts/gnu/libc/manual/html_node/Getopt.html) | GPL license
> \- Очень низкоуровневый для C++
> \- Кода получается много и он плохо читается
> \- Использует POSIX библиотеки. Сложно заставить работать под Windows
> \+ Очень просто добавить в проект под linux (подключить стандартную библиотеку)
> \+ Использует коды ошибок,
в проекте было принято решение использовать коды ошибки при неправильном вводе от пользователя, а не исключения

> ### Boost Program_options
> [documentation](https://www.boost.org/doc/libs/1_72_0/doc/html/program_options.html) | Boost Software license
> \- Неудобный интерфейс для простой программы
Появляется много сущностей options_description/variables_map, необходимы допольнительные действия store/notify
> \+ Очень хорошо настраивается, можно заставить работать с любым форматом аргументов
(например добавить свой парсер)
> \+ Boost уже используется в проекте. Добавить будет легко

> ### TCLAP
> [documentation](http://tclap.sourceforge.net) | MIT license
> \+ Субъективно, самый удобный интерфейс для простой программы
> \+ header-only, несложно добавить

> ### Lean Mean C++
> [documentation](http://optionparser.sourceforge.net/index.html) | MIT license
> \+ Удобный и простой
> \+ Использует коды ошибок
> \+ header-only, несложно добавить
> \- Не поддерживает автоматическую конвертацию типов

> ### AnyOption
> [documentation](https://github.com/hackorama/AnyOption) | MIT license
> \+ Удобный и простой
> \+ header-only, несложно добавить
> \- Страшные define в библиотеке. Некоторые из них (вроде MAX OPTIONS) нужно настраивать самостоятельно. 
> \- Мало пользователей и тесты выгядят неубедительно. Нет доверия

# Выбор парсера
Было принято решение использовать в проекте TCLAP, как одну из простых библиотек с удобным интерфейсом и без заметных на первый взгляд проблем
