# Шаблонный класс Matrix.<br>
Работает с любыми примитивными типами данных: short, int, char, float, double и другими.<br>
Класс разработан на языке C++ стандарта C++17 используя компилятор gcc.<br>
Полное покрытие unit-tests используя библиотеку GTest.<br>
Makefile для сборки (цели: all, clean, test, static-test, leaks, gcov-report).<br>

### Для создания матрицы, заполненной нулями реализованы конструкторы:
  `auto mtx = Matrix<int>(5, 5);` - достаточно передать конструктору два целочисленных значения(кол-во строк и столбцов)<br>
  `auto mtx = Matrix<double>(5);` - или одно значение для создания квадратной матрицы<br>
  `mtx(3,2) = 15.5;` - задавать значение по индексу используя круглые скобки<br>
  `double var = mtx(3,2);` - получать значение по индексу используя круглые скобки<br>

Так в классе перегружены операторы `>`, `<`, `==`, `!=`, `>=`, `<=`, `+`, `-`, `+=`, `-=`, `*`.

### Класс обладает такими функциями как:<br>
  `auto eqMatrix(const Matrix<T> &other) const  -> bool`       проверка на равенство<br>
  `auto sumMatrix(const Matrix<T> &other)       -> void`       сложение<br>
  `auto subMatrix(const Matrix<T> &other)       -> void`       вычитание<br>
  `auto mulMatrix(const Matrix<T> &other)       -> void`       умножение на матрицу<br>
  `auto mulNumber(T num)                        -> void`       умножение матрицы на число/умножение числа на матрицу<br>
  `auto determinant()                           -> double`     нахождение детерминанта матрицы<br>
  `auto calcComplements()                       -> Matrix<T>`  нахождение матрицы алгебраических дополнений<br>
  `auto inverseMatrix()                         -> Matrix<T>`  вычисление обратной матрицы<br>
  `auto transpose()                             -> Matrix<T>`  транспонирование матрицы<br>


### Для запуска тестов в Docker:<br>
`make docker-run` предварительно запустив Docker
