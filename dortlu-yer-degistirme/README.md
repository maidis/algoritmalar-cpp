# C++'ta Bir Bayttaki İki Dörtlünün Yerini Değiştirmek

## Dörtlüler

**Dörtlü**, dört tane bitin peş peşe bir araya gelmesiyle oluşan yapıdır. Bir baytın yarısıdır ve Türkçe'de yarım bayt veya dört bit olarak da isimlendirilir. İngilizce karşılığıysa **nibble**'dır. Bu isimlerden ve tanımlardan da anlaşılabileceği gibi bir baytta iki tane dörtlü vardır.

Baytın İngilizce karşılığı olan byte, ısırmak anlamına gelen bite kelimesine fonetik olarak benzer. Buradan yola çıkarak, yarım bayt boyutundaki veriyi ifade etmek için de dişlemek anlamındaki nibble kelimesi kullanılmıştır.


## Dörtülülerin Listesi

Olası tüm dörtlüler ve diğer sayı sistemlerindeki karşılıkları aşağıdaki gibidir:

| Onaltılık | Onluk | Sekizlik | İkilik |
| 0 | 0 | 0 | 0 0 0 0 |
| 1 | 1 | 1 | 0 0 0 1 |
| 2 | 2 | 2 | 0 0 1 0 |
| 3 | 3 | 3 | 0 0 1 1 |
| 4 | 4 | 4 | 0 1 0 0 |
| 5 | 5 | 5 | 0 1 0 1 |
| 6 | 6 | 6 | 0 1 1 0 |
| 7 | 7 | 7 | 0 1 1 1 |
| 8 | 8 | 10 | 1 0 0 0 |
| 9 | 9 | 11 | 1 0 0 1 |
| A | 10 | 12 | 1 0 1 0 |
| B | 11 | 13 | 1 0 1 1 |
| C | 12 | 14 | 1 1 0 0 |
| D | 13 | 15 | 1 1 0 1 |
| E | 14 | 16 | 1 1 1 0 |
| F | 15 | 17 | 1 1 1 1 |


## İki Dörtlünün Yer Değişimi

Bize bir baytın verildiğini ve bu baytın ilk dörtlüsüyle ikinci dörtlüsünün yerini değiştirmemiz gerektiğini varsayalım. Örneğin `100`, bit seviyesinde `01100100` olarak ifade edilir. Dörtlüler `0110` ve `0100`'dır. Eğer iki dörtlünün yerini değiştirirsek `01000110` elde ederiz ki bu da onluk tabanda `70`'e denk gelir.

Dörtlüleri değiştirmek için bitsel ve `&`, bitsel veya `|`, bitsel sağa kaydırma `>>` ve bitsel sola kaydırma `<<` operatörlerini kullanabiliriz. Genel olarak bir C++ derleyicisindeki bir karakter büyüklüğü 1 bayt olduğundan, 1 bayt, bir unsigned char kullanılarak gösterilebilir. Kısaca bahsettiğimiz bu fikrin gerçeklemesi şöyledir:

```cpp
#include <bits/stdc++.h>
#include <bitset>
#include <iostream>

int swapNibbles(int x)
{
    return ( (x & 0x0F) << 4 | (x & 0xF0) >> 4 );
}


int main()
{
    int x = 100;
    std::cout << x << " - " << std::bitset<8>(x) << '\n';
    int y = swapNibbles(x);
    std::cout << y << " - " << std::bitset<8>(y) << '\n';
    return 0;
}
```

Program çalıştırıldığında vereceği çıktı şöyledir:

```bash
100 - 01100100
70 - 01000110
```

100'ün ikilik tabanda 01100100 olduğunu söylemiştik. Programdaki işlemler temel olarak iki bölüme ayrılabilir:

İlk önce `x & 0x0F`, bize `x`'in son dört bitini verir. `x = 100` için sonuç `00000100`'dır. Bitsel `<<` operatörü kullanılarak son dört bit sola dört kez kaydırılır ve yeni son dört bit `0` olarak ayarlanır. Kaydırma sonrasında sonuç `01000000`'dır.

Sonra, `x & 0xF0` ifadesi bize ilk dört biti verir. `x = 100` için sonuç `01100000`'dır. Bitsel `>>` operatörü kullanılarak rakam dört kez sağa kaydırılır ve ilk dört biti `0` yapılır. Kaydırma sonrasındaki sonuç `00000110`'dır.

Sonunda yukarıda sonucunu bulduğumuz iki ifadeyi bitsel veya `|` işlemine koyarak birleştiriyoruz. Burada veya işlemi ilk dört biti sona, son dört biti de başa yerleştirir. `x = 100` için: `01000000 | 00000110` işleminin sonucu bize `01000110` değerini verir ki bu da onluk tabanda `70`'tir.


## Kaynaklar
- [Swap two nibbles in a byte - GeeksforGeeks](https://www.geeksforgeeks.org/swap-two-nibbles-byte/)
- [Swap two nibbles in a byte - Firmcodes](http://www.firmcodes.com/swap-two-nibbles-byte/)
- [Nibble - Ekşi Sözlük](https://eksisozluk.com/nibble--71970)
