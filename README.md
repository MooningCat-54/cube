# ASCII 3D Donut

Terminal üzerinde dönen 3 boyutlu simit (torus) animasyonu. Harici bir grafik kütüphanesi kullanılmadan, tamamen boş vakitte eğlencesine saf C ile yazılmıştır.

---

## Genel Bakış

* Standart C kütüphaneleri dışında hiçbir bağımlılığı yoktur.
* 3B koordinatları trigonometrik fonksiyonlarla uzayda döndürür.
* Yüzey aydınlatması ve derinlik sıralaması için temel bir Z-Buffer mantığı kullanır.
* ANSI kaçış dizileri ile terminalde titreşimsiz bir şekilde render edilir.

---

## Derleme ve Çalıştırma

Matematik kütüphanesini (`-lm`) bağlayarak derleyebilirsiniz:

```bash
gcc donut.c -o donut -lm
./donut
