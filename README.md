## Параллельное вычисление
1) **Задание**: *Вычислить факториал числа с использованием многопоточности. Разделить вычисление на несколько потоков, где каждый поток вычисляет факториал для своего диапазона чисел. Объединить результаты от каждого потока, чтобы получить итоговый результат.*

**Файлы**: ```lab_factorial.cpp```

2) **Задание**: *Создать программу, имитирующую ситуацию, в которой несколько потоков одновременно пытаются получить доступ к общему ресурсу. Использовать мьютексы для синхронизации доступа к общим данным.*

**Файлы**: ```parallel_laba_2.cpp```

3) **Задание**: *Вывести приветствие несколько раз. Ввести количество потоков и вывести порядок потоков.*

**Файлы**: ```parallel_practice_1.cpp```

4) **Задание**: *а) Заполнить массив случайными числами, посчитать сумму элементов. б) Отсортировать массив без использования параллельных вычислений и с использованием. Сравнить результаты и время работы.*

**Файлы**: ```practice_openmp.cpp```

5) **Задание**: *Найти самое часто встречающееся слово в текстовом файле.*

**Файлы**: ```practice_word_text.cpp``` и ```Хоббит.txt```

6) **Задание**: *Выполнить преобразования изображения*

**Файлы**: ```practice_conv_image.cpp``` и ```image.jpg```

7) **Задание**: *Ускорить при помощи параллельных вычислений работу программы ```opencv_practice_face.cpp``` из ветки **OpenCV**.*

**Файлы**: ```practice_face.cpp```

**Результат**: Время работы *opencv_practice_face.cpp* = 169сек. Время работы *practice_face.cpp* = 118сек. Выигрыш по времени ~30%.
