# C++'ta Yinelenen Öğelerin Yerlerinin Bulunması

Bu yazıda bir `vector`'deki peş peşe konumlarda yer alan aynı öğelerin konum bilgilerini döndüren bir program gerçekleştireceğiz. Örneğin `v = {1, 1, 1, 0, 0, 1, 1, 0, 1, 1};` için almak istediğimiz çıktı `{(0, 2), (5, 6), (8, 9)}`. Bu işi gerçekleştirmek için iki farklı yol izleyeceğiz.

## Geleneksel yol

Programın ilerleyen kısımlarında kullanacağımız değişkenleri ve sabitleri tanımlayarak programa başlayalım. Aslında bunları kullanılacakları yerlerin daha yakınlarında tanımlamak daha doğru ama şimdilik bu gerçeği görmezden gelelim. Değişkenlerimizi kısaca tanıtmak gerekirse:

- `v`: Üzerinde arama yapacağımız taşıyıcı
- `a`, b`: Aradığımız öğelerin konumlarını bulurken alt ve üst sınırları belirlemek için yardımcı değişkenler
- `q`: Aranan öğe
- `vect`: Alt ve üst sınırların saklanacağı taşıyıcı
- `inSeries`: O anda bir seri içinde olunup olunmadığını belirten değişken

Bu değişkenlerden bazıları ikinci yol içinde kullanılacağından orada ayrıca bahsedilmeyecektir.

```cpp
    std::vector<int> v = {1, 1, 1, 0, 0, 1, 1, 0, 1, 1}; // {(0, 2), (5, 6), (8, 9)}
    int a, b;
    int q = 1;
    std::vector <std::pair<int, int>> vect;
    bool inSeries = false;
```

Değişkenlerimizi tanımladığımıza göre şimdi asıl işi yapacak döngümüzü oluşturmaya başlayabiliriz. Döngümüzde genel olarak dört soru soruyoruz:

- O an bakılan öğe, aranan öğe değilse ve bir serinin içinde bulunulmuyorsa bir sonraki öğeye geç
- O an bakılan öğe, aranan öğeyse ve bir seri içinde bulunulmuyorsa, seri içinde bulunulmaya başlandığını belirt, alt ve üst sınırı o anki öğenin konumuna ayarla
  - O an bakılan öğe, son öğeyse o anki seri için alt ve üst sınırı döndür
- O an bakılan öğe, aranan öğeyse ve bir serinin içinde bulunuluyorsa, üst sınırı o anki öğenin konumuna ayarla
  - O an bakılan öğe, son öğeyse o anki seri için alt ve üst sınırı döndür
- O an bakılan öğe, aranan öğe değilse ve bir serinin içinde bulunuluyorsa alt ve üst sınırı önceden verilen değerlere ayarla ve seri içinde bulunulmamaya başlandığını belirt

```cpp
    for (int i = 0; i < v.size(); ++i)
    {
        if (v[i] != q && inSeries == false)
        {
            continue;
        }
        else if (v[i] == q && inSeries == false)
        {
            inSeries = true;
            a = i;
            b = i;
            if (i == v.size() - 1)
            {
                vect.push_back(std::make_pair(a, b));
            }
        }
        else if ( v[i] == q && inSeries == true)
        {
            b = i;
            if (i == v.size() - 1)
            {
                vect.push_back(std::make_pair(a, b));
            }
        }
        else if (v[i] != q && inSeries == true)
        {
            vect.push_back(std::make_pair(a, b));
            inSeries = false;
        }
    }
```

Konumların alt ve üst sınırlarının tamamını bulduktan sonra yapılacak son iş, bunları istediğimiz biçimde ekranda göstermektir. Bunu biraz süslü şekilde yapmak istediğimiz için kod normalde olması gerekenden daha uzun oldu. İlk önce bir adet `{` yazdırıyoruz. Sonra her bir bulunan serinin alt ve üst sınırını `(a, b),` biçiminde yazdırıyoruz. Burada küçük bir hile daha yaparak son seri için sondaki virgülün yazılmamasını sağlıyoruz. Tüm seriler bittiğinde de `}` ekleyerek yazdırma işlemini bitiriyoruz.

```cpp
    std::cout << '{';
    for (auto i = vect.begin(); i != vect.end(); ++i)
    {
        std::cout << '(' << std::get<0>(*i) << ", " << std::get<1>(*i);

        if (std::next(i) != vect.end())
        {
            std::cout << "), ";
        }
        else
        {
            std::cout << ")";
        }
    }
    std::cout << '}' << std::endl;
```

## Bir başka yol

Bir problemi tek bir yoldan çözmek bana yeterli gelmediği için hem bulduğum ilk yolu iyileştirmeyi hem de tamamen farklı yollar aramayı seviyorum. Şimdi aynı problemi farklı bir yolla çözmeyi deneyelim. Değişken tanımları ve yazdırma kısmı bahsetmeye değecek bir değişiklik içermediği için sadece işlerin geçekleştiği iki döngüyü inceleyeceğiz.

```cpp
    auto i = std::find(v.begin(), v.end(), q);
    std::vector<std::size_t> result;
    while(i != v.end())
    {
        auto pv = std::prev(i, 1);
        auto nt = std::next(i, 1);

        if (*pv != q)
            result.push_back(std::distance(v.begin(), i));
        if (*nt != q)
            result.push_back(std::distance(v.begin(), i));
        i = std::find(i + 1, v.end(), q);
    }
```

Döngüye girmeden önce aradığımız öğenin ilk konumunu buluyoruz. Sonra `vector`'un sonuna ulaşılıncaya dek sürecek bir döngü oluşturup içine giriyoruz. Yararlanacağımız önceki ve sonraki öğeleri gösterecek `pv` ve `nt` iteratörlerini tutuyoruz. Sonra da o an bakılan öğenin öncesindeki öğenin aranan öğe olup olmadığını bakıyoruz. Eğer önceki öğe aranan öğe değilse o an bakılan öğe seri başlangıcı demektir. Daha sonra da sonraki öğenin aranan öğe olup olmadığına bakıyoruz. Eğer sonraki öğe, aranan öğe değilse o an bakılan öğe, seri sonu demektir. Döngünün sonunda da o anda bakılan öğenin sonrasından `vector`'un sonuna kadar bakılarak aranan öğelerin ilkini buluyoruz.

```cpp
    std::vector <std::pair<int, int>> vect;

    for (int i = 0; i < result.size(); i = i + 2)
    {
        vect.push_back(std::make_pair(result[i], result[i+1]));
    }
```

Önceki döngüde `result` içine sırasıyla bir seri başlangıcı, bir seri sonu ekledik. Şimdi de bu yapıya uygun olarak bu `vector`'den seri sonlarını ve seri başlangıçlarını temsile eden bir `pair`'ler oluşturuyoruz.

Önceki yolda kullandığımız yazdırma bölümünü aynen burada da uygulayarak sonucu görüntülüyoruz.

## Kaynaklar

* [Serilerin başlangıç ve bitiş noktaları](https://algoritma-sorulari.blogspot.com/2019/01/serilerin-baslangc-ve-bitis-noktalar.html)
* [Mirat Can Bayrak - Twitter](https://twitter.com/miratcanbayrak/status/1087633166670708736)
* [Twitter'dan Düşüncelik'in (@kitapfilmtahta) gerçeklemesi](https://repl.it/repls/SuperficialLostProgrammingmacro)
* [c++ std::vector check if first or last element](https://stackoverflow.com/questions/30205158/c-stdvector-check-if-first-or-last-element)
