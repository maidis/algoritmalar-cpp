# 3 veya 5'e Bölünebilen Doğal Sayıların Toplamı

Kullanıcı tarafından girilen belirli bir sınır değere kadar, 3 veya 5 ile bölünebilen tüm doğal sayıların toplamını hesaplayan ve yazdıran bir program yazmamız gerektiğini düşünelim.

Bu sorunun çözümü için 3'ten (1 ve 2, 3 ile bölünemeyen sayılardan olduğundan bunları kontrol etmeye gerek yoktur) kullanıcı tarafından girilen sınır değere kadar ilerlemek gerekir.

Bir sayının 3 veya 5'e bölünmesinden kalanının 0 olup olmadığını kontrol etmek için modulo işlemi kullanılabilir. Daha büyük bir sınır değere kadar olan toplam değeri hesaplayabilmenin püf noktası, `int` veya `long` yerine `long long` kullanmaktır.


```cpp
#include <iostream>

int main()
{
    unsigned int limit = 0;

    std::cout << "Üst sınır: ";
    std::cin >> limit;

    unsigned long long sum = 0;
    bool isDivisible = 0;

    for (unsigned int i = 3; i < limit; ++i)
    {
        if (i % 3 == 0)
        {
            isDivisible = 1;
        }
        else if (i % 5 == 0)
        {
            isDivisible = 1;
        }

        if (isDivisible)
        {
            sum += i;
        }

        isDivisible = 0;
    }

    // 11 için: 3 + 5 + 6 + 9 + 10 = 33
    std::cout << "Toplam: " << sum << std::endl;
}

```

Yukarıdaki programı biraz optimize ederek aşağıdaki programa çevirebiliriz:

```cpp
#include <iostream>

int main()
{
    unsigned int limit = 0;

    std::cout << "Üst sınır: ";
    std::cin >> limit;

    unsigned long long sum = 0;

    for (unsigned int i = 3; i < limit; ++i)
    {
        if (i % 3 == 0 || i % 5 == 0)
        {
            sum += i;
        }
    }

    // 11 için: 3 + 5 + 6 + 9 + 10 = 33
    std::cout << "Toplam: " << sum << std::endl;
}
```

## Toplama Formülünden Yararlanarak Hesaplama

Matematikte toplama, toplananlar olarak adlandırılan, herhangi bir sayı türünden olan sayıların değerinin eklenmesidir; sonuç, bunların toplamıdır.

Sonsuz dizilerin toplamlarına seri adı verilir ve limit kavramını içerirler. Şu an konumuz dışındadırlar.

Bir dizinin toplamı, toplananların art arda gelmesi şeklinde gösterilir. Örneğin, [1, 2, 4, 2]'nin toplamı 1 + 2 + 4 + 2 olarak ifade edilir ve 9 değeriyle sonuçlanır, yani 1 + 2 + 4 + 2 = 9'dur. Toplama, birleşmeli ve değişmeli bir işlem olduğundan parantez gerekmez ve sonuç toplananların sırasına bağlı değildir. Sadece bir öğeden oluşan bir dizinin toplamı bu öğenin kendisiyle sonuçlanır. Boş bir dizinin (sıfır elemanlı bir dizinin) toplamı, 0 ile sonuçlanır.

Çok sık olarak, bir dizinin elemanları, düzenli bir desen içinde dizilimdeki yerlerinin bir fonksiyonu olarak tanımlanır. Basit desenler için, uzun dizilerin toplamı, çoğu toplananın üç noktayla değiştirilmesiyle temsil edilebilir. Örneğin, ilk 100 doğal sayının toplamı 1 + 2 + 3 + 4 + ⋅⋅⋅ + 99 + 100 şeklinde yazılabilir.

Diğer durumlarda toplama, Σ notasyonu kullanılarak gösterilir. Örneğin, ilk n doğal tam sayının toplamı (n) Σ (i = 1) i şeklinde gösterilebilir.

Uzun toplamaların ve değişken uzunluktaki toplamların sonucu için kapalı formlu ifadeler bulmak yaygın bir problemdir. Örneğin:

(n) Σ (i = 1) i = (n * (n + 1)) / 2

Bu formüller her zaman bulunmamasına rağmen, birçok toplama formülü keşfedilmiştir. En yaygın ve basit olanlardan birini 3 veya 5'e bölünebilen doğal sayıların toplamını bulma problemimizde kullanabiliriz. Örneğin 1000'e kadar olan doğal sayılardan 3'e veya 5'e bölünenbilenlerin toplamı:

(333) Σ (k1 = 1) 3 * k1 + (199) Σ (k2 = 1) 5 * k2 - (66) Σ (k3 = 1) 15 * k3 = 166833 + 99500 − 33165 = 233168

```cpp
#include <iostream>

int main()
{
    unsigned int limit = 0;

    std::cout << "Üst sınır: ";
    std::cin >> limit;

    unsigned int limit3 = (limit - 1) / 3;
    unsigned int limit5 = (limit- 1) / 5;
    unsigned int limit15 = (limit - 1) / 15;

    unsigned long long sum = 0;

    sum = 0.5 * 3 * limit3 * (limit3 + 1) + 0.5 * 5 * limit5 * (limit5 + 1) - 0.5 * 15 * limit15 * (limit15 + 1);

    std::cout << "Toplam: " << sum << std::endl;
}
```

## Kaynaklar

* [Project Euler - Problem 1](https://projecteuler.net/problem=1)
* [number theory - Find the sum of all the multiples of 3 or 5 below 1000 - Mathematics Stack Exchange](https://math.stackexchange.com/questions/9259/find-the-sum-of-all-the-multiples-of-3-or-5-below-1000)
* [Summation - Wikipedia](https://en.wikipedia.org/wiki/Summation)
* [The Modern C++ Challenge - Chapter 1 - Problem 1](https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/tree/master/Chapter01/problem_01)
