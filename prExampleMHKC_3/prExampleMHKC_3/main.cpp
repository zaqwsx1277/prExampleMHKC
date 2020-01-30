#include <iostream>

#include <cassert>
#include <vector>
#include <algorithm>

//-----------------------------------------------------------------------------------
static const int numPos {4} ;             // позиция для поиска отсчетов в списке

typedef std::pair <int, int> tdInData ;   // typedef для одного отсчета
//---------------------------------------------------------
/*!
 * \brief foo Тестовая функция.
 */
void foo()
{
    // Контейнер содержащий исходный набор данных
    std::vector <tdInData> inData {{1, 10}, {2, 11}, {3, 11}, {4, 11}, {5, 11}, {6, 10}, {7, 11}, {8, 11}, {9, 11}, {10, 11}, {11, 10}} ;

    for (auto item : inData) std::cout << "(" << item.first << ", " << item.second << "), " ;
    std::cout << std::endl ;

    int numPosCurrent = 1 ;             // текущая позиция в непрерывной последовательности
    auto it = inData.begin() ;
                                        // прореживание исходного контейнера
    for (; it != inData.end() - 1; ++it, ++numPosCurrent) {
        auto itNext = it + 1 ;
        if ((*it).first > (*itNext).first) break ;      // признак полного прореживания контейнера
        if ((*it).second != (*itNext).second) {         // Оставляем последний отсчёт идентичной последовательности
            numPosCurrent = 0 ;
            continue ;
        }
        if (numPosCurrent == 1) continue ;              // Оставляем первый отсчёт идентичной последовательности
        if (numPosCurrent % numPos == 0) continue ;     // Оставляем отсчет в позиции кратной numPos
        std::rotate (it, it + 1, inData.end()) ;        // если мы сюда попали, то отсчёт нужно удалить и он переносится в конец контейнера
        --it ;
    }

    inData.erase(it + 1, inData.end()) ;                // очистка контейнера от удаленных элементов
    for (auto item : inData) std::cout << "(" << item.first << ", " << item.second << "), " ;
    std::cout << std::endl ;

}
//--------------------------------------------------------
int main()
{
    assert (numPos > 2 && "Искомая позиция n-ного отсчёта меньше 3-х!!!") ;               // Тупо остановим выполнение, если искомая позиция n-ного отсчета меньше 3

    foo () ;

    return 0 ;
}
//--------------------------------------------------------
