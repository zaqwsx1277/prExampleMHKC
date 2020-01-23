#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

#include <cassert>

static const int numPos {2} ;             // позиция для поиска отсчетов в списке

typedef std::pair <int, int> tdInData ;   // typedef для одного отсчета

//---------------------------------------------------------
struct stCmpX   // Cортировкa исходного контейнера по отсчётам
{
    bool operator () (const tdInData& inData1, const tdInData& inData2) const {
        return inData1.first < inData2.first  ;
    }
};
//---------------------------------------------------------
/*!
 * \brief foo Тестовая функция.
 */
void foo()
{
                                        // Контейнер содержащий исходный набор данных
    std::vector <tdInData> setInData {{1, 10}, {2, 11}, {3, 11}, {4, 11}, {5, 11}, {6, 10}, {7, 11}, {8, 11}, {9, 11}, {10, 11}, {11, 10}} ;
    std::set <tdInData, stCmpX> result ;     // Контейнер содержащий результат

    auto it = setInData.cbegin() ;
    while (true) {
        result.insert(*it) ;
                                             //  Ищем граничный элемент идентичной последовательности
        auto itSecond = std::find_if_not (it, setInData.cend(), [&] (const tdInData& inData) { return (inData.second == (*it).second) ; } ) ;
        for (auto it2 = it; it2 != itSecond; ++it2) {     // Поиск отсчёта в позиции кратной numPos
            if ((std::distance (it, it2) + 1) % numPos == 0)
                result.insert(*it2) ;
        }
        if (std::distance (it, itSecond) > 1) result.insert(*std::prev (itSecond)) ; // Если в идентичной последовательности больше одного элемента, то добавляем элемент из конца списка
        if (itSecond == setInData.cend()) break ;
        it = itSecond ;                     // Устанавливаем начало следующей идентичной последовательности
    }
    for (auto item : setInData) std::cout << "(" << item.first << ", " << item.second << "), " ;
    std::cout << std::endl ;
    for (auto item : result) std::cout << "(" << item.first << ", " << item.second << "), " ;
    std::cout << std::endl ;
}
//-------------------------------------------------------------
int main()
{
    assert (numPos > 2 && "Искомая позиция n-ного отсчёта меньше 3-х!!!") ;               // Тупо остановим выполнение, если искомая позиция n-ного отсчета меньше 3

    foo () ;

    return 0 ;
}
