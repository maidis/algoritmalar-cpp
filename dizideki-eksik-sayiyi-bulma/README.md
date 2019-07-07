# Dizideki Eksik Sayıyı Bulma

n boyutunda, 1'den n'e kadar tamsayılardan oluşan bir dizimiz olduğunu varsayalım. Listede birbirinin aynısı olan eleman da bulunmasın. Dizide bulunmayan bir şey daha olsun, bir kayıp, eksik bir sayı... Eksik tamsayıyı bulmak için etkili bir kod yazmak tam da bize göre bir iş değil mi sizce de?

```cpp
std::array<int, 8> a1{ {1, 2, 4, ,6, 3, 7, 8} };
```

yukarıdaki gibi bir dizide `5`'in eksik olduğunu bulan bir program yazalım.

## Toplama Formülünü Kullanarak Eksik Sayıyı Bulma

Bu problemi çözmek için toplam formülünü aşağıdaki gibi bir algoritmayla birlikte kullanabiliriz:

1. Sayıların toplamını al: `total = n * (n + 1) / 2`
2. Tüm sayıları toplamdan çıkar ve eksik sayıyı bul.

```cpp
#include <iostream>
#include <array>

template<std::size_t SIZE>
unsigned long long findMissing(std::array<int, SIZE>& arr)
{
    unsigned long long total;
    total = (SIZE) * (SIZE + 1) / 2;
    for(auto& e : arr)
    {
        total -= e;
    }
    return total;
}

int main()
{
    std::array<int, 10> a1{ {10, 2, 5, 6, 3, 7, 8, 4, 9} };
    int miss = findMissing(a1);
    std::cout << miss;
    return 0;
}
```

```
2 3

2 + 3 = 5

(3 * 4) / 2 = 6

6 - 5 = 1

```

`std::array`'i fonksiyona geçmek için normalde boyutunu da bildirmemiz gerekir. Bu kullanımı sevmiyorsak yukarıdaki gibi değişken boyut kabul eden bir şablon oluşturabiliriz. Bu yöntemi de tercih etmek istemezsek `std::vector`'ü kullanabiliriz.

Bu çözümün karmaşıklığı O(n)'dir:

* Gauss Yöntemi: n * (n + 1) / 2 -> O(1)
* Döngü ile toplama -> O(n)

## XOR Kullanarak Eksik Sayıyı Bulma

Toplama formülünü kullanmak yeteri kadar zekiceydi ama daha ilginç bir şeyler arıyorsanız problemin XOR ile çözümünü inceleyebilirsiniz.

1. Tüm dizi öğeleri XOR'lanır, XOR'lama sonucu X1'de saklanır.
2. 1'den n'e kadar tüm sayılar XOR'lanır, XOR'lama sonucu X2'de saklanır.
3. X1 ve X2 XOR'lanır ve XOR'lama sonucu eksik sayıyı verir.

```cpp
#include <iostream>
#include <array>

template<std::size_t SIZE>
int findMissing(std::array<int, SIZE>& arr)
{
    int x1 = arr[0];
    int x2 = 1;

    for (int i = 1; i < SIZE; ++i)
    {
        x1 ^= arr[i];
    }

    for (int i = 2; i <= SIZE; ++i)
    {
        x2 ^= i;
    }

    return (x1 ^ x2);
}

int main()
{
    std::array<int, 10> a1{ {1, 2, 5, 6, 3, 9, 8, 4, 10} };

    std::cout << findMissing(a1) << std::endl;

    return 0;
}
```

```
2 3

10
11

10 ^ 11 = 01

1 2 3

01
10
11

01 ^ 10 = 11
11 ^ 11 = 00

01 ^ 00 = 01
```

## Sıralayarak Sırada Olmayana Bakarak Eksik Sayıyı Bulma

Önceki çözümler dışında akla gelebilecek bir yöntem de sıralama yapmaktır. Diziyi sıraladıktan sonra ilk önce uç durumları kontrol etmemiz gerekiyor. Dizinin ilk elemanı 1 değilse eksik olan sayı 1 ve dizinin son elemanı dizinin boyutuna eşit değilse bu eleman eksik demektir. Şimdi dizi üzerinde ilerleyebiliriz. Ardışık indeksler arasındaki fark 1'e eşit değilse eksik sayı, geçerli indeks + 1'e eşittir.

```cpp
#include <iostream>
#include <algorithm>
#include <array>

template<std::size_t SIZE>
int findMissing(std::array<int, SIZE>& arr)
{
    std::sort(arr.begin(), arr.end());

    if (arr.at(1) != 1) // arr.front() has 0
    {
        return 1;
    }
    else if (arr.back() != SIZE)
    {
        return SIZE;
    }
    else
    {
        for (int i = 0; i < SIZE; ++i)
        {
            if (arr.at(i + 1) - arr.at(i) != 1)
            {
                return arr.at(i) + 1;
            }
        }
    }
}

int main()
{
    std::array<int, 10> a1{ {3, 10, 5, 6, 7, 9, 8, 4, 1} };

    std::cout << findMissing(a1) << std::endl;

    return 0;
}
```

[//]: # (## Bloom Filtresi Kullanarak)

[//]: # (Bloom filtresi, 1970 yılında Burton Howard Bloom tarafından tasarlanan, bir elemanın bir kümenin üyesi olup olmadığını test etmek için kullanılan, alan açısından verimli bir olasılıksal veri yapısıdır.)

[//]: # (Yanlış pozitif eşleşmeler mümkündür, ancak yanlış negatifler yoktur. Başka bir deyişle, bir sorgu "muhtemelen kümede" veya "kesinlikle küme değil" ifadesini döndürür.)

[//]: # (Öğeler kümeye eklenebilir, ancak kaldırılamaz, kümeye ne kadar çok eleman eklenirse, yanlış pozitiflerin olasılığı o kadar artar.)

## Kaynaklar

* [Find the Missing Number - GeeksforGeeks](https://www.geeksforgeeks.org/find-the-missing-number/)
* [c++ - Passing a std::array of unknown size to a function - Stack Overflow](https://stackoverflow.com/questions/17156282/passing-a-stdarray-of-unknown-size-to-a-function)
* [Solutions to Find Missing Number in Array](https://gist.github.com/malchak/7575842)
* [java - Quickest way to find missing number in an array of numbers - Stack Overflow](https://stackoverflow.com/questions/2113795/quickest-way-to-find-missing-number-in-an-array-of-numbers)
* [Bir dizide olmayan integer'ı bulma problemi](https://github.com/msusur/kodlama-pratikleri/blob/master/sorular/dizide-olmayan-sayiyi-bulma.md)
* [Bloom filter - Wikipedia](https://en.wikipedia.org/wiki/Bloom_filter)
* [Day 60: Bloom Filter](https://medium.com/100-days-of-algorithms/day-60-bloom-filter-5ab01d0d1b06)
