#include <iostream>
#include <vector>
#include <map>

int main()
{
    // Sayılar için vector
    std::vector<int> vecOfInts{1, 1, 1, 2, 2, 3, 3, 3, 3, 3, 5, 5, 5, 5};

    // vector'deki her bir öğenin sıklığını saklamak için bir map oluştur
    std::map<int, int> countMap;

    // vector üzerinde ilerle ve her bir öğenin sıklığını map'te sakla
    for (auto &elem : vecOfInts)
    {
        auto result = countMap.insert(std::pair<int, int>(elem, 1));
        if (result.second == false)
        {
            result.first->second++;
        }
    }

    // map üzerinde ilerle
    for (auto &elem : countMap)
    {
        // Frekans sayısı 1'den büyükse bu, bir yinelenen öğedir
        if (elem.second > 1)
        {
            std::cout << elem.first << ": " << elem.second << std::endl;
        }
    }
}
