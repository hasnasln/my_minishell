

# Minishell

## Proje Özeti

`Minishell` projesi, Bash benzeri basit bir shell (kabuk) oluşturmayı amaçlamaktadır. Bu proje sayesinde süreçler (`processes`) ve dosya tanımlayıcıları (`file descriptors`) hakkında kapsamlı bilgi edinilecektir. Geliştiricilerin Windows öncesi dönemde karşılaştığı zorlukları deneyimleyerek, bilgisayarlarla komut satırı aracılığıyla etkileşim kurma fikrinin nasıl ortaya çıktığına dair bir bakış açısı sunar.

## Temel Gereksinimler ve Kurallar

* Proje C dilinde yazılmalıdır.
* Tüm kod "Norm" kurallarına uygun olmalıdır; bonus dosyaları da dahil olmak üzere norm hatası durumunda 0 puan alınacaktır.
* Fonksiyonlar beklenmedik şekilde sonlanmamalıdır (segmentation fault, bus error, double free vb.). Bu tür durumlar projeyi işlevsiz kılar ve değerlendirmede 0 puanla sonuçlanır.
* Heap'te ayrılan tüm bellek gerektiğinde düzgün bir şekilde serbest bırakılmalıdır; bellek sızıntılarına izin verilmeyecektir. `readline()` fonksiyonundan kaynaklanan bellek sızıntıları için düzeltme yapma zorunluluğu yoktur, ancak kendi yazdığınız kodda bellek sızıntısı olmamalıdır.
* Proje için `Makefile` sağlanmalı, kaynak dosyaları `-Wall`, `-Wextra`, `-Werror` bayraklarıyla `cc` kullanarak derlemelidir. `Makefile` gereksiz yeniden bağlama yapmamalıdır.
* `Makefile` en azından `$(NAME)`, `all`, `clean`, `fclean` ve `re` kurallarını içermelidir.
* Bonus kısmı için `Makefile`'da ayrı bir `bonus` kuralı bulunmalı ve bonuslar `_bonus.c`/`_bonus.h` dosyalarında yer almalıdır. Zorunlu ve bonus kısımların değerlendirmesi ayrı yapılır.
* Libft kullanımı gerekiyorsa, Libft kaynakları ve `Makefile`'ı `libft` klasörüne kopyalanmalı ve projenin `Makefile`'ı önce Libft'i derlemelidir.
* Test programları oluşturulması teşvik edilir, ancak bu çalışma notlandırılmaz.
* Çalışma atanan Git deposuna gönderilmelidir; yalnızca depodaki çalışma değerlendirilecektir.

## Zorunlu Bölüm (Mandatory Part)
**Not:** Bu bölümün tüm gereksinimleri eksiksiz bir şekilde tamamlanmış ve proje Git deposuna teslim edilmiştir.
Minishell uygulamasının zorunlu özellikleri şunları içermelidir:

* Yeni bir komut beklerken bir prompt (`ipucu`) göstermelidir.
* Çalışan bir komut geçmişine (`history`) sahip olmalıdır.
* Doğru yürütülebilir dosyayı (PATH değişkenine veya göreceli/mutlak yola göre) aramalı ve başlatmalıdır.
* Alınan bir sinyali belirtmek için en fazla bir global değişken kullanmalıdır. Bu global değişken sadece sinyal numarasını saklamalı, ek bilgi sağlamamalı veya ana veri yapılarına erişmemelidir. Global kapsamda "norm" tipi yapılar kullanmak yasaktır.
* Kapanmamış tırnakları veya konu tarafından istenmeyen özel karakterleri (örneğin `\` veya `;`) yorumlamamalıdır.
* Tek tırnak (`'`) içindeki meta karakterlerin yorumlanmasını engellemeli.
* Çift tırnak (`"`) içindeki meta karakterlerin, `$` (dolar işareti) hariç, yorumlanmasını engellemeli.
* Aşağıdaki yönlendirmeleri (`redirections`) uygulamalıdır: 
    * `<`: Girişi yönlendirmelidir.
    * `>`: Çıkışı yönlendirmelidir.
    * `<<<`: Bir sınırlayıcı (`delimiter`) verilmelidir, ardından sınırlayıcı içeren bir satır görülene kadar girişi okumalıdır. Geçmişi güncellemek zorunda değildir.
    * `>>`: Çıkışı ekleme modunda yönlendirmelidir.
* Pipeları (`|` karakteri) uygulamalıdır.
* Ortam değişkenlerini (`$`) değerlerine genişletmelidir.
* `$?`'yi en son yürütülen ön plan pipeline'ının çıkış durumuna genişletmelidir.
* Ctrl-C, Ctrl-D ve Ctrl-\ davranışlarını Bash'teki gibi uygulamalıdır.
    * Etkileşimli modda:
        * Ctrl-C: Yeni bir satırda yeni bir prompt gösterir.
        * Ctrl-D: Shell'den çıkar.
        * Ctrl-\: Hiçbir şey yapmaz.
* Aşağıdaki dahili komutları (`built-in commands`) uygulamalıdır: 
    * `echo` ( `-n` seçeneği ile)
    * `cd` (sadece göreceli veya mutlak yol ile)
    * `pwd` (seçeneksiz)
    * `export` (seçeneksiz)
    * `unset` (seçeneksiz)
    * `env` (seçeneksiz veya argümansız)
    * `exit` (seçeneksiz)
* Şüpheniz varsa, Bash'i referans olarak almalısınız.
