# 100'lük Not Sistemindeki Notu Harf Notuna Dönüştürme

Eğitimde derecelendirme, bir dersteki değişen başarı seviyeleri için standartlaştırılmış bir ölçüm uygulama sürecidir. Notlar harf olarak (örneğin A'dan F'ye kadar), bir aralık olarak (örneğin 1'den 6'ya kadar), doğru cevaplanan toplam soru sayısının yüzdesi olarak veya olası toplamın bir sayısı olarak atanabilir (örneğin 20 veya 100).

Aşağıdaki harf notu - puan tablosunu kullanarak girilen puanı harf notuna çeviren bir algoritma geliştirmemiz beklendiğini düşünelim.

```
90-100   AA
80-89    BA
70-79    BB
65-69    CB
60-64    CC
50-59    DD
30-49    FD
0-29     FF
```

## If-Else

Bu problem için akla gelebilecek ilk çözüm yöntemi if-else kontrol ifadelerini kullanmaktır:

```cpp
#include <iostream>
#include <string>

std::string getGrade(int numberGrade)
{
    if (numberGrade >= 0 && numberGrade <= 100)
    {
        if (numberGrade > 89)
        {
            return "AA";
        }
        else if (numberGrade > 79)
        {
            return "BA";
        }
        else if (numberGrade > 69)
        {
            return "BB";
        }
        else if (numberGrade > 64)
        {
            return "CB";
        }
        else if (numberGrade > 59)
        {
            return "CC";
        }
        else if (numberGrade > 49)
        {
            return "DD";
        }
        else if (numberGrade > 29)
        {
            return "FD";
        }
        else
        {
            return "FF";
        }
    }
    return "";
}

int main()
{
    for (int i = 100; i >= 0; --i)
    {
        std::cout << i << " = " << getGrade(i) << std::endl;
    }

    return 0;
}
```

## Switch İfadesi

Yukarıdaki çözümde epey bir if ifadesi kullandığımız dikkatinizi çekmiştir. Diyelim ki if ifadesini kullanmanız istenmiyor, ne yapardınız? Switch kullanmayı deneyebilirsiniz:

```cpp
#include <iostream>
#include <string>

std::string getGrade(int numberGrade)
{
    unsigned int quotient = numberGrade / 10;
    unsigned int remainder = numberGrade % 10;

    std::string letterGrade = "";

    switch (quotient)
    {
        case 10:
            letterGrade = "AA";
            break;
        case 9:
            letterGrade = "AA";
            break;
        case 8:
            letterGrade = "BA";
            break;
        case 7:
            letterGrade = "BB";
            break;
        case 6:
            letterGrade = "C";
            switch (remainder)
            {
                case 9:
                case 8:
                case 7:
                case 6:
                case 5:
                    letterGrade += "B";
                    break;
                case 4:
                case 3:
                case 2:
                case 1:
                case 0:
                    letterGrade += "C";
                    break;
            }
            break;
        case 5:
            letterGrade = "DD";
            break;
        case 4:
        case 3:
            letterGrade = "FD";
            break;
        case 2:
        case 1:
        case 0:
            letterGrade = "FF";
            break;
    }
    return letterGrade;
}

int main()
{
    for (int i = 100; i >= 0; --i)
    {
        std::cout << i << " = " << getGrade(i) << std::endl;
    }

    return 0;
}
```

## Daha Şık Bir Çözüm

Evet her ne kadar switch, if'in eşleneği olarak sayılabilse de if kullanmamayı da başardınız. Peki ya bu kadarcık bir iş için bu kadar satır çoğunuza gitseydi ne yapardınız? `std::map`'i kullanabilirdiniz örneğin:

```cpp
#include <iostream>
#include <string>
#include <map>

std::string getGrade(int numberGrade)
{
    if (numberGrade >= 0 && numberGrade <= 100)
    {
        std::map<int, std::string> score = {
            { 30, "FF" },
            { 50, "FD" },
            { 60, "DD" },
            { 65, "CC" },
            { 70, "CB" },
            { 80, "BB" },
            { 90, "BA" },
            { 101, "AA" }
        };

        for (const auto& i : score)
        {
            if (numberGrade < i.first)
            {
                return i.second;
            }
        }
    }
    return "";
}

int main()
{
    for (int i = 100; i >= 0; --i)
    {
        std::cout << i << " = " << getGrade(i) << std::endl;
    }

    return 0;
}
```

## Kaynaklar

* [Grading systems by country - Wikipedia](https://en.wikipedia.org/wiki/Grading_systems_by_country)
* [Grading in education - Wikipedia](https://en.wikipedia.org/wiki/Grading_in_education)
* [java - How can I use a switch() statement to convert from a numeric to a letter grade? - Stack Overflow](https://stackoverflow.com/questions/1535076/how-can-i-use-a-switch-statement-to-convert-from-a-numeric-to-a-letter-grade)
* [Not sistemlerinin karşılaştırılması - Tubitak](http://www.tubitak.gov.tr/sites/default/files/equivalency_table_0.pdf)
* [100'lük not sisteminde kullanıcıdan girilen puan ile harf sonucu bastırma](https://github.com/msusur/kodlama-pratikleri/blob/master/sorular/not-sistemi-sorusu.md)
