#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <string>

/*
vector'deki yinelenen öğeleri bulmak için genel fonksiyon.
Yinelenen öğeleri ve bunların yinelenme sayılarını verilen countMap map'ine ekler.
*/
template <typename T>
void findDuplicates(std::vector<T> & vecOfElements, std::map<T, int> & countMap)
{
    // vector üzerinde ilerle ve her bir öğenin sıklığını map'te sakla
    for (auto & elem : vecOfElements)
    {
        auto result = countMap.insert(std::pair<T, int>(elem, 1));
        if (result.second == false)
        {
            result.first->second++;
        }
    }

    // Frekansları 1 olan öğeleri map'ten kaldır
    for (auto it = countMap.begin(); it != countMap.end();)
    {
        if (it->second == 1)
        {
            it = countMap.erase(it);
        }
        else
        {
            it++;
        }

    }
}

int main()
{
    // karakter katarları için vector
    std::vector<std::string> vecOfStrings{"merhaba", "selam", "merhaba", "naber", "selam", "nasılsın", "naber",
                                          "merhaba", "selam" , "bir", "iki", "iki", "selam", "naber"};

    std::map<std::string, int> duplicateElements;

    // Yinelenen öğeleri vector olarak al
    findDuplicates(vecOfStrings, duplicateElements);

    for (auto &elem : duplicateElements)
    {
        std::cout << elem.first << ": " << elem.second << std::endl;
    }

    // Sayılar için vector
    std::vector<int> vecOfInts{1, 1, 1, 2, 2, 3, 3, 3, 3, 3, 5, 5, 5, 5};

    std::map<int, int> duplicateElements2;

    // Yinelenen öğeleri vector olarak al
    findDuplicates(vecOfInts, duplicateElements2);

    for (auto &elem : duplicateElements2)
    {
        std::cout << elem.first << ": " << elem.second << std::endl;
    }

    return 0;
}
