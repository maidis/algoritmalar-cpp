# En Küçük Ortak Kat

En küçük ortak kat (least common multiple, LCM), iki veya daha çok sıfırdan farklı tam sayının hepsine birden tam bölünen en küçük pozitif tam sayıdır.

Bir sayının katı, bu sayının ve bir tam sayının çarpımıdır. Örneğin 10, 5 * 2 = 10 oldğundan 5'in bir katıdır, yani 10, 5 ve 2 ile bölünebilir. 10, hem 5 hem de 2 tarafından bölünebilen en küçük pozitif tam sayı olduğundan 5 ve 2'nin en küçük ortak katıdır. Aynı prensipte 10, -5 ve -2'nin de en küçük ortak katıdır.

4 ve 6'nın en küçük ortak katının ne olduğuna bakalım.

4'ün katları şunlardır: 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76, ...

6'nın katlarıysa şunlardır: 6, 12, 18, 24, 30, 36, 42, 48, 54, 60, 66, 72, ...

4 ve 6'nın ortak katları, her iki listede de bulunan sayılardır: 12, 24, 36, 48, 60, 72, ...

Böylece, son listeden 4 ve 6 sayılarının ilk birkaç ortak katına bakılarak en küçük ortak katlarının 12 olduğu görülebilir.

## En Büyük Ortak Böleni Kullanarak Hesaplama

EKOK'u hesaplama yöntemlerinden biri, problemi en büyük ortak böleni hesaplamaya indirgemektir. Bu durumda aşağıdaki formül kullanılabilir:

```cpp
lcm(a, b) = abs(a * b) / gcd(a, b)
```

gcd(a, 0) = |a| olduğundan bu formül aynı zamanda a ve b'den biri 0 olduğunda da geçerlidir. Bununla birlikte hem a hem de b 0 ise bu formül sıfıra bölünmeye neden olur ve lcm(0, 0) = 0 özel bir durumdur.

Öklid Algoritması'nda en büyük ortak böleni hesaplamak için çarpanlara ayırma yapılmasını gerekmediğinden hızlı bir algoritmadır.

```cpp
lcm(21, 6) = (21 * 6) / gcd(21, 6) = (21 * 6) / gcd(3, 6) = (21 * 6) / 3 = 126 / 3 = 42
```

gcd(a, b), hem a hem de b'nin bir böleni olduğundan çarpmadan önce LCM'nin hesaplanması daha verimli olur:

```cpp
lcm(a, b) = (|a| / gcd(a, b)) * |b| = (|b| / gcd(a, b)) * |a|
```

Bu, hem bölme hem de çarpma için bir girişin boyutunu ve ara sonuçlar için gereken depolama alanını azaltır. gcd(a, b), hem a hem de b'nin bir böleni olduğu için bölümün bir tamsayı üretmesi garantidir, böylece ara sonuç bir tamsayı içinde saklanabilir. Bu şekilde yapıldığında önceki örnek şöyle olur:

```cpp
lcm(21, 6) = (21 / gcd(21, 6)) * 6 = (21 / gcd(3, 6)) * 6 = (21 / 3) * 6 = 7 * 6 = 42
```

```cpp
#include <iostream>
#include <numeric>
#include <vector>

int gcd1(int const a, int const b)
{
   return b == 0 ? a : gcd1(b, a % b);
}

int lcm1(int const a, int const b)
{
   int h = gcd1(a, b);
   return h ? (a * (b / h)) : 0;
}

int lcm2(int const a, int const b)
{
   return std::lcm(a, b);
}

int main()
{
    std::cout << "Sayıları giriniz: ";

    unsigned int a, b;
    std::cin >> a >> b;

    std::cout << "lcm(" << a << ", " << b << ") = "
              << lcm1(a, b) << std::endl;

    std::cout << "std lcm(" << a << ", " << b << ") = "
              << lcm2(a, b) << std::endl;
}
```

## Asal Çarpanlarına Ayırarak Hesaplama

Benzersiz çarpanlara ayırma teoremi, 1'den büyük olan her pozitif tamsayının, asal sayıların bir çarpımı olarak sadece bir şekilde yazılabileceğini söyler. Asal sayılar, bir araya geldiklerinde bileşik sayıları oluşturan atomik elemanlar olarak düşünülebilir.

Örneğin:

```cpp
90 = 2 ^ 1 * 3 ^ 2 * 5 ^ 1 = 2 * 3 * 3 * 5
```

Burada, asal sayı 2'nin bir atomundan, asal sayı 3'ün iki atomundan ve asal sayı 5'in bir atomundan oluşan bileşik sayı 90'a sahibiz. Bu bilgi sayıların LCM'sini bulmak için kullanılabilir.

Örneğin lcm(8, 9, 21)'in değerini bulalım. İlk olarak her sayıyı çarpanlara ayırıp asal sayı katlarının bir çarpımı olarak ifade edelim.

```cpp
8 = 2 ^ 3
9 = 3 ^ 2
21 = 3 ^ 1 * 7 ^ 1
```

LCM, her asal sayının en yüksek katının çarpımının sonucu olacaktır:

```cpp
lcm(8, 9, 21) = 2 ^ 3 * 3 ^ 2 * 7 ^ 1 = 8 * 9 * 7 = 504
```

Tamsayıları çarpanlarına ayırmak için bilinen genel bir verimli algoritma olmadığı için bu yöntem, en büyük ortak bölene indirgeme kadar etkili değildir ancak kavramları göstermek için faydalıdır.

## Tablo Yöntemiyle Hesaplama

Bu yöntem, tüm sayıları dikey olarak bir tabloda listeleyerek başlar. Bu örnekte sayılarımız 4, 7, 12, 21 ve 42 olsun.

```
4
7
12
21
42
```

Süreç, tüm sayıları 2'ye bölerek başlar. Sayılardan herhangi biri tam olarak bölündüyse tablonun üstüne 2 yazılır ve bu yeni sütünun altına 2'ye tam bölünen her sayının 2'ye bölümünden kalan, 2'ye tam bölünmeyen sayılarınsa kendileri yazılır. 2 sayıların hiçbirini tam olarak bölmezse 3'e geçilir.

```
x	2
4	2
7	7
12	6
21	21
42	21
```

Şimdi, tekrar 2'nin tam bölüp bölmediği kontrol edilir:

```
x	2	2
4	2	1
7	7	7
12	6	3
21	21	21
42	21	21
```

Artık 2 tam bölmediğinde, 3'e bölüm denenir. 3 tam bölmemeye başlarsa, 5 ve 7 denenmeye başlanır. Tüm sayılar 1'e düşene kadar devam edilir.

```
x	2	2	3	7
4	2	1	1	1
7	7	7	7	1
12	6	3	1	1
21	21	21	7	1
42	21	21	7	1
```

Son olarak en üstteki sayılar çarpılarak LCM elde edilir: 2 * 2 * 3 * 7 = 84.

## Birden Çok Sayının En Küçük Ortak Katını Bulma

C++'ta birden çok sayının en küçük ortak katını bulmak için kullanılabilecek birkaç yöntem vardır. Aşağıda bu iş için `std::accumulate`'in nasıl kullanılabileceğini görebilirsiniz.

```cpp
#include <iostream>
#include <numeric>
#include <vector>

template<class InputIt>
int lcmr(InputIt first, InputIt last)
{
    return std::accumulate(first, last, 1, std::lcm<int, int>);
}

int main()
{
    int n = 0;
    std::cout << "Girdi sayısı: ";
    std::cin >> n;

    std::vector<int> numbers;
    std::cout << "Sayıları giriniz: ";

    for (unsigned int i = 0; i < n; ++i)
    {
       int v{ 0 };
       std::cin >> v;
       numbers.push_back(v);
    }

    std::cout << "lcm = " << lcmr(std::begin(numbers), std::end(numbers)) << '\n';
}
```

## Kaynaklar

* [Least common multiple - Wikipedia](https://en.wikipedia.org/wiki/Least_common_multiple)
* [The Modern C++ Challenge - Chapter 1 - Problem 3](https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/tree/master/Chapter01/problem_03)
