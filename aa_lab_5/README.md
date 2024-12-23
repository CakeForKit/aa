# Анализ алгоритмов

## Лаб 5

Вариант:

1. Считать из txt файла строки (не менее 256) вида <строковый ключ из символов a-zA-Z0-9>: <число>

2. Выполнить раскладку чисел в группы (не более чем в N, N — по умолчанию количество логических ядер машины, но оставить возможность задать) так, чтобы разница максимальной и минимальной среди сумм чисел каждой группы была наименьшей

3. Записать в N файлов с именами group_<i>.<имя исходного файла>.txt, где i — номер группы из п. 2, каждую группу в формате

<сумма чисел группы>
<ключ1>: <значение1>
…
<ключN>: <значениеN>

Ключи должны быть отсортированы в лексикографическом порядке по возрастанию



### Основное задание

Цель работы
Получить навык организации параллельных вычислений по конвейерному принципу.

Общие требования и определения
Отчет необходимо оформлять в соответствии с требованиями, которые размещены в разделе "Файлы". В случае затруднений обратиться к преподавателю.

Обязательно использование нативных потоков (и, следовательно, языка, поддерживающего такие потоки).
Допускаются корутины (например, go). Конкретный язык необходимо согласовать с преподавателем.

Под задачей понимается собственно процесс обработки от начала и до конца. Каждой задаче необходимо поставить в соответствие некоторый уникальный идентификатор задачи (например, порядковый номер, выражающийся натуральным числом).

Для каждой задачи необходимо логировать в хронологическом порядке:

- время создания задачи;
- время постановки задачи в каждую из очередей;
- время начала обработки на каждой из стадий;
- время уничтожения задачи.

В ходе исследования необходимо получить следующие характеристики:

- среднее время существования задачи;
- среднее время ожидания задачи в каждой из очередей;
- среднее время обработки задачи на каждой из стадий.

Вариант по умолчанию
По умолчанию лабораторные работы №4 и №5 объединены общим вариантом и могут быть выполнены и защищены как совместно, так и по отдельности.

Требуется разработать ПО, которое осуществляет обработку данных, полученных от ПО, разработанного в ходе выполнения лабораторной работы №4, в несколько стадий в конвейерном режиме.

Стадии обработки:

- чтение данных из файла;
- излечение необходимого подмножества данных;
- запись извлеченных данных в хранилище.

В рассматриваемом процессе обработки данных каждому входному файлу соответствует единственная задача (в смысле, указанном в общих требованиях).

Необходимо создать как минимум по одному дополнительному потоку,
выполняющему назначенную ему стадию обработки, то есть как минимум один поток выполняет чтение, как минимум один выполняет извлеченные данных и т. д. Каждый такой поток выбирает задачи из входной очереди и помещает их после обработки в выходную очередь.

Кроме того, необходимо создать поток-генератор задач, т. е. поток, выполняющий создание задач путем чтения имен файлов, создания для каждого имени своей задачи и постановку их в очередь обработки первой стадии. Также необходимо создать поток-накопитель задач, т. е. поток, выполняющий выборку задач из
выходной очереди задач потока завершающей стадии обработки. Этот поток должен выполнять логирование и уничтожать задачу.

Предметная область для варианта по умолчанию
Для каждого рецепта необходимо сохранить (`моноширинным` приводятся названия полей/колонок/атрибутов в БД):

- `id` --- уникальный идентификатор задачи (не из Redmine, см. задание к работе) на обработку рецепта;
- `issue_id` --- номер задачи из Redmine;
- `url` --- URL страницы рецепта;
- `title` --- название рецепта, например, `"Пирог с малиной"`;
- `ingredients` --- массив ингредиентов, каждый ингредиент -- словарь вида (пример на JSON) `{"name": название, "unit": единица измерения, "quantity": количество}`, например, `{"name": "малина", "unit": "гр.", "quantity": 200}`;
- `steps` --- шаги рецепта, массив строк, она строка - одно предложение;
- `image_url` --- URL основного изображения рецепта (если есть).

В извлеченных данных строкового типа исключить html-теги, пустые строки, мусор из знаков препинания и/или спецсимволов вроде `!!!`, `\n\n\n\n`, ` ` и аналогичных.

Информацию необходимо сохранять в БД. БД разрешается выбирать любую такую, которая удовлетворяет требованиям:

- знакома студенту;
- позволяет получить дамп данных в JSON в формате выше.

Примечание: БД использовать обязательно в учебных целях, нельзя просто записать в JSON.

Индивидуальный вариант
Допускается замена варианта выше на индивидуальный. Для такой замены необходимо обратиться к преподавателю. В этом случае применяется задание ниже.

Требуется разработать ПО, которое осуществляет обработку данных в несколько стадий (не менее трех) в конвейерном режиме.

Необходимо создать как минимум по одному дополнительному потоку,
выполняющему назначенную ему стадию обработки. Каждый такой поток выбирает задачи из входной очереди и помещает их после обработки в выходную очередь.

Кроме того, необходимо создать поток-генератор задач, т. е. поток, выполняющий создание задач и постановку их в очередь обработки первой стадии. Также необходимо создать поток-накопитель задач, т. е. поток, выполняющий выборку задач из
выходной очереди задач потока завершающей стадии обработки. Этот поток должен выполнять логирование и уничтожать задачу.



