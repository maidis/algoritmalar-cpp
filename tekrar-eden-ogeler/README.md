# C++'ta Yinelenen Öğelerin Bulunması

Bu yazıda bir `vector`'deki yinelenen öğelerin nasıl bulunacağını ve bunların sayısının nasıl hesaplanacağını göreceğiz. Sayılardan oluşan aşağıdaki gibi bir `vector`'ümüz olsun:

```cpp
// Sayılar için vector
std::vector<int> vecOfInts{1, 1, 1, 2, 2, 3, 3, 3, 3, 3, 5, 5, 5, 5};
```

Bu listedeki yinelenen öğeleri ve yinelenme sayılarını bulalım. Örneğin, yukarıdaki `vector` için yinelenen öğeler ve yinelenme sayıları şöyledir:

```bash
1: 3
2: 2
3: 5
5: 4
```

Şimdi bunu gerçekte nasıl elde edeceğimizi görelim.


## Bir vector'deki yinelenenleri bulma

`vector`'deki her sayının sıklık sayısını içinde saklamak için bir `<int, int> map`'i oluşturalım. sonra da `vector`'deki tüm öğelerin üzerinde geçerek `map`'e, 1 değerine sahip bir anahtar olarak eklemeyi deneyelim. Sayı `map`'te zaten varsa, değerini bir artıralım.

```cpp
// vector'deki her bir öğenin sıklığını saklamak için bir map oluştur
std::map<int, int> countMap;

// vector üzerinde ilerle ve her bir öğenin sıklığını map'te sakla
for (auto & elem : vecOfInts)
{
    auto result = countMap.insert(std::pair<int, int>(elem, 1));
    if (result.second == false)
        result.first->second++;
}
```

Şimdi `map` üzerinde ilerleyelim ve değeri 1'den büyük olan öğeleri yazdıralım.

```cpp
// map üzerinde ilerle
for (auto & elem : countMap)
{
    // Frekans sayısı 1'den büyükse bu, bir yinelenen öğedir
    if (elem.second > 1)
    {
        std::cout << elem.first << ": " << elem.second << std::endl;
    }
}
```

`vector`'deki yinelenen öğeler ve bunların yinelenme sayıları şu şekilde yazdırılacaktır:

```bash
1: 3
2: 2
3: 5
5: 4
```

`map`, isminden de anlaşılabileceği gibi bir `anahtar-değer` çiftini saklamak için kullanılan bir taşıyıcıdır. `map`, üzerinde arama yapmak sadece `O(1)` zaman karmaşıklığına sahip olduğundan kullanımının diğer taşıyıcılara göre bir avantajları vardır. Örneğimizde eklene özelliğinden yararlanılmıştır.

`std::map::insert`, yeni öğeler ekleyerek taşıyıcıyı genişletir, taşıyıcının boyutu, eklenen öğelerin sayısıyla etkin bir şekilde arttırır.

Bir `map`'te öğe anahtarları benzersiz olduğundan, ekleme işlemi, eklenen her öğenin halihazırda taşıyıcıda bulunan bir öğeye eşdeğer bir anahtara sahip olup olmadığını kontrol eder, öğe halihazırda varsa ve yeni öğe eklenmediyse, mevcut öğeye bir iteratör döndürülür.

Yinelenen öğelere izin veren benzer bir taşıyıcı için `multimap`'e bakılabilir.

`std::map::insert`'ün tek öğeli sürümleri, bir pair döndürür:

```cpp
pair<iterator, bool>
```

`pair`'in `pair::first` üyesi, ya yeni eklenen öğeye ya da `map`'taki eşdeğer bir anahtara sahip öğeye işaret eden bir iteratöre ayarlanır. `pair::second` ise yeni bir öğe eklenirse `true`, eşdeğer bir anahtar mevcutsa `false` olarak ayarlanır.


## vector'deki yinelenen elemanları bulmak için genel fonksiyon

Şimdi de yinelenen öğeleri ve yinelenme sayılarını almak için genel bir fonksiyon oluşturalım.

```cpp
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
        auto result = countMap.insert(std::pair<std::string, int>(elem, 1));
        if (result.second == false)
            result.first->second++;
    }

    // Frekansları 1 olan öğeleri map'ten kaldır
    for (auto it = countMap.begin() ; it != countMap.end() ;)
    {
        if (it->second == 1)
            it = countMap.erase(it);
        else
            it++;

    }
}
```

Bu genel fonksiyonu, `vector`'deki yinelenen öğeleri bulmak için kullanalım:

```cpp
std::map<std::string, int> duplicateElements;

// Yinelenen öğeleri vector olarak al
findDuplicates(vecOfInts, duplicateElements);
```

Şimdi yinelenen öğeleri ve yinelenen öğelerin sayılarını yazdırmak için bu `map` üzerinde ilerleyelim.

```cpp
for (auto & elem : duplicateElements)
    std::cout << elem.first << " :: " << elem.second << std::endl;
```

Her şey yolunda gittiyse önceki kod parçasıyla aynı çıktıyı almamız gerekir:

```bash
1: 3
2: 2
3: 5
5: 4
```

Bu genel fonksiyonun iyi yönü, sadece tam sayılar üzerinde değil tüm türler üzerinde çalışabilmesidir.

Tam örnek aşağıdaki gibidir:

```cpp
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

```

Çıktı:

```bash
iki: 2
merhaba: 3
naber: 3
selam: 4
1: 3
2: 2
3: 5
5: 4
```

Örneği derlemek için aşağıdaki komut kullanılabilir:

```bash
g++ -std=c++11 tekrar-eden-ogeler2.cpp
```

## Kaynaklar
- [C++: How to find duplicates in a vector?](https://thispointer.com/c-how-to-find-duplicates-in-a-vector/)
- [map::insert - C++ Reference](http://www.cplusplus.com/reference/map/map/insert/)
- [C++ Map Insert Example](https://thispointer.com/c-map-insert-example/)
- [Inserting elements in std::map (insert, emplace and operator [])](https://www.geeksforgeeks.org/inserting-elements-in-stdmap-insert-emplace-and-operator/)
- [Listedeki Tekrar Eden Sayıları Bulma](https://algoritma-sorulari.blogspot.com/2018/12/elimizde-tamsaylardan-olusan-bir-liste.html)
