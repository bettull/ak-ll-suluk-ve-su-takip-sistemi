# ak-ll-suluk-ve-su-takip-sistemi
Bu proje, bireylerin günlük su tüketimini takip etmelerini kolaylaştırmak için geliştirilmiş bir **akıllı suluk sistemidir**. Kullanıcıdan yaş ve kilo bilgisi alır, buna göre günlük su ihtiyacını hesaplar ve HC-SR04 sensörüyle şişedeki su seviyesini ölçer.  uzun süre su içilmediğinde LED ve buzzer ile kullanıcıyı uyarır.

## Kullanılan Bileşenler

| Parça             | Açıklama                         |
|------------------|----------------------------------|
| Arduino Uno      | Ana mikrodenetleyici             |
| HC-SR04          | Ultrasonik mesafe sensörü        |
| LCD 16x2 (I2C)    | Menü ve bilgilendirme ekranı     |
| 4x4 Keypad       | Yaş ve kilo girişi, menü kontrolü|
| LED              | Uyarı ışığı                      |
| Buzzer           | Sesli uyarı                      |
| Reset Butonu     | Sistem sıfırlama tuşu            |

##  Kurulum

1. Devre elemanlarını bağlayın (devre şeması için aşağıya bakın).
2. Aşağıdaki Arduino kütüphanelerini yükleyin:
   - `LiquidCrystal_I2C`
   - `Keypad`
3. Kodları Arduino IDE'ye yükleyin ve karta gönderin.


##  Çalışma Prensibi

- **Adım 1:** Kullanıcı yaşını girer → `#` tuşuna basar  
- **Adım 2:** Kullanıcı kilosunu girer → `#` ile onaylar  
- **Adım 3:** Günlük su ihtiyacı hesaplanır (`kg x 35 ml`)  
- **Adım 4:** HC-SR04 ile şişedeki su miktarı ölçülür  
- **Adım 5:**  
  - `*` tuşu → bir önceki menü  
  - `#` tuşu → bir sonraki menü  
  - Menü 0 → Günlük hedef  
  - Menü 1 → Suluktaki mevcut su miktarı  
- **Adım 6:** Eğer 1 dakika boyunca su içilmezse LED ve buzzer devreye girer  
- **Adım 7:** Reset butonuna basıldığında tüm sistem sıfırlanır

## Koddan Örnek

suIhtiyaci = kilo * 35.0 / 1000.0; // litre olarak hesaplama
suSeviyesi = 2.0 * (1.0 - (mesafe / 25.0)); // 25 cm’lik şişeye göre

 Reset Butonu
A0 pinine bağlı olan buton, LED ve buzzer'ı kapatır ve sistemi başa döndürür.

 
 
 Geliştirici: Betül Başboğa
 Proje Tarihi: 17 Haziran 2025


