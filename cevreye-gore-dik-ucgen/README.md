# Bir Çevre Uzunluğundaki Mümkün Tüm Dik Üçgenler

Elimizdeki `p` metre uzunluğundaki bir iple hangi kenar uzunluklarına sahip üçgenlerin dik açılı üçgenler oluşturduğunu bulan bir program yazmak istediğimizi düşünelim.

Örneğin elimizde `1000` metre ip var. Bu iple kenarları `200`, `375` ve `425` uzunluklarında bir üçgen oluşturduğumuzda bir dik üçgen oluştuğunu `200^2 + 375^2 = 425^2` denkleminin doğruluğunu gördüğümüzde anlayabiliyoruz.

Yukarıdaki denklem oluşturulurken kullanılan **Pisagor Teoremine** göre bir dik üçgende dik kenarların uzunluklarının kareleri toplamı dik açının karşısındaki kenarın (hipotenüsün) uzunluğunun karesine eşittir. Pisagor teoremi hakkında daha çok bilgi için [matematikciler.com'daki Pisagor Teoremi makalesine](https://www.matematikciler.com/8-sinif-pisagor-teoremi-pisagor-bagintisi/) göz atabilirsiniz.

Görüleceği gibi amacımız, `a + b + c = p` ve `a^2 + b^2 = c^2` şartlarını sağlayan dik açılı üçgenleri bulmaktır.

İlk akla gelebilecek yaklaşımlardan biri, `i`(`1`'den `p/2`'ye) ve `j`(`i+1`'den `p/2`'ye) olmak üzere iki döngü çalıştırmak, sonra üçüncü kenar uzunluğunu `c = p - i - j` denklemiyle almak ve eğer `i*i + j*j == c*c` eşitliği sağlanıyorsa üçgenin kenar uzunluklarını ekrana basmaktır. Bu, `O(p^2)` zaman alacaktır.

```cpp
#include <iostream>

int main()
{
    int p = 3000;
    for (int i = 1; i < p/2; i++)
    {
        for (int j = i+1; j < p/2; j++)
        {
            int c = p - i - j;
            if (i*i + j*j == c*c)
            {
                std::cout << i << ", " << j << ", " << c << std::endl;
            }
        }
    }

    return 0;
}
```

```
500, 1200, 1300
600, 1125, 1275
750, 1000, 1250
```

Küçük bir cebirsel hileyle daha verimli bir yaklaşım bulunabilir:

```
a^2 + b^2 = c^2
(a+b)^2 - 2ab = c^2
(p-c)^2 - 2ab = c^2
p^2 - 2cp - 2ab = 0
2ab = p^2 - 2cp
2ab = p^2 - 2p(p - a - b)
2a(p-b) = p(p-2b)
a = (p/2) * ((p - 2b) / (p - b))
```

`a + c > b` ve `p – b > b` ve `b < p/2` olduğundan `b`'nin `1`'den `p/2`'ye doğru ilerletilmesi, `a`'nın hesaplanması ve sadece tam sayı `a`'ların saklanması verilen `p` için tüm çözümleri verecektir. Dik açılı üçgenler Pisagor Teoremine uyduğundan `p`'nin tek sayı olduğu durumlar için herhangi bir dik üçgen oluşturulması mümkün değildir. `a` ve `b`'nin değerlerini saklamak için bir çiftler listesi kullanılabilir ve sonunda da oluşturulan üçgenler ekrana basılabilir. Bu yaklaşımın bir gerçeklemesi aşağıdaki gibidir:

```cpp
#include <iostream>
#include <algorithm>
#include <set>

int main()
{
    int p = 1000;

    std::set <std::pair<int, int>> ucgen;

    if (p % 2 != 0)
    {
        return 0;
    }
    else
    {
        for (float b = 1; b < p/2; b++)
        {
            float a = (p/2) * ((p - 2*b) / (p - b));
            int inta = (int) a;
            int c = p - a - b;
            if (a == inta)
            {
                if (a < b)
                {
                    ucgen.insert(std::make_pair(a, b));
                }
                else
                {
                    ucgen.insert(std::make_pair(b, a));
                }
            }
        }
    }

    for (auto i : ucgen)
    {
        std::cout << std::get<0>(i) << ", " << std::get<1>(i)
                  << ", " << p - std::get<0>(i) - std::get<1>(i) << std::endl;
    }

    return 0;
}
```

```
200, 375, 425
```

Bu çözüm de `O(p)` zaman alacaktır.

## Kaynaklar
- [Dik üçgen bulma algoritması - Algoritma Soruları](https://algoritma-sorulari.blogspot.com/2019/07/dik-ucgen-bulma-algoritmas.html)
- [Count number of right triangles possible with a given perimeter - GeeksforGeeks](https://www.geeksforgeeks.org/count-number-of-right-triangles-possible-with-a-given-perimeter/)
- [Count number of right triangles possible with a given perimeter](http://www.programming.pk/question/count-number-of-right-triangles-possible-with-a-given-perimeter/)
- [Problem 39 - Project Euler](https://projecteuler.net/problem=39)
- [How to calculate the total number of possible right angle triangles where the perimeter is given, and all sides are integers? - Mathematics Stack Exchange](https://math.stackexchange.com/questions/2676162/how-to-calculate-the-total-number-of-possible-right-angle-triangles-where-the-pe)
