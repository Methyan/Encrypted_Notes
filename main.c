#include <stdio.h>
#include <stdlib.h>

/*
 * Tanımlayıcı karakter dizini1:  >-?<
 * TKD2:                         >|<
 */


// BAGLI LISTE:
typedef struct liste {
    char ch;
    struct liste *next;
} liste;


// FONKSIYONLAR:
void NotGirdisi (liste *root, int NotAdedi);
void ListeSifrele  (liste *root);
liste * DosyaListele (void);
void FullListeYazdirma (liste *root);
void ListeDosyala (liste *root);
void ListeSifreCoz (liste *root);
int DosyaVarlikKontrol (void);
int NoteCounter (liste *root);
void NotOzelTamYazdir (liste *root);
void NotTekYazdir (liste *root, int NotNo);
int NotBaslikOlustur (liste *root, int NotAdedi);
int NotTumBaslikYazdir (liste *root);
int DosyaSil (void);
void SifresizDosyaOkuma (void);
void NotGenelTamOkuma (liste *root);
void toUpperCase (liste *root);
void ListeSifirla (liste *root);


// GELISTIRICI MENU FONKSIYONLARI:
void GelistiriciMenu1Fonk (void);
void GelistiriciMenu2Fonk (void);
void GelistiriciMenu3Fonk (void);
void GelistiriciMenu4Fonk (void);
void GelistiriciMenu5Fonk (void);
void GelistiriciMenu6Fonk (void);
void GelistiriciMenu7Fonk (void);
void GelistiriciMenu8Fonk (void);
void GelistiriciMenu9Fonk (void);
void GelistiriciMenu10Fonk (void);
void GelistiriciMenu11Fonk (void);
void GelistiriciMenu12Fonk (void);
void GelistiriciMenu13Fonk (void);


// ANA MENU FONKSIYONLARI:
void Menu1Fonk (void);
void Menu2Fonk (void);
void Menu3Fonk (void);
void Menu8Fonk (void);



int main() {

    girdiMain:

    printf("\n[1] Normal Menu \n[2] Gelistirici Menusu\n--> Hangi menuye gireceksiniz: ");
    char secim = getchar();
    while (1) {
        char temp = getchar();
        if (temp == 10) break;
    }


// Normal Menü:
    if (secim == 49) {
        while (1) {
            printf("\n[1] Not Yaz \n[2] Tum Notlari Oku \n[3] Secilen Notu Goruntule \n[8] Tum notlari sil \n[9] Cikis\n--> Hangi menuye gireceksiniz: ");
            secim = getchar();
            while (1) {
                char temp = getchar();
                if (temp == 10) break;
            }

            if (secim == 49) {
                Menu1Fonk(); // Dosya Yazma Fonksiyonu.
                printf("\n\n--> Degisikliklerin uygulanmasi icin program kapatildi.\n");
                return 1;
            }

            else if (secim == 50) Menu2Fonk();

            else if (secim == 51) Menu3Fonk();

            else if (secim == 56) {
                Menu8Fonk();
                printf("\n\n--> Degisikliklerin uygulanmasi icin program kapatildi.\n");
                return 1;
            }

            else if (secim == 57) {
                printf("Program kapatildi...");
                break;
            }

            else printf("\nHatali bir giris yaptiniz!\nTekrar deneyin.\n");
        }
    }


// Geliştirici Menüsü:
    else if (secim == 50) {
        girdiGelisticiMenu:
        printf("\n[1] Okuma \n[2] Yazma \n[3] Not Sil \n[4] Sifresiz Okuma \n[5] Dosya Listele - Liste Yazdir \n"
               "[6] Dosya Varlık Kontrol \n[7] Not Ozel Tam Yazdir \n[8] Not Tek Yazdir \n"
               "[9] Not Baslik Olustur (Nota müdahil) \n[A] Basliklarinin Tumunu Goster \n"
               "[B] Not Genel Tam Yazdır \n[C] Girilen basligin harflerini buyutuyor (TR haric)\n"
               "[D] Girdi Al yaz-oku (sifresiz) \n--> Yapacaginiz işlemi giriniz: ");
        secim = getchar();
        while (1) {
            char temp = getchar();
            if (temp == 10) break;
        }

        if (secim == 49) GelistiriciMenu1Fonk();         // Okuma yapılacak Ne var ne yok yazdırır.

        else if (secim == 50) GelistiriciMenu2Fonk();    // Dosyaya yazılacak:

        else if (secim == 51) GelistiriciMenu3Fonk();    // Notlar silinecek:

        else if (secim == 52) GelistiriciMenu4Fonk();    // Sifresiz dosya okuma:

        else if (secim == 53) GelistiriciMenu5Fonk();    // Dosya Listele - Yazdır

        else if (secim == 54) GelistiriciMenu6Fonk();    // Dosya Varlık Kontrol

        else if (secim == 55) GelistiriciMenu7Fonk();    // Not Ozel Tam Yazdır. Tüm notları yazıdır. (Başlıkları olmadan)

        else if (secim == 56) GelistiriciMenu8Fonk();    // İsteenilen notu tek olarak yazdırır. (Başlık olmadan)

        else if (secim == 57) GelistiriciMenu9Fonk();    // Not için başlık oluşturacak.

        else if (secim == 65) GelistiriciMenu10Fonk();  // Bütün notların başlıklarını yazdıracak.

        else if (secim == 66) GelistiriciMenu11Fonk();  // Tüm notları başlıkları ile birlikte yazdıracak.

        else if (secim == 67) GelistiriciMenu12Fonk();  // Girilen başlığın karakterlerini büyük harfe dönştürüyor.

        else if (secim == 68) GelistiriciMenu13Fonk();  // Girdi alıp listeler, listeyi şifresiz kaydedip okur.

        else {
            printf("Hatali bir giris yaptiniz!");
            goto girdiGelisticiMenu;
        }                           // Hatali girişte girdiMain'e geri döndürecek.
    }

    else {
        printf("Hatali bir giris yaptiniz!");
        goto girdiMain;
    }


    return 0;
}




void NotGirdisi (liste *root, int NotAdedi) {  // Kullanıcıdan not girdisi alacak ve listeye yazacak:
    // Not Adedi: -1 ise --> İçerisinde not yok, ama başlık yazıldı.
    int rootOlustur = 0;
    liste *iter = root;

    if (NotAdedi > 0 || NotAdedi == -1) { // Daha önceden not oluşturulduysa:
        while (iter->next != NULL) iter = iter->next;
    }
    if (NotAdedi == -1) NotAdedi = 0; // Alttaki algoritmaların düzgün çalışması için sıfırlandı!

    printf("\n\n--> Notunuzu giriniz. Cikmak icin TAB+ENTER\n--------------------------------------------------------------------\n");
    char karakter;
    int counter = 0;
    while (1) {
        karakter = getchar();
        if (karakter == 9) {
            karakter = getchar();
            if (karakter == 10) {
                printf("--------------------------------------------------------------------\nYazım bitirildi.\n");
                if (counter == 0) { // Gövdeye hiçbir şey yazılmadı ise:
                    char uyari[] = {'N', 'o', 't', ' ', 'Y', 'o', 'k', '!'};
                    iter->ch = uyari[0];
                    for (int i = 1; i < 8; i++) {
                        iter->next = malloc(sizeof(liste));
                        iter = iter->next;
                        iter->ch = uyari[i];
                    }
                }
                break;
            }
            else {
                iter->ch = 9;
                counter++;
                iter->next = malloc(sizeof(liste));
                iter = iter->next;
            }
        }
        if (karakter != 0) {
            if (rootOlustur == 1) {
                iter->next = malloc(sizeof(liste));
                iter = iter->next;
            }
            iter->ch = karakter;
            rootOlustur = 1;   // ilk iter boş geçilsin diye oluşturuldu.
        }
        counter++;
    }

    // TKD'de fonksiyondan dönen sayaca göre sıra numarası verilecek (? işareti yerine).
    // 5. birime atanan değer Not adedinin karakter karşılığının bir fazlasıdır.
    // TANIMLAYICI KARAKTER DIZISI:  >-?<   (? işareti yarine sıra numarası gelecek).

    char TKD[] = {'>', '-', (NotAdedi + 49), '<', 0};
    for (int i = 0; i < 5; i++) {
        iter->next = malloc(sizeof(liste));
        iter = iter->next;
        iter->ch = TKD[i];
    }
    FullListeYazdirma(root);
}




void ListeSifrele  (liste *root) {
// Cyrpting & File Write:
    liste *iter = root;
    int counter2 = 0;
    while (iter->next != NULL) {
        counter2++;
        if (counter2 % 3 == 0) {
            char ch = iter->ch;
            ch += (counter2 % 7);
            iter->ch = ch;
        }
        else if (counter2 % 3 == 1) {
            char ch = iter->ch;
            ch += ((counter2 % 4) + 1);
            iter->ch = ch;
        }
        else if (counter2 % 3 == 2) {
            char ch = iter->ch;
            ch += (counter2 + 31);
            iter->ch = ch;
        }
        iter = iter->next;
    }
}




liste * DosyaListele (void) {
    FILE *dosya1 = fopen("qwe.qwe", "r");
    FILE *dosya2 = fopen("asd.asd", "r");
    FILE *dosya3 = fopen("zxc.zxc", "r");

    liste *root = malloc(sizeof(liste));
    liste *iter = root;

    int counter = 1, control = 3;
    int Q_counter = 0, A_counter = 0, Z_counter = 0;

    // dosyanın ilk elemanı alınıyor:
    char karakter = fgetc(dosya2);
    iter->ch = karakter;
    A_counter++;

    while (1) {
        counter++;
        if (control == 0) { // Döngü sonlandırıcı:
            printf("\nProgram normal bir sekilde sonlandi!\n");
            break;
        }
        // Exception:
        if (control < 0) {
            printf("\n\nPROGRAMDA CIDDI HATA VAR\n--> Dosya Listele\n\n");
            return 0;
        }

        if (counter % 3 == 0) {
            Q_counter++;
            if (Q_counter % 4 == 0) fgetc(dosya1); /* 5'li karakter sonuna gelindi ise fazladan 1 karakter alacak */
            karakter = fgetc(dosya1);
            if (karakter == EOF) control--;
            else {
                iter->next = malloc(sizeof(liste));
                iter = iter->next;
                iter->ch = karakter;
            }
        }
        else if (counter % 3 == 1) {
            A_counter++;
            if (A_counter % 4 == 0) fgetc(dosya2);
            karakter = fgetc(dosya2);
            if (karakter == EOF) control--;
            else {
                iter->next = malloc(sizeof(liste));
                iter = iter->next;
                iter->ch = karakter;
            }
        }
        else if (counter % 3 == 2) {
            Z_counter++;
            if (Z_counter % 4 == 0) fgetc(dosya3);
            karakter = fgetc(dosya3);
            if (karakter == EOF) control--;
            else {
                iter->next = malloc(sizeof(liste));
                iter = iter->next;
                iter->ch = karakter;
            }
        }
    }


    fclose(dosya1);
    fclose(dosya2);
    fclose(dosya3);
    return root;
}




int DosyaVarlikKontrol (void) {
    int counter = 0;
    if (fopen("qwe.qwe", "r")) {
        counter++;
    }
    if (fopen("asd.asd", "r")) {
        counter++;
    }
    if (fopen("zxc.zxc", "r")) {
        counter++;
    }
    if (counter == 3) return 1; // Dosyalar mevcut.
    else if (counter < 3 && counter > 0) {
        printf("\n\nONEMLI:\n--> Dosyalar eksik!\n");
        return 0;
    }
    else return 0; // Dosya yok.
}




void FullListeYazdirma (liste *root) {
    printf("\n\nListenin icindekiler:\n");
    while (root != NULL) {
        printf("%c", root->ch);
        root = root->next;
    }
    printf("\n\n");
}




void ListeDosyala (liste *root) {
    liste *iter = root;
    FILE *dosya1 = fopen("qwe.qwe", "w+");
    FILE *dosya2 = fopen("asd.asd", "w+");
    FILE *dosya3 = fopen("zxc.zxc", "w+");

    int counter = 0, Q_counter = 0, A_counter = 0, Z_counter = 0;
    while (iter != NULL) {
        counter++;
        if (counter % 3 == 0) {     // Mod:0 --> 1. Dosyaya yazılacak:
            Q_counter++;
            if (Q_counter % 4 == 0) {
                if ((Q_counter / 4) % 4 == 0) { // Alt satıra geçilecek:
                    fprintf(dosya1, "\n");
                }
                else fprintf(dosya1, "\t");
            }
            fprintf(dosya1, "%c", iter->ch);
        }
        else if (counter % 3 == 1) { // Mod:1 --> 2. Dosyaya yazılacak:
            A_counter++;
            if (A_counter % 4 == 0) {
                if ((A_counter / 4) % 4 == 0) {
                    fprintf(dosya2, "\n");
                }
                else fprintf(dosya2, "\t");
            }
            fprintf(dosya2, "%c", iter->ch);
        }
        else if (counter % 3 == 2) { // Mod:2 --> 3. Dosyay yazılacak:
            Z_counter++;
            if (Z_counter % 4 == 0) {
                if ((Z_counter / 4) % 4 == 0) {
                    fprintf(dosya3, "\n");
                }
                else fprintf(dosya3, "\t");
            }
            fprintf(dosya3, "%c", iter->ch);
        }
        iter = iter->next;
    }
    fclose(dosya1);
    fclose(dosya2);
    fclose(dosya3);
}




void ListeSifreCoz (liste *root) {
    liste *iter = root;
    int cyrptCounter = 0;
    while (iter->next != NULL) {
        cyrptCounter++;
        if (cyrptCounter % 3 == 0) {
            char ch = iter->ch;
            ch -= (cyrptCounter % 7);
            iter->ch = ch;
        }
        else if (cyrptCounter % 3 == 1) {
            char ch = iter->ch;
            ch -= ((cyrptCounter % 4) + 1);
            iter->ch = ch;
        }
        else if (cyrptCounter % 3 == 2) {
            char ch = iter->ch;
            ch -= (cyrptCounter + 31);
            iter->ch = ch;
        }
        iter = iter->next;
    }
}




int NoteCounter (liste *root) { // DİKKAT: Sadece şifresi çözülmüş listeleri okur:
    // TKD1:  >-?<      TKD2:  >|<
    liste *iter = root;
    int body_counter = 0, title_counter = 0;
    while (iter->next != NULL) { // TKD sayacı:
        if (iter->ch == '>' && iter->next->ch == '-' && iter->next->next->next->ch == '<'){
            body_counter++;
        }
        else if (iter->ch == '>' && iter->next->ch == '|' && iter->next->next->ch == '<') {
            title_counter++;
        }
        iter = iter->next;
    }
    if ((title_counter / 2) == body_counter) return body_counter;
    else {
        printf("\n\n--> DIKKAT: Baslik ile govde sayisi esit cikmadi!\n");
        return body_counter;
    }
}




void NotOzelTamYazdir (liste *root) { // Tüm nootları TKD olmadan yazdırıyor:
    int counter = 1;
    printf("\n\n-> %d. Not\n", counter++);
    liste *iter = root;
    while (iter->next->ch != 0) {
        if (iter->ch == '>' && iter->next->ch == '-' && iter->next->next->next->ch == '<'){
            for (int i = 0; i < 4; i++) {
                if (iter->next->next == NULL) {
                    printf("\n\n");
                    return;
                }
                iter = iter->next;
            }
            printf("\n\n-> %d. Not\n", counter++);
        }

// BASLIK ATLAMA KOMUTU:
        if (iter->ch == '>' && iter->next->ch == '|' && iter->next->next->ch == '<') { // başlık TKD'sine gelirse:
            while (iter->next != NULL) { // Başlık atlanacak ve yazdırılmayacak.
                iter = iter->next;
                if (iter->ch == '>' && iter->next->ch == '|' && iter->next->next->ch == '<') {
                    iter = iter->next->next->next;
                    break;
                }
            }
        }

        printf("%c", iter->ch);
        iter = iter->next;
        if (iter == NULL) break;
    }
    printf("\n\n");
}



/*
void NotTekYazdir (liste *root, int NotNo) {
    liste *iter = root;

    if (!(iter->ch == '>' && iter->next->ch == '|' && iter->next->next->ch == '<')) { // Değilse:
        printf("\n\nProgramda bir hata var!!!\niter hatasi\nProgram sonlandirildi!\n\n");
        return;
    }

    if (NotNo == 1) {   // İlk not isteniyorsa: (Sadece burası çalışacak.
        goto yazdir;    // Başlık atlama döngüsüne gönderiyor.
    }

    while (iter->next != NULL) {
        if (iter->ch == '>' && iter->next->ch == '-' && iter->next->next->ch == NotNo + 47 && iter->next->next->next->ch == '<') {
            for (int i = 0; i < 4; i++) {
                if (iter->next == NULL) {
                    printf("\n\nBagli Liste Yapisinda Bir Hata Var\n--> Program Sonlandirildi\n\n");
                    return;
                }
                iter = iter->next;
            }
            printf("\n\nIlerleme tamamlandi\nNotYazdiriliyor:\n");
            break;
        }
        iter = iter->next;
    }

    yazdir:

// Baslık atlama komutu:
    if (iter->ch == '>' && iter->next->ch == '|' && iter->next->next->ch == '<') { // başlık TKD'sine gelirse:
        iter = iter->next->next;
        int control = 0;
        while (iter->next != NULL) { // Başlık atlanacak ve yazdırılmayacak.
            iter = iter->next;
            if (iter->ch == '>' && iter->next->ch == '|' && iter->next->next->ch == '<') {
                iter = iter->next->next->next;
                control = 1;
                break;
            }
        }
        if (control == 0) {
            printf("\n\nProgramda hata var!!!\nSonlandirildi\n\n");
            return;
        }
    }

    printf("\n\niterin geldiği karakter: %c\n", iter->ch);


    while (iter->next != NULL) {
        if (iter->ch == '>' && iter->next->ch == '-' && iter->next->next->ch == (NotNo + 48) && iter->next->next->next->ch == '<') {
            printf("\n\nNot Buraya kadardi!\n");
            break;
        }
        printf("%c", iter->ch);
        iter = iter->next;
    }
}
*/

void NotTekYazdir (liste *root, int NotNo) {
    liste *iter = root;

    // iter_Exception:
    if (!(iter->ch == '>' && iter->next->ch == '|' && iter->next->next->ch == '<')) {
        printf("\n\nProgramda Hata Var!!!\n");
        return;
    }

    // 1. --> 1
    // 2. --> 3
    // 3. --> 5
    // 4. --> 7
    // 5. --> 9

    int TKD2_counter = 0;
    while (iter->next != NULL) {
        if (iter->ch == '>' && iter->next->ch == '|' && iter->next->next->ch == '<') {
            for (int i = 0; i < 3; i++) { // iter atlama dögüsü:
                if (iter->next != NULL) iter = iter->next;
                else {
                    printf("\n\nBir hata var !\n!--> iter Tasti\n");
                    return;
                }
            }
            TKD2_counter++;
        }
        if (TKD2_counter == ((NotNo * 2) - 1)) break;
        else iter = iter->next;
    }

    printf("\n\nBaslik\n----------------------------------------------------------------------\n");
    while (iter->next != NULL) { // Başlık yazdırma:
        if (iter->ch == '>' && iter->next->ch == '|' && iter->next->next->ch == '<') {
            for (int i = 0; i < 3; i++) { // iter atlama dögüsü:
                if (iter->next != NULL) iter = iter->next;
                else {
                    printf("\n\nBir hata var !\n!--> iter Tasti\n");
                    return;
                }
            }
            break;
        }
        else {
            printf("%c", iter->ch);
            iter = iter->next;
        }
    }

    printf("\nGovde\n----------------------------------------------------------------------\n");
    while (iter->next != NULL) {
        if (iter->ch == '>' && iter->next->ch == '-' && iter->next->next->next->ch == '<') {
            if (iter->next->next->ch != (NotNo + 48) ) {
                printf("\n\nPROGRAMDA CIDDI HATA VAR !!!\nNot Tek Yazdir Fonksiyonu\n");
                return;
            }
            else {
                printf("\n----------------------------------------------------------------------\n\n");
                printf("\n--> Fonksiyon Normal Sonlandirildi.\n");
                return;
            }
        }
        else {
            printf("%c", iter->ch);
            iter = iter->next;
        }
    }
    printf("\n--> Fonksiyon Hatali Sonlandirildi.\n");
}




int NotBaslikOlustur (liste *root, int DosyaVarlik) {
    liste *iter = root;
    if (DosyaVarlik == 1) { // Daha önceden not oluşturulduysa, Notun sonuna gidecek:
        while (iter->next != NULL) iter = iter->next;
    }

    liste *tempRoot = malloc(sizeof(liste));
    liste *tempIter = tempRoot;

    girdi2:

    printf("Lutfen basliginizi giriniz (Max 30 karakter): ");
    char karakter = getchar();
    if (karakter == 9) {
        karakter = getchar();
        if (karakter == 10) {
            printf("\n\nBaslik girmediniz!\nYazim Iptal Edildi!\n\n");
            return 0;
        }
        else tempIter->ch = '\t';
    }
    tempIter->ch = karakter;

    int counter = 1;
    while (1) {
        karakter = getchar();
        if (karakter == 9) {
            karakter = getchar();
            if (karakter == 10) {
                printf("--------------------------------------------------------------------\nYazım bitirildi.\n");
                break;
            }
            else {
                tempIter->next = malloc(sizeof(liste));
                tempIter = tempIter->next;
                tempIter->ch = 9;
                counter++;
            }
        }
        tempIter->next = malloc(sizeof(liste));
        tempIter = tempIter->next;
        tempIter->ch = karakter;
        counter++;
    }
    tempIter->next = NULL;

    if (counter > 30) {
        printf("\n\n!--> Girdiginiz baslik 30 karakterden fazla.\nLutfen daha kisa bir baslik giriniz.\n\n\n");
        tempRoot = malloc(sizeof(liste));
        tempIter = tempRoot;    // tempIter sıfırlanıyor.
        goto girdi2;            // Başlık sorgusuna gönderiyor.
    }
    else if (counter == 0) {
        printf("\n\nBaslik girmediniz!\nYazim Iptal Edildi!\n\n");
        return 0;
    }
    else { // Başlık uygun ise:
        tempIter = tempRoot;
        char TKD2[] = {'>', '|', '<'};
        iter->ch = TKD2[0];
        for (int i = 1; i < 3; i++) { // TKD2 Writer:
            iter->next = malloc(sizeof(liste));
            iter = iter->next;
            iter->ch = TKD2[i];
        }
        while (tempIter != NULL) {
            iter->next = malloc(sizeof(liste));
            iter = iter->next;
            iter->ch = tempIter->ch;
            tempIter = tempIter->next;
        }
        for (int i = 0; i < 3; i++) { // TKD2 Writer:
            iter->next = malloc(sizeof(liste));
            iter = iter->next;
            iter->ch = TKD2[i];
        }
        iter->next = malloc(sizeof(liste));
        iter = iter->next;
        iter->ch = 0;
        free(tempRoot);
        return 1;
    }
}




int NotTumBaslikYazdir (liste *root) {
    liste *iter = root;
    // TKD2:  >|<
    int counter = 1;
    printf("\n\nTum basliklar:\n");
    while (iter->next != NULL) {
        if (iter->ch == '>' && iter->next->ch == '|' && iter->next->next->ch == '<') {
            printf("\n%d-> ", counter++);
            iter = iter->next->next->next;
            while (iter->next != NULL) {
                if (iter->ch == '>' && iter->next->ch == '|' && iter->next->next->ch == '<'){
                    iter = iter->next->next;
                    break;
                }
                printf("%c", iter->ch);
                iter = iter->next;
            }

        }
        iter = iter->next;
    }
    return counter;
}




int DosyaSil (void) {
    int counter = 0;
    if (fopen("qwe.qwe", "r")) {
        remove("qwe.qwe");
        counter++;
    }
    if (fopen("asd.asd", "r")) {
        remove("asd.asd");
        counter++;
    }
    if (fopen("zxc.zxc", "r")) {
        remove("zxc.zxc");
        counter++;
    }
    if (counter == 3) {
        printf("\n\n--> Tum Dosyalar Silindi!\n");
        return 1;
    }
    else if (counter < 3 && counter > 0) {
        printf("\n\n--> Dikkat: Eksik dosya mevcut!\nTum dosyalar silindi\n");
        return 1;
    }
    printf("\n\n--> Dosya zaten silinmis!\n");
    return 0;
}




void SifresizDosyaOkuma (void) {
    FILE *dosya1 = fopen("qwe.qwe", "r");
    while (!feof(dosya1)) {
        char karakter;
        fscanf(dosya1, "%c", &karakter);
        printf("%c", karakter);
    }
    fclose(dosya1);
}




void NotGenelTamOkuma (liste *root) {
    liste *iter = root;
    while (iter->next != NULL) {
        if (iter->ch == '>' && iter->next->ch == '|' && iter->next->next->ch == '<') { // başlık
            printf("\n\nNot Başlığı:  ");
            iter = iter->next->next->next;
            while (iter->next != NULL) { // başlık yazdırma:
                if (iter->ch == '>' && iter->next->ch == '|' && iter->next->next->ch == '<'){
                    iter = iter->next->next->next;
                    break;
                }
                printf("%c", iter->ch);
                iter = iter->next;
            }
            printf("\nNot Govdesi:  ");
        }
        if (iter->ch == '>' && iter->next->ch == '-' && iter->next->next->next->ch == '<') {
            for (int i = 0; i < 4; i++) {
                if (iter->next == NULL) {
                    printf("\n\nPORGRAMDA HATA VAR: NotGenelTamOkuma\n");
                    return;
                }
                if (iter->next == NULL) return;
                iter = iter->next;
            }
        }
        else { // Gövde sonuna gelmediyse:
            if (iter->next == NULL) return;
            if (iter->ch != 0) printf("%c", iter->ch);
            iter = iter->next;
        }
    }
    printf("\n\n");
}




void toUpperCase (liste *root) {
    liste *iter = root;
    if (iter->ch == '>' && iter->next->ch == '|' && iter->next->next->ch == '<') {
        iter = iter->next->next->next;
        int counter = 0;
        while (iter->next != NULL) {
            counter++;
            if (iter->ch == '>' && iter->next->ch == '|' && iter->next->next->ch == '<') {
                printf("\n\nIslem biitrildi.\n");
                break;
            }
            if (iter->ch >= 97 && iter->ch <= 122) {
                iter->ch -= 32;
            }
            if (counter > 30) {
                printf("\n\nBaslik siniri asildi!!!\nProgramda hata var. Sonlandirildi\n\n");
                return;
            }
            iter = iter->next;
        }
    }
    else {
        printf("\n\nRoot hatali gonderildi !!!\nIslem Yapilmadi!\n\n");
        return;
    }
    printf("\n\nIslem Tamamlandi.\n");
}




void ListeSifirla (liste *root) {
    root->ch = 0;
    root->next = NULL;
    root = NULL;
    //printf("\n--> Liste sifirlandi\n");
}





// Normal Menü:
void Menu1Fonk (void) {
    if (DosyaVarlikKontrol()) { // Dosya Var ise:
        liste *root = DosyaListele();
        ListeSifreCoz(root);
        int NotAdedi = NoteCounter(root);
        int control =  NotBaslikOlustur(root, 1);
        if (control == 0) return;
        NotGirdisi(root, NotAdedi);
        ListeSifrele(root);
        ListeDosyala(root);
        ListeSifirla(root);
    }
    else { // Dosya Yok ise:
        liste *root = malloc(sizeof(liste));
        int concrol = NotBaslikOlustur(root, 0);
        if (concrol == 0) return;
        NotGirdisi(root, -1); // Başlık yazıldığı için listenin dolu olduğu göstermek amacıyla -1 gönderiliyor.
        ListeSifrele(root);
        ListeDosyala(root);
    }
}
void Menu2Fonk (void) {
    if (DosyaVarlikKontrol()) {
        liste *root = DosyaListele();
        ListeSifreCoz(root);
        NotGenelTamOkuma(root);
        ListeSifirla(root);
    }
    else printf("\n\nKaydedilmis Not Yok!\n\n");
}
void Menu3Fonk (void) {
    if (DosyaVarlikKontrol()) {
        system("clear");
        liste *root = DosyaListele();
        ListeSifreCoz(root);
        int NotNo, NotAdedi = NoteCounter(root);
        printf("Kaydedilmiş Not Başlıkları");
        int BaslikAdedi = NotTumBaslikYazdir(root) - 1;
        if (BaslikAdedi != NotAdedi) {
            printf("\n\nPROGRAMDA CIDDI HATA VAR !!!\n -- Menu-3 -- \n\n");
            printf("\nBaslik adedi: %d,  Not adedi: %d\n", BaslikAdedi, NotAdedi);
            return;
        }
        printf("\n\nYazdirmak istediginiz notun numarasini giriniz: ");
        scanf("%d", &NotNo);
        getchar();
        system("clear");
        NotTekYazdir(root, NotNo);
        ListeSifirla(root);
    }
    else printf("\n\n-->Dosya Bulunamadi!\n");
}
void Menu8Fonk (void) {
    DosyaSil();
}


// Geliştirici Menüsü:
void GelistiriciMenu1Fonk (void) {
    liste *root = DosyaListele();
    ListeSifreCoz(root);
    int NotAdedi = NoteCounter(root);
    printf("\n\nNot Adedi: %d\n", NotAdedi);
    FullListeYazdirma(root);
}
void GelistiriciMenu2Fonk (void) {
    if (DosyaVarlikKontrol()) { // Dosya Var ise:
        printf("\nDosya Var'a girdi\n");
        liste *root = DosyaListele();
        ListeSifreCoz(root);
        int NotAdedi = NoteCounter(root);
        printf("\nNot adedi: %d\n" ,NotAdedi);
        NotGirdisi(root, NotAdedi);
        ListeSifrele(root);
        ListeDosyala(root);
    }
    else { // Dosya Yok ise:
        printf("\nDosya Yok'a girdi\n");
        liste *root = malloc(sizeof(liste));
        NotGirdisi(root, 0);
        ListeSifrele(root);
        ListeDosyala(root);
    }
}
void GelistiriciMenu3Fonk (void) {
    DosyaSil();
}
void GelistiriciMenu4Fonk (void) {
    SifresizDosyaOkuma();
}
void GelistiriciMenu5Fonk (void) {
    liste *root = DosyaListele();
    FullListeYazdirma(root);
}
void GelistiriciMenu6Fonk (void) {
    printf("\n\nDosya var mi: %d\n", DosyaVarlikKontrol());
}
void GelistiriciMenu7Fonk (void) {
    if (DosyaVarlikKontrol()) {
        liste *root = DosyaListele();
        ListeSifreCoz(root);
        NotOzelTamYazdir(root);
    }
    else printf("\n\nHerhangi bir dosya mevcut degil!\n\n");
}
void GelistiriciMenu8Fonk (void) {
    if (DosyaVarlikKontrol()) {  // Dosya var ise:
        liste *root = DosyaListele();
        ListeSifreCoz(root);
        int NotNo, NotAdedi = NoteCounter(root);
        printf("\n\nKaydedilmis Not Adedi: %d\nYazdirmak istediginiz notun numarasini giriniz: ", NotAdedi);
        scanf("%d", &NotNo);
        NotTekYazdir(root, NotNo);
    }
    else printf("\n\nDosya Bulunamadi!\n");
}
void GelistiriciMenu9Fonk (void) {
    liste *root = DosyaListele();
    ListeSifreCoz(root);
    NotBaslikOlustur(root, 1);
    FullListeYazdirma(root);
    ListeSifrele(root);
    ListeDosyala(root);
}
void GelistiriciMenu10Fonk (void) {
    if (DosyaVarlikKontrol()) {
        liste *root = DosyaListele();
        ListeSifreCoz(root);
        NotTumBaslikYazdir(root);
    }
    else printf("\n\nDosya Bulunamadi\n");
}
void GelistiriciMenu11Fonk (void) {
    if (DosyaVarlikKontrol()) {
        liste *root = DosyaListele();
        ListeSifreCoz(root);
        NotGenelTamOkuma(root);
    }
    else printf("\n\nDosya Bulunamadi\n");
}
void GelistiriciMenu12Fonk (void) {
    liste *rootG = malloc(sizeof(liste));
    NotBaslikOlustur(rootG, 0);
    toUpperCase(rootG);
    FullListeYazdirma(rootG);
}
void GelistiriciMenu13Fonk (void) {
    liste *root = malloc(sizeof(liste));
    NotGirdisi(root, 0);
    ListeDosyala(root);
    liste *root2 = DosyaListele();
    FullListeYazdirma(root2);
}
