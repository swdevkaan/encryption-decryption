#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <windows.h>
using namespace std;

// Fonksiyon bildirileri
void giris_fonksiyonu();
void kayit_fonksiyonu();
void mesaj_gonder_fonksiyonu(string gonderen);
void mesaj_oku_fonksiyonu(string aktif_kullanici);
string sifrele(string metin, string anahtar);
string deşifre(string metin, string anahtar);
void ticaret_sistemi_fonksiyonu(string aktif_kullanici);
void urun_ekle_fonksiyonu(string satici);
void urunleri_listele_fonksiyonu(string alici);
string basitHashle(string metin);



int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    cout  << R"(
    ==================================================================
       _   _  _   _   ___   _   _  __   __ __  __   ___   _   _  ____
      / \  | \|  | / _ \ | \ | | \ \ / /|  \/  | / _ \ | | | | / ___|
     / _ \ | . ` || | | ||  \| |  \ V / | |\/| || | | || | | | \___ \
    / ___ \| |\  || |_| || |\  |   | |  | |  | || |_| || |_| |  ___) |
   /_/   \_\_| \_| \___/ |_| \_|   |_|  |_|  |_| \___/  \___/  |____/

                       [ ANON NETWORK & MARKETPLACE ]
    ==================================================================
    )" << endl;
    cout<<("\n");
    cout<<("  +================================================+\n");
    cout<<("  |      KAHRAMANMARAŞ İSTİKLAL ÜNİVERSİTESİ       |\n");
    cout<<("  +================================================+\n");
    cout<<("  | DERS:YZM102 ALGORİTMA VE PROGRAMLAMAYA GİRİŞ II|\n");
    cout<<("  | DERSİN HOCASI: Dr.Öğr.Üy.İBRAHİM ARUK          |\n");
    cout<<("  | PROJE: ANONSİM                                 |\n");
    cout<<("  | HAZIRLAYAN: Mustafa Kaan Çelik                 |\n");
    cout<<("  | ÖĞRENCİ NO: 25020091020                        |\n");
    cout<<("  +================================================+\n");
    int secim;
    while (true) {
        cout << "\n1- KAYIT OL\n"
                "2- GIRIS YAP\n"
                "3- CIKIS\n"
                "Seciminiz: ";
        cin >> secim;

        if (secim == 1) {
            kayit_fonksiyonu();
        } else if (secim == 2) {
            giris_fonksiyonu();
        } else if (secim == 3) {
            cout << "Cikis yapiliyor...\n";
            break;
        } else {
            cout << "Gecersiz secim! Lutfen 1 ile 3 arasinda bir deger girin.\n";
        }
    }
    return 0;
}

void kayit_fonksiyonu() {
    string alias, parola;
    cout << "\n[KAYIT EKRANI]\n";
    cout << "Kullanici Adi (Alias): ";
    cin >> alias;
    cout << "Parola: ";
    cin >> parola;

    // Şifreyi güvenli hale getirmek için hashliyoruz
    string hashliParola = basitHashle(parola);

    ofstream dosya("veritabani.txt", ios::app);
    if (dosya.is_open()) {
        dosya << alias << " " << hashliParola << "\n"; // Hashli şifre yazılıyor
        dosya.close();
        cout << "Kayit basariyla olusturuldu!\n";
    } else {
        cout << "Hata: Veritabani dosyasina erisilemedi!\n";
    }
}


void giris_fonksiyonu() {
    string girilen_alias, girilen_parola;
    cout << "\n[GIRIS EKRANI]\n";
    cout << "Kullanici Adi (Alias): ";
    cin >> girilen_alias;
    cout << "Parola: ";
    cin >> girilen_parola;

    ifstream dosya("veritabani.txt");
    string dosyadaki_alias, dosyadaki_parola;
    bool girisBasarili = false;

    if (dosya.is_open()) {
        // Kullanıcının girdiği parolayı da hash'e çeviriyoruz
        string girilenHash = basitHashle(girilen_parola);

        while (dosya >> dosyadaki_alias >> dosyadaki_parola) {
            // Dosyadaki hashli şifre ile kullanıcının girdiği şifrenin hash'ini kıyaslıyoruz
            if (dosyadaki_alias == girilen_alias && dosyadaki_parola == girilenHash) {
                girisBasarili = true;
                break;
            }
        }
        dosya.close();
    }

    if (girisBasarili) {
        cout << "\nGiris Basarili! Hos geldin, " << girilen_alias << "\n";
        int alt_secim;
        while (true) {
            cout << "\n--- ANON ISLEM MENUSU ---\n"
                    "1- Mesaj Gonder\n"
                    "2- Gelen Kutusu (Mesajlari Oku)\n"
                    "3- Anon Ticaret Sistemi\n"
                    "4- Ana Menuye Don\n"
                    "Seciminiz: ";
            cin >> alt_secim;

            if (alt_secim == 1) {
                mesaj_gonder_fonksiyonu(girilen_alias);
            } else if (alt_secim == 2) {
                mesaj_oku_fonksiyonu(girilen_alias);
            } else if (alt_secim == 3) {
                ticaret_sistemi_fonksiyonu(girilen_alias);
            } else if (alt_secim == 4) {
                break;
            }
        }
    } else {
        cout << "\nHata: Kullanıcı adı veya parola yanlış\n";
    }
}


void mesaj_gonder_fonksiyonu(string gonderen) {
    string alici, anahtar, mesaj;
    cout << "\n[MESAJ GONDERME EKRANI]\n";
    cout << "Alicinin Kullanici Adi (Alias): ";
    cin >> alici;
    cout << "Sifreleme Anahtari: ";
    cin >> anahtar;

    cin.ignore(); // Satir okumadan once buffer temizligi
    cout << "Mesajiniz: ";
    getline(cin, mesaj);

    // Mesajdaki bosluklari dosya kaydi bozulmasin diye '_' yapiyoruz
    for (char &c : mesaj) {
        if (c == ' ') c = '_';
    }

    string sifreliMesaj = sifrele(mesaj, anahtar);

    ofstream dosya("mesajlar.txt", ios::app);
    if (dosya.is_open()) {
        dosya << gonderen << " " << alici << " " << sifreliMesaj << "\n";
        dosya.close();
        cout << "Sifreli mesaj basariyla gonderildi!\n";
    } else {
        cout << "Hata: Mesaj gonderilemedi!\n";
    }
}


void mesaj_oku_fonksiyonu(string aktif_kullanici) {
    ifstream dosya("mesajlar.txt");
    string gonderen, alici, sifreliMesaj;
    bool mesajVarMi = false;

    cout << "\n[GELEN KUTUNUZ]\n";

    if (dosya.is_open()) {
        while (dosya >> gonderen >> alici >> sifreliMesaj) {
            if (alici == aktif_kullanici) {
                mesajVarMi = true;
                cout << "\nGonderen: " << gonderen << "\n";
                cout << "Sifreli Mesaj: " << sifreliMesaj << "\n";

                string anahtar;
                cout << "Cozmek icin anahtar girin: ";
                cin >> anahtar;

                string cozulmusMesaj = deşifre(sifreliMesaj, anahtar);

                // '_' karakterlerini tekrar bosluga ceviriyoruz
                for (char &c : cozulmusMesaj) {
                    if (c == '_') c = ' ';
                }

                cout << "=> Orijinal Mesaj: " << cozulmusMesaj << "\n";
                cout << "-----------------------------------\n";
            }
        }
        dosya.close();
    }

    if (!mesajVarMi) {
        cout << "Gelen kutunuzda mesaj bulunmamaktadir.\n";
    }
}


void ticaret_sistemi_fonksiyonu(string aktif_kullanici) {
    int ticaret_secim;
    while (true) {
        cout << "\n--- ANON PAZAR YERI ---\n"
                "1- Urun Ekle (Satis)\n"
                "2- Urunleri Listele & Satin Al\n"
                "3- Anon Islem Menusune Don\n"
                "Seciminiz: ";
        cin >> ticaret_secim;

        if (ticaret_secim == 1) {
            urun_ekle_fonksiyonu(aktif_kullanici);
        } else if (ticaret_secim == 2) {
            urunleri_listele_fonksiyonu(aktif_kullanici);
        } else if (ticaret_secim == 3) {
            break;
        } else {
            cout << "Gecersiz secim!\n";
        }
    }
}


void urun_ekle_fonksiyonu(string satici) {
    string urun_adi;
    double fiyat;

    cout << "\n[URUN EKLEME EKRANI]\n";
    cin.ignore(); // buffer temizleme
    cout << "Urun Adi: ";
    getline(cin, urun_adi);
    cout << "Fiyat (Pazar Birimi): ";
    cin >> fiyat;

    // Ürün adındaki boşlukları dosya yapısı bozulmasın diye '_' yapıyoruz
    for (char &c : urun_adi) {
        if (c == ' ') c = '_';
    }

    ofstream dosya("urunler.txt", ios::app);
    if (dosya.is_open()) {
        // Format: satici urun_adi fiyat
        dosya << satici << " " << urun_adi << " " << fiyat << "\n";
        dosya.close();
        cout << "Urununuz pazar yerine basariyla eklendi!\n";
    } else {
        cout << "Hata: Pazar yeri veritabanina erisilemedi!\n";
    }
}


void urunleri_listele_fonksiyonu(string alici) {
    ifstream dosya("urunler.txt");
    string satici, urun_adi;
    double fiyat;
    int sayac = 1;
    bool urunVarMi = false;

    cout << "\n[PAZARDAKI AKTIF URUNLER]\n";
    cout << "No\tSatici Urun Adi Fiyat\n";
    cout << "---------------------------------------\n";

    if (dosya.is_open()) {
        while (dosya >> satici >> urun_adi >> fiyat) {
            urunVarMi = true;

            // Ekran basarken alt tireleri tekrar boşluk yapıyoruz
            string gosterilecek_ad = urun_adi;
            for (char &c : gosterilecek_ad) {
                if (c == '_') c = ' ';
            }

            cout << sayac << "-\t" << satici << "\t" << gosterilecek_ad << "\t" << fiyat << "\n";
            sayac++;
        }
        dosya.close();
    }

    if (!urunVarMi) {
        cout << "Pazarda su an satilik urun bulunmamaktadir.\n";
        return;
    }

    // Basit bir satın alma simülasyonu
    int satin_alinacak_no;
    cout << "\nSatin almak istediginiz urun numarasini girin (Cikis icin 0): ";
    cin >> satin_alinacak_no;

    if (satin_alinacak_no > 0 && satin_alinacak_no < sayac) {
        cout << "\nTebrikler! Urun basariyla satin alindi.\n";
        cout << "Anon kuryelerimiz teslimat icin yola cikti...\n";
    } else if (satin_alinacak_no != 0) {
        cout << "Gecersiz urun numarasi!\n";
    }
}


// Vigenere şifreleme (harfleri kaydırarak yeni bir metin oluşturur)
string sifrele(string metin, string anahtar) {
    for (size_t i = 0; i < metin.length(); i++) {
        if (isalpha(metin[i])) {
            char baslangic = isupper(metin[i]) ? 'A' : 'a';
            int kaydirma = toupper(anahtar[i % anahtar.length()]) - 'A';
            metin[i] = (metin[i] - baslangic + kaydirma) % 26 + baslangic;
        }
    }
    return metin;
}


// Vigenere Deşifreleme
string deşifre(string metin, string anahtar) {
    for (size_t i = 0; i < metin.length(); i++) {
        if (isalpha(metin[i])) {
            char baslangic = isupper(metin[i]) ? 'A' : 'a';
            int kaydirma = toupper(anahtar[i % anahtar.length()]) - 'A';
            metin[i] = (metin[i] - baslangic - kaydirma + 26) % 26 + baslangic;
        }
    }
    return metin;
}

// DJB2 Temelli Basit Hash Fonksiyonu
string basitHashle(string metin) {
    unsigned long long hashDegeri = 5381;
    for (size_t i = 0; i < metin.length(); i++) {
        hashDegeri = ((hashDegeri << 5) + hashDegeri) + metin[i];
    }
    return to_string(hashDegeri);
}