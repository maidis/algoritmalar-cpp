# C++'ta vector'ü Tersine Çevirme

Bu yazıda, C++'ta bir `vector`'ün nasıl tersine çevrileceğini göreceğiz. Örneğin şöyle bir `vector`'ümüz olsun:

```cpp
std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
```

Bunu doğrudan aynı `vektor` veya farklı bir `vector`'de tersine çevirirsek aşağıdaki gibi bir sonuç elde ederiz:

```cpp
{ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
```

## std::reverse kullanarak

En basit çözüm, `<algorithm>` başlığında tanımlanan `std::reverse` fonksiyonunu kullanmaktır. Bu fonksiyon dahili olarak verilen aralığın her iki ucundaki elemanları değiştirmek için `std::iter_swap`'i kullanır.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> &v)
{
    for (T const& i: v)
    {
        os << i << " ";
    }

    return os;
}

int main()
{
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::cout << "Orijinal vector: " << v << '\n';

    std::reverse(v.begin(), v.end());
    std::cout << "Çevrilmiş vector: " << v << '\n';

    return 0;
}
```

Çıktı:

```bash
Orijinal vector: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
Çevrilmiş vector: 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
```

## Tersleme iteratörlerini kullanarak

Buradaki ana fikir, tersleme iteratörlerini kullanarak yeni bir `vector` oluşturmak ve bu sırada aralık yapıcısını kullanmaktır. Daha sonra orijinal `vector`'ü, yeni `vector` ile değiştirebiliriz.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> &v)
{
    for (T const& i: v)
    {
        os << i << " ";
    }

    return os;
}

int main()
{
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::cout << "Orijinal vector: " << v << '\n';

    std::vector<int> r(v.rbegin(), v.rend());
    v.swap(r); //  veya v = r; ifadesini kullanın

    std::cout << "Çevrilmiş vector: " << v << '\n';

    return 0;
}
```


## std::swap kullanarak

`std::reverse` fonksiyonunun dahili olarak `std::iter_swap` fonksiyonunu kullandığını gördük. `std::swap` fonksiyonunun yardımıyla aşağıda gösterildiği gibi de aynı şey yapılabilir:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> &v)
{
    for (T const& i: v)
    {
        os << i << " ";
    }

    return os;
}

int main()
{
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::cout << "Orijinal vector: " << v << '\n';

    for (auto start = v.begin(), end = std::prev(v.end()); start < end; ++start, --end)
    {
        //std::swap(*start, *end);
        *start = *start + *end;
        *end = *start - *end;
        *start = *start - *end;
    }

    std::cout << "Çevrilmiş vector: " << v << '\n';

    return 0;
}
```

## std::transform kullanarak

Son olarak, bir başka iyi çözüm de aşağıda gösterildiği gibi `std::transform` algoritmasını kullanmaktır:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> &v)
{
    for (T const& i: v)
    {
        os << i << " ";
    }

    return os;
}

int main()
{
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::cout << "Orijinal vector: " << v << '\n';

    auto mid = v.begin() + v.size()/2;

    std::transform(v.begin(), mid,
                    v.rbegin(), v.begin(),
                    [](int& x, int& y)
                    {
                        std::swap(x, y);
                        return x;
                    });

    std::cout << "Çevrilmiş vector: " << v << '\n';

    return 0;
}
```


## Kaynaklar

- [Reverse a vector in C++](https://www.techiedelight.com/reverse-vector-cpp/)
- [C++: How to reverse a List or sub-list in place?](https://thispointer.com/c-how-to-reverse-a-list-or-sub-list-in-place/)
- [C++'ta İki Değişkenin Değerini Birbirine Atamak](https://anilozbek.blogspot.com/2015/08/cta-iki-degiskenin-degerini-birbirine.html)
- [Listeyi Tersine Çevirme](https://algoritma-sorulari.blogspot.com/2018/12/listeyi-tersine-cevirme.html)
