# Arduino Akıllı suluk ve su takip sistemi
Bu proje, kullanıcının yaş ve kilo bilgilerine göre günlük su ihtiyacını hesaplayan ve su içmeyi hatırlatan akıllı bir Arduino sistemidir.

##  Özellikler

- **Kişiselleştirilmiş Su Hesaplama**: Yaş ve kilo bilgilerine göre günlük su ihtiyacını otomatik hesaplar
- **Gerçek Zamanlı Su Seviye Takibi**: HC-SR04 ultrasonik sensörü ile su şişesindeki seviyeyi ölçer
- **Akıllı Hatırlatma Sistemi**:uzun süre su içilmezse LED ve buzzer ile uyarı verir
- **Kullanıcı Dostu Menü**: LCD ekranda gezinilebilir menü sistemi
- **Kolay Sıfırlama**: Reset butonu ile sistemi yeniden başlatma

##  Gerekli Malzemeler

### Elektronik Bileşenler
- Arduino Uno/Nano
- 16x2 I2C LCD Ekran
- 4x4 Matrix Keypad
- HC-SR04 Ultrasonik Mesafe Sensörü
- LED
- Buzzer
- Push Button (Reset için)
- Jumper kablolar
- Breadboard

### Kütüphaneler
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>


##  Bağlantı Şeması

### LCD (I2C)
- VCC → 5V
- GND → GND
- SDA → A4 (Arduino Uno)
- SCL → A5 (Arduino Uno)

### Keypad (4x4)
- Row pins: D2, D3, D4, D5
- Column pins: D6, D7, D8, D9

### HC-SR04 Ultrasonik Sensör
- VCC → 5V
- GND → GND
- Trig → D11
- Echo → D12

### Diğer Bileşenler
- LED → D13
- Buzzer → D10
- Reset Button → A0

##  Kurulum

1. **Kütüphaneleri yükleyin:**
   - Arduino IDE'de `Sketch` → `Include Library` → `Manage Libraries`
   - `LiquidCrystal I2C` ve `Keypad` kütüphanelerini arayın ve yükleyin

2. **Bağlantıları yapın:**
   - Yukarıdaki bağlantı şemasına göre tüm bileşenleri Arduino'ya bağlayın

3. **Kodu yükleyin:**
   - Bu repository'yi klonlayın veya kodu kopyalayın
   - Arduino IDE'de açın ve kartınıza yükleyin

##  Kullanım

### İlk Kurulum
1. **Yaş Girişi**: Sistemi açtığınızda yaşınızı keypad ile girin ve `#` tuşuna basın
2. **Kilo Girişi**: Kilonuzu girin ve tekrar `#` tuşuna basın
3. **Otomatik Hesaplama**: Sistem günlük su ihtiyacınızı otomatik hesaplar (Kilo × 35ml)

### Ana Menü Kullanımı
- **`*` tuşu**: Önceki menüye geç
- **`#` tuşu**: Sonraki menüye geç

#### Menü 0: Günlük Hedef
```
Gunluk Hedef:
2.45 L
```

#### Menü 1: Su Seviyesi
```
Sulukta:
1.23 L
```

### Uyarı Sistemi
- Su seviyesi değişmediğinde (1 dakika boyunca su içilmediğinde)
- LED yanar ve buzzer çalar
- Su içildikten sonra otomatik olarak kapanır

### Reset İşlemi
- Reset butonuna basarak sistemi tamamen sıfırlayabilirsiniz
- Tüm veriler silinir ve baştan kurulum yapılır

## Teknik Detaylar

### Su İhtiyacı Hesaplama

suIhtiyaci = kilo * 35.0 / 1000.0; // litre cinsinden


### Su Seviyesi Ölçümü
- 25 cm yüksekliğinde şişe için kalibre edilmiştir
- Maksimum 2 litre kapasiteli şişe destekler
- Mesafe ölçümü: `mesafe = sure * 0.034 / 2.0`

### Uyarı Koşulları
- Su seviyesi değişimi: `abs(suSeviyesi - oncekiSuSeviyesi) > 0.05`
- Uyarı süresi: 60 saniye (1 dakika)

##  Özelleştirme

### Şişe Boyutunu Değiştirme
// 25 cm yerine farklı yükseklik için
suSeviyesi = 2.0 * (1.0 - (distance / YENİ_YÜKSEKLİK));


### Uyarı Süresini Değiştirme
// 60000 ms (1 dakika) yerine istediğiniz süre
if (millis() - sonIcilmeZamani > YENİ_SÜRE) 

### Su Hesaplama Formülünü Değiştirme

// 35ml/kg yerine farklı oran
suIhtiyaci = kilo * YENİ_ORAN / 1000.0;


## Kod Yapısı

### Ana Fonksiyonlar
- `setup()`: Başlangıç ayarları ve pin konfigürasyonu
- `loop()`: Ana program döngüsü
- `mesafeOku()`: HC-SR04 sensörü ile mesafe ölçümü

### Değişkenler
- `yasStr`, `kiloStr`: Kullanıcı giriş verileri
- `suIhtiyaci`: Hesaplanan günlük su ihtiyacı
- `suSeviyesi`: Şişedeki mevcut su seviyesi
- `sonIcilmeZamani`: Son su içme zamanı
- `menuIndex`: Aktif menü indeksi

##  Sorun Giderme

### LCD Görünmüyor
- I2C adresini kontrol edin (genellikle 0x27 veya 0x3F)
- SDA/SCL bağlantılarını kontrol edin
- LCD backlight fonksiyonunu test edin

### Keypad Yanıt Vermiyor
- Pin bağlantılarını doğrulayın
- Keypad matrisinin doğru tanımlandığından emin olun
- Keypad kütüphanesinin doğru kurulduğunu kontrol edin

### Mesafe Ölçümü Hatalı
- HC-SR04 sensörünün düzgün yerleştirildiğinden emin olun
- Trig/Echo pinlerinin doğru bağlandığını kontrol edin
- Sensör önünde engel olmadığından emin olun

### Buzzer Çalışmıyor
- Buzzer polaritesini kontrol edin
- Pin bağlantısını doğrulayın
- digitalWrite komutlarını test edin


##  İletişim
betül başboğa 
betulbasboga921@gmail.com
