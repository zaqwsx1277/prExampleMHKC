#include <iostream>

#include <cassert>

//-----------------------------------------------------------------------------------
static const int numPos {4} ;             // позиция для поиска отсчетов в списке

typedef std::pair <int, int> tdInData ;   // typedef для одного отсчета
//---------------------------------------------------------
/*!
 * \brief checkLast     Проверка является ли элемент идентичной последовательности последним
 * \param inItem        Указатель на проверяемый элемен
 * \return              Если проверяемый элемент последний, то возвращается true
 */
bool checkLastPos (tdInData *inItem)
{
    bool retValue {false} ;
    tdInData *nextItem = inItem + 1 ;
    if (inItem -> second != nextItem -> second) retValue = true ;
    return retValue ;
}
//---------------------------------------------------------
/*!
 * \brief foo Тестовая функция.
 */
void foo()
{
                                                            // Контейнер содержащий исходный набор данных
        tdInData setInData [] {{1, 10}, {2, 11}, {3, 11}, {4, 11}, {5, 11}, {6, 10}, {7, 11}, {8, 11}, {9, 11}, {10, 11}, {11, 10}} ;

        std::size_t setInDataSize = sizeof (setInData) / sizeof (tdInData) ;        // Получаем кол-во элементов в массиве
                                                            // Выводим первоначальный массив
        for (std::size_t i = 0; i < setInDataSize; ++i)
            std::cout << "(" << setInData[i].first << ", " << setInData[i].second << "), " ;
        std::cout << std::endl ;

        int numIdenticalSeq {1} ;           // Значение текущей позиции в идентичной последовательности
                                                            // Основной цикл прореживания
        for (std::size_t i = 0; i < setInDataSize - 1; ++i, ++numIdenticalSeq) {
            if (numIdenticalSeq == 1) {                     // Оставляем первый элеинт идентичной последовательности
                numIdenticalSeq = checkLastPos (&setInData [i]) ? 0 : numIdenticalSeq ; // Проверяем, не является ли элемент единственным в идентичной последовательности
                continue ;
            }
            if (checkLastPos (&setInData [i])) {            // Оставляем последний элемент идентичной последовательности
                numIdenticalSeq = 0 ;
                continue ;
            }
            if (numIdenticalSeq % numPos == 0) continue ;   // Проверяем номер позиции на кратность numPos

            for (std::size_t j = i; j < setInDataSize - 1; ++j) setInData [j] = setInData [j + 1] ; // Удаляем "ненужный" отсчёт
            setInData [setInDataSize - 1] = tdInData {0, 0} ; // Забиваем нулями "последний" отсчет
            --setInDataSize ;                                // Уменьшаем размер массива
            --i ;
        }
                                                            // Выводим результирующий массив
        for (std::size_t i = 0; i < setInDataSize; ++i)
            std::cout << "(" << setInData[i].first << ", " << setInData[i].second << "), " ;
        std::cout << std::endl ;
}

int main()
{
    assert (numPos > 2 && "Искомая позиция n-ного отсчёта меньше 3-х!!!") ;               // Тупо остановим выполнение, если искомая позиция n-ного отсчета меньше 3

    foo () ;

    return 0 ;
}
