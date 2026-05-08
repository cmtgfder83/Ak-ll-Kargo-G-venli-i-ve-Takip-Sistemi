 GitHub'daki README.md dosyası projenin kartvizitidir.

 Akıllı Kargo Güvenliği ve Takip Sistemi
 lojistik süreçlerinde hassas kargoların güvenliğini sağlamak amacıyla geliştirilmiş, gerçek zamanlı eğim ve duruş takibi yapan otonom bir mühendislik çözümüdür. Bu proje, Gökhan Beyaz tarafından İstanbul Topkapı Üniversitesi Elektrik Elektronik Mühendisliği Yüksek Lisans çalışmaları kapsamında tasarlanmıştır.

 Proje Özeti
Sistem, taşıma esnasında kutuların devrilmesi veya hatalı açılarda taşınması sonucu oluşan maddi hasarları minimize etmeyi hedefler. MPU6050 ivmeölçer sensörü yardımıyla kargonun üç eksendeki hareketleri milisaniyeler içinde analiz edilir.

 Temel Özellikler
Kritik Eğim Analizi: Kargonun açısı 25 derece eşik değerini aştığında sistem otomatik olarak uyarı verir.

Görsel İkaz: Tehlikeli eğim durumunda STM32L031K6 üzerindeki PA5 (D13) pinine bağlı LED aktifleşir.

Dijital Raporlama: UART protokolü üzerinden bilgisayar terminaline anlık veri ve durum bilgisi aktarılır.

Düşük Güç Tüketimi: Enerji verimliliği odaklı tasarımı sayesinde uzun süreli lojistik operasyonlara uygundur.

 Teknik Altyapı
Sistem mimarisi aşağıdaki donanım ve yazılım bileşenleri üzerine kurgulanmıştır:

MCU: STM32L031K6 (ARM Cortex-M0+).

Sensör: MPU6050 (6 Eksenli İvmeölçer & Jiroskop).

Haberleşme: Veri aktarımı için I2C ve seri izleme için UART protokolleri kullanılmıştır.

Geliştirme Ortamı: STM32CubeIDE ve HAL kütüphaneleri.

 Gelecek Vizyonu

IoT Entegrasyonu: Verilerin bulut sistemine aktarılarak global kargo takibi yapılması.

Mobil Uygulama: Flutter tabanlı bir arayüz ile kargo durumunun anlık izlenmesi.

Yapay Zeka Destekli Analiz: Yapay zeka mühendisliği birikimiyle sarsıntı ve darbe modellerinin sınıflandırılması.

 Geliştirici
Gökhan Beyaz

Elektrik Elektronik Mühendisliği | İstanbul Topkapı Üniversitesi Lisansüstü Öğrencisi

20 Yıllık Saha ve Saha Yönetimi Tecrübesi
