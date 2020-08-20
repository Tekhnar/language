# Язык программирования GOP
Это мой язык программирования - "язык гопников". Раширение текстовых программ `.gop`.

### Важно!
Данный синтаксис для языка взят "just for fun" (про возможность изменения ключевых слов - ниже).

## Возможности языка
* Дифференцирование выражения
* Локальные переменные
* Рекурсивный вызов функции
* Вызов функции с аргументами
* Условные выражения, циклы и т.д.
## Синтаксис языка

`муйн`            - main()

`здорова`         - {

`вали`            - }


`ну че там`       - if

`за базар ответь` - else

`точняк больше`   - >

`точняк меньше`   - <

`че реально`      - ==

`побольше`        - >=

`поменьше`        - <=

`базарь`          - 	scanf  (%lg, ...)

`слышь`           - printf (%lg, ...)

`на кортах`       - while (...)

`выкинуть`        - return

`d(...)/d _var_`  - дифференцирование выражения по переменной _var_

Математические операторы для удобства оставлены без изменения.
Все ключевые команды можно поменять в файле `frontend/libraries/com_language.h` (**ОСТОРОЖНО**, файл в кодировке cp1251).
## Подпрограммы
* `frontend` - преобразовывает текст программы в AST
  
* `middle_end` - производит дифференцирование и оптимизацию математических конструкций
  * Первый аргумент при запуске - путь к файлу AST программы, после преобразований дерево записыввается в этот же файл
  
* `frontend_back` - по AST восстанавливает исходный текст (с выравниванием)

* `backend` - перевод из AST в мой ассемблер для выполнения на [моём виртуальном процессоре](https://github.com/Tekhnar/My_CPU)
  * Первый аргумент при запуске - путь к файлу программы в AST
* `backend_x86_x64` - перевод из AST в бинарный исполняемый файл `.exe`
  * Первым аргументом - путь до AST программы
  * После директивы `-o` указывается файл, в который будет записана указанная прогрмма
  * Директивой `-O1` или `-O0` указывается соответствующая оптимизация
  
Во всех подпрограммах директива `--d` включает режим отладки, при котором абстрактное синтаксическое дерево изображается в виде картинки
`.png` с именем запустившей подпрограммы.

## Тестирование

В `workspace/` лежат все скомпилированные подпрограммы языка (+ виртуальный процессор). В папке `workspace/compiler/` лежит `makefile`
для автоматической компиляции программ из папки `workspace/programs/` и дальнейшего запуска на виртуальном процессоре. 
**Все программы в данной папке скомпилированы под Linux x64.**

В `workspace_win64/` лежат скомпилированные подпрограммы языка (+ виртуальный процессор). В папке `workspace/compiler/` лежат `.bat`
файлы для автоматической компиляции программ из папки `workspace_win64/programs/` и дальнейшего запуска на виртуальном процессоре и/или `.exe` 
файла этой же программы, но уже напрямую переведенным в исполняемый файл. **Все программы в данной папке скомпилированы под Windows x64.**

## Подробнее о `backend_x86_x64`

Это компилятор, преобразующий абстрактное синтаксическое дерево в исполняемый файл `.exe`. 

Это последняя написанная программа из серии данных подпрограмм, отличительной особенностью которой является произведённый масштабный рефакторинг библиотеки по работе с деревьями - файлы `Tree.h` и `Tree.cpp`.

На данной программе проверим какой прирост в произодительности мы получаем при исполнении файла `.exe` с командами процессора 
Intel_x86_x64 в сравнении с виртуальным процессором.

Это факториал 10 вычисляемый 200000 раз.
```
fact (сиги)  здорова
	ну че там (сиги поменьше 1) здорова
		выкинуть 1
	вали
	за базар ответь
		выкинуть сиги * fact (сиги - 1)
вали


муйн () здорова
	номерок = 200000
	
	на кортах (номерок точняк больше 0) здорова
		число = 10
		fact (число)
		номерок = номерок - 1
	вали
вали
```

| Виртуальный процессор | Реальный процессор с Intel_x86_x64 оптимизация -O0 | Реальный процессор с Intel_x86_x64 оптимизация -O1 |
|:----------------:|:---------:|:----------------:|
|  45,6835 сек |  0,1404 сек |   0,0965 сек |

Важно отметить, что здесь `-O0` и `-O1` оптимизации ***моего*** компилятора.
Замеры производились с помощью команды Measure-Command { } в PowerShell.

Таким образом, время исполнения `.exe` файла с оптимизацией `-O1` у моего компилятора в ***473,4 раза меньше***, чем на виртуальном процессоре. 