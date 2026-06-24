# ANONSİM: Anon Network & Marketplace

## Proje Hakkında
### Bu proje, C++ ile geliştirilmiş terminal tabanlı bir gizli ağ ve pazar yeri simülasyonudur.
### Algoritma ve Programlamaya Giriş II dersi kapsamında bir öğrenci projesi olarak tasarlanmıştır.
### Temel amacı; dosya okuma/yazma işlemleri, basit kriptografi ve algoritma mantığını pratik bir konsol uygulamasında birleştirmektir.

## Temel Özellikler

### 1. Güvenli Kayıt ve Giriş Sistemi
#### Sisteme kayıt olan kullanıcıların parolaları düz metin yerine DJB2 hash algoritması kullanılarak saklanır.
#### Kullanıcı verileri "veritabani.txt" dosyasına kaydedilir ve giriş doğrulamaları bu dosya üzerinden güvenli şekilde yapılır.

### 2. Şifreli Mesajlaşma Ağı
#### Kullanıcılar birbirlerine Vigenere şifreleme algoritması kullanarak uçtan uca şifreli mesajlar gönderebilir.
#### Gelen kutusundaki mesajları deşifre edip okuyabilmek için, göndericinin belirlediği özel şifreleme anahtarının bilinmesi zorunludur.

### 3. Anonim Ticaret ve Pazar Yeri
#### Aktif kullanıcılar, pazar yerine belirledikleri fiyatlarla yeni ürünler ekleyebilir ("urunler.txt" dosyasına işlenir).
#### Pazaryerindeki mevcut ürünler listelenebilir ve terminal üzerinden basit bir satın alma simülasyonu gerçekleştirilebilir.

## Kurulum ve Çalıştırma

### Projeyi derlemek için C++11 veya üzeri standartları destekleyen bir derleyiciye (GCC, MinGW vb.) ihtiyacınız vardır.
### Kaynak kodu derlemek için terminalinizde veya komut istemcinizde g++ main.cpp -o anonsim komutunu çalıştırabilirsiniz.
### Programı başlatmak için derlenen dosyayı Windows ortamında anonsim.exe, Linux/Mac ortamında ./anonsim yazarak açabilirsiniz.
### Türkçe karakterlerin konsolda düzgün görüntülenmesi için Windows terminalinin UTF-8 (65001) formatında çalışması sağlanmıştır.

## Kullanılan Teknolojiler ve Kütüphaneler
### Geliştirme dili olarak standart C++ kullanılmıştır.
### Veri akışı ve dosya işlemleri için <iostream>, <string> ve <fstream> kütüphanelerinden faydalanılmıştır.
### Şifreleme algoritmalarındaki karakter dönüşümleri için <cctype>, konsol dil kodlaması için <windows.h> kütüphaneleri kullanılmıştır.

## Akademik Bilgiler
### Kurum: Kahramanmaraş İstiklal Üniversitesi
### Ders: YZM102 Algoritma ve Programlamaya Giriş II
### Proje: ANONSİM Konsol Uygulaması
### Geliştirici: Mustafa Kaan Çelik (25020091020)
