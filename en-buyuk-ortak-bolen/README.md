# En Büyük Ortak Bölen

En büyük ortak bölen (greatest common divisor, gcd), iki veya daha çok sıfırdan farklı tamsayının hepsini bölen en büyük pozitif tamsayıdır.

Peki, 54 ve 24'ün en büyük ortak böleni nasıl bulunur? 54 sayısı, iki tamsayının çarpımı olarak birkaç farklı şekilde ifade edilebilir: `54 * 1 = 27 * 2 = 18 * 3 = 9 * 6`. Böylece 54'ün bölenleri: 1, 2, 3, 6, 9, 18, 27 ve 54'tür. Benzer şekilde 24'ün bölenleri de: 1, 2, 3, 4, 6, 8, 12 ve 24'tür.

Bu iki listede ortak olan sayılar, 54 ve 24'ün ortak bölenleridir: 1, 2, 3 ve 6. Bunların en büyüğü 6'dır. Yani, 54 ve 24'ün en büyük ortak böleni 6'dır.

```cpp
gcd(54, 24) = 6
```

## Öklid Algoritması

En büyük ortak böleni hesaplamak için birden çok yöntem vardır. Bunlarden etkili bir tanesi Öklid'in algoritmasıdır. İki tamsayı için bu algoritma şu şekildedir:

```cpp
gcd(a, 0) = a
gcd(a, b) = gcd(b, a mod b)
```

Öklid Algoritması, iki sayının en büyük böleninin, büyük sayı yerine büyük sayının küçük sayıdan farkının yazılması durumunda değişmemesi prensibine dayanır.

Örneğin, 21, 252 ve 105'in en büyük ortak bölenidir (`252 = 21 * 12` ve `105 = 21 * 5` olmak üzere) ve 21 aynı zamanda 105'in ve 252 - 105 = 147'nin de en büyük ortak bölenidir.

Bu değiştirme, iki sayının büyüklüğünü azalttığından, bu işlemin tekrarlanması, iki sayı eşitleninceye kadar art arda daha küçük sayı çiftleri verir. Sonun da elde edilen değer de orijinal iki sayının en büyük ortak bölenidir.

Öklid Algoritması birçok teorik ve pratik uygulamaya sahiptir. Kesirleri en basit haline indirmek ve modüler aritmetikte bölme yapmak için kullanılır. Bu algoritmayı kullanan hesaplamalar, internet iletişimini güvence altına alan şifreleme protokollerinin oluşturulması ve büyük şifreleme sayılarını çarpanlara ayırarak bu şifreleme sistemlerinin kırılması için kullanılır.

Eğer gcd(a, b) = 1 ise, a ve b'nin aralarında asal olduğu söylenir. Bu, a veya b'nin asal sayılar olduğu anlamına gelmez. Örneğin, ne 6 ne de 35 asal bir sayıdır, çünkü her ikisi de iki asal çarpana sahiptir: `6 = 2 * 3` ve `35 = 5 * 7`. Yine de, 6 ve 35 aralarında asaldır. 1'den başka hiçbir doğal sayı, hem 6 hem de 35'i bölemez, çünkü ortak bir çarpanları yoktur.

Üç veya daha çok sayının en büyük ortak böleni, tüm sayılar için ortak olan asal çarpanların çarpımına eşittir, ancak sayı çiftlerinin en büyük ortak bölenleri teker teker alınarak da hesaplanabilir. Örneğin:

```cpp
gcd(a, b, c) = gcd(a, gcd(b, c)) = gcd(gcd(a, b), c) = gcd(gcd(a, c), b)
```

Bu nedenle, iki tamsayının en büyük ortak bölenini hesaplayan Öklid Algoritması, ikiden çok tamsayının en büyük ortak bölenini hesaplamak için de yeterlidir.

Öklid Algoritması, C++'ta hem iteratif hem de özyinelemeli olarak gerçekleştirilebilir. Ayrıca C++17'de `<numeric>` başlığında iki sayının en büyük ortak bölenini hesaplayan `gcd()` isminde bir `constexpr` fonksiyon vardır.

```cpp
#include <iostream>
#include <numeric>

unsigned int gcd1(unsigned int const a, unsigned int const b)
{
   return b == 0 ? a : gcd1(b, a % b);
}

unsigned int gcd2(unsigned int a, unsigned int b)
{
   while (b != 0)
   {
      unsigned int r = a % b;
      a = b;
      b = r;
   }

   return a;
}

int main()
{
   std::cout << "Sayıları giriniz: ";

   unsigned int a, b;
   std::cin >> a >> b;

   std::cout << "ozy gcd(" << a << ", " << b << ") = "
             << gcd1(a, b) << std::endl;

   std::cout << "ite gcd(" << a << ", " << b << ") = "
             << gcd2(a, b) << std::endl;

   std::cout << "std gcd(" << a << ", " << b << ") = "
             << std::gcd(a, b) << std::endl;
}
```

## İkilik En Büyük Ortak Bölen Algoritması

En büyük ortak böleni hesaplamanın alternatif bir yöntemi, sadece çıkarma ve 2 ile bölme işlemlerini içeren ve Stein Algoritması olarak da bilinen İkilik En Büyük Ortak Bölen Algoritması'dır (Binary GCD algorithm).

Stein Algoritması, geleneksel Öklid Algoritması'ndan daha basit aritmetik işlemler kullanır, bölme işleminin yerini aritmetik kaydırmalar, karşılaştırmalar ve çıkarma alır. Algoritma ilk kez İsrailli fizikçi ve programcı Josef Stein tarafından 1967'de yayınlanmış olmasına rağmen, 1. yüzyılda Çin'de biliniyor olabilir.

Anahatlarıyla yöntem şöyledir:

1. `gcd(0, v) = v`'dir, çünkü her şey sıfıra bölünür ve `v`, `v`'yi bölen en büyük sayıdır. Benzer şekilde, `gcd(u, 0) = u`'dur. `gcd(0, 0)` genellikle tanımlanmaz, ancak `gcd(0, 0) = 0` ayarının yapılması uygundur.

2. `u` ve `v`'nin ikisi de çiftse `gcd(u, v) = 2 * gcd(u/2, v/2)`'dir, çünkü 2 ortak bir bölendir.

3. `u`, çift ve `v`, tek olduğunda `gcd(u, v) = gcd(u/2, v)`'dir, çünkü 2 ortak bir bölen değildir. Benzer şekilde, eğer `u`, tek ve `v`, çiftse `gcd(u, v) = gcd(u, v/2)`'dir.

4. `u` ve `v`'nin ikisi de tekse ve u >= v ise `gcd(u, v) = gcd((u − v)/2, v)`'dir. Eğer ikisi de tekse ve u < v ise `gcd(u, v) = gcd((v − u)/2, u)`'dur.

`u = v` veya `u = 0` olana kadar 2-4 adımları tekrarlanır. Her iki durumda da, en büyük ortak bölen power(2, k) * v'dir, burada k, ikinci adımda bulunan 2 ortak çarpanının sayısıdır.

```cpp
#include <iostream>

int gcd(unsigned int u, unsigned int v)
{
    // temel durumlar (sonlandırmalar)
    if (u == v)
    {
        return u;
    }

    if (u == 0)
    {
        return v;
    }
    if (v == 0)
    {
        return u;
    }
    // GCD(0, 0) = 0

    // 2'nin katlarını ara
    if (~u & 1) // u çift
    {
        if (v & 1) // v tek
        {
            return gcd(u >> 1, v);
        }
        else // hem u hem de v çift
        {
            return gcd(u >> 1, v >> 1) << 1;
        }
    }

    if (~v & 1) // u tek, v çift
    {
        return gcd(u, v >> 1);
    }

    // büyük sayıyı küçült
    if (u > v)
    {
        return gcd((u - v) >> 1, v);
    }

    return gcd((v - u) >> 1, u);
}

int main()
{
    std::cout << "Sayıları giriniz: ";

    unsigned int u, v;
    std::cin >> u >> v;

    std::cout << "gcd(" << u << ", " << v << ") = "
              << gcd(u, v) << std::endl;

    return 0;
}
```

Algoritma, O(n^2) en kötü durum çalıştırma zamanına sahiptir, buradaki n, iki sayıdan büyük olanının bit sayısıdır. Her adım en az bir işlenenin en az 2'nin bir katı kadar azaltmasına rağmen çıkarma ve kaydırma işlemleri çok büyük tamsayılar için doğrusal zaman alır (uygulamada hala epey hızlı olmasına rağmen, gösterimin her word'u başına yaklaşık bir işlem gerektirir).

Akhavi ve Vallée, teoride, İkilik En Büyük Ortak Bölen Algoritması'nın Öklid Algoritması'ndan ortalama olarak yaklaşık %60 daha verimli olabileceğini kanıtladı. Bu algoritma, gerçek uygulamalardaki geleneksel Öklid Algoritmasını mütevazı bir şekilde geride bıraksa da, asimptotik performansı aynıdır ve İkilik En Büyük Ortak Bölen Algoritması, tüm modern mikroişlemcilerde bir bölme komutunun yaygın olarak bulunması göz önünde bulundurulduğunda kodlama için epey karmaşıktır. Ancak bazı işlemcilerde bölme komutu diğer makine komutlarından çok daha yavaş olabilir.

## Birden Çok Sayının En Büyük Ortak Bölenini Bulma

C++'ta birden çok sayının en büyük ortak bölenini bulmak için kullanılabilecek birkaç yöntem vardır. Aşağıda bu iş için varyadik şablonların nasıl kullanılabileceğini görebilirsiniz.

```cpp
#include <iostream>
#include <utility>

template<typename T1, typename T2>
T1 gcd(T1 a, T2 b)
{
    // a >= b, a * b != 0
    if(a < b)
    {
        std::swap(a, b);
    }

    T1 r;
    while(r = a % b)
    {
        a = b;
        b = r;
    }

    return b;
}

template<typename T1, typename T2, typename... Types>
T1 gcd(T1 a, T2 b, Types... args)
{
   return gcd(a, gcd(b, args...));
}

int main()
{
    std::cout << "gcd(10, 20, 30, 40, 55) = "
              << gcd(10, 20, 30, 40, 55) << std::endl;
}
```

## Kaynaklar

* [Euclidean algorithm - Wikipedia](https://en.wikipedia.org/wiki/Euclidean_algorithm)
* [Greatest common divisor - Wikipedia](https://en.wikipedia.org/wiki/Greatest_common_divisor)
* [Binary GCD algorithm - Wikipedia](https://en.wikipedia.org/wiki/Binary_GCD_algorithm)
* [Stein's Algorithm for finding GCD - GeeksforGeeks](https://www.geeksforgeeks.org/steins-algorithm-for-finding-gcd/)
* [Variadic function template for Greatest Common Divisor - Kim Thomas](https://www.youtube.com/watch?v=vzchEgALYZ8)
* [The Modern C++ Challenge - Chapter 1 - Problem 2](https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/tree/master/Chapter01/problem_02)
