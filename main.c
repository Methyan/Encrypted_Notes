#include <stdio.h>
#include <stdlib.h>

/*
 * Tanımlayıcı karakter dizini:  >-?<
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
int DosyaSilme (void);
void SifresizDosyaOkuma (void);


// MENU FONKSIYONLARI:
void Menu1Fonk (void);
void Menu2Fonk (void);
void Menu3Fonk (void);
void Menu4Fonk (void);
void Menu5Fonk (void);
void Menu6Fonk (void);
void Menu7Fonk (void);
void Menu8Fonk (void);


int main() {
    int secim;

    girdiMain:
    printf("[1] Okuma \n[2] Yazma \n[3] Not Sil \n[4] Sifresiz Okuma \n[5] Dosya Listele - Liste Yazdir \n"
           "[6] Dosya Varlık Kontrol \n[7] Not Ozel Tam Yazdir \n[8] Not Tek Yazdir \n--> Yapacaginiz işlemi giriniz: ");
    scanf("%d", &secim);
    getchar();

    if (secim == 1) Menu1Fonk();         // Okuma yapılacak:

    else if (secim == 2) Menu2Fonk();    // Dosyaya yazılacak:

    else if (secim == 3) Menu3Fonk();    // Notlar silinecek:

    else if (secim == 4) Menu4Fonk();    // Sifresiz dosya okuma:

    else if (secim == 5) Menu5Fonk();    // Dosya Listele - Yazdır

    else if (secim == 6) Menu6Fonk();    // Dosya Varlık Kontrol

    else if (secim == 7) Menu7Fonk();    // Not Ozel Tam Yazdır

    else if (secim == 8) Menu8Fonk();    // İsteenilen notu tek olarak yazdırır.

    else {
        printf("Hatali bir giris yaptiniz!");
        goto girdiMain;
    }                           // Hatali girişte girdiMain'e geri döndürecek.


    return 0;
}




void NotGirdisi (liste *root, int NotAdedi) {  // Kullanıcıdan not girdisi alacak ve listeye yazacak:
    liste *iter = root;

    if (NotAdedi > 0) { // Daha önceden not oluşturulduysa:
        while (iter->next != NULL) iter = iter->next;
        iter->next = malloc(sizeof(liste));
        iter = iter->next;
    }

    printf("\n\n--> Notunuzu giriniz. Cikmak icin TAB+ENTER\n--------------------------------------------------------------------\n");
    int counter1 = 0;
    char karakter;
    while (1) {
        karakter = getchar();
        if (karakter == 9) {
            karakter = getchar();
            if (karakter == 10) {
                printf("--------------------------------------------------------------------\nYazım bitirildi.\n");
                break;
            }
            else {
                iter->ch = 9;
                iter->next = malloc(sizeof(liste));
                iter = iter->next;
            }
        }
        iter->ch = karakter;
        counter1++;
        iter->next = malloc(sizeof(liste));
        iter = iter->next;
    }

    // TKD'de fonksiyondan dönen sayaca göre sıra numarası verilecek (? işareti yerine).
    // 5. birime atanan değer Not adedinin karakter karşılığının bir fazlasıdır.
    // TANIMLAYICI KARAKTER DIZISI:  >-?<   (? işareti yarine sıra numarası gelecek).

    char TKD[] = {'>', '-', NotAdedi + 49, '<'};
    for (int i = 0; i < 4; i++) {
        iter->ch = TKD[i];
        iter->next = malloc(sizeof(liste));
        iter = iter->next;
    }
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
    liste *root = malloc(sizeof(liste));
    liste *iter = root;

    while (!feof(dosya1)) {
        char karakter = fgetc(dosya1);
        iter->ch = karakter;
        iter->next = malloc(sizeof(liste));
        iter = iter->next;
    }
    fclose(dosya1);
    return root;
}




int DosyaVarlikKontrol (void) {
    if (fopen("qwe.qwe", "r")) {
        return 1; // Dosya var.
    }
    return 0; // Dosya yok.
}




void FullListeYazdirma (liste *root) {
    printf("\n\nListenin icindekiler:\n");
    while (root->next != NULL) {
        printf("%c", root->ch);
        root = root->next;
    }
    printf("\n\n");
}




void ListeDosyala (liste *root) {
    liste *iter = root;
    FILE *dosya1 = fopen("qwe.qwe", "w+");
    while (iter->next != NULL) {
        fprintf(dosya1, "%c", iter->ch);
        iter = iter->next;
    }
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
    // TKD:  >-?<
    liste *iter = root;
    int counter = 0;
    while (iter->next != NULL) { // TKD sayacı:
        if (iter->ch == '>' && iter->next->ch == '-' && iter->next->next->next->ch == '<'){
            counter++;
        }
        iter = iter->next;
    }
    return counter;
}




void NotOzelTamYazdir (liste *root) { // Tüm nootları TKD olmadan yazdırıyor:
    int counter = 1;
    printf("\n\n-> %d. Not\n", counter++);
    liste *iter = root;
    while (iter->next != NULL) {
        if (iter->ch == '>' && iter->next->ch == '-' && iter->next->next->next->ch == '<'){
            for (int i = 0; i < 6; i++) {
                if (iter->next == NULL) {
                    printf("\n\n");
                    return;
                }
                iter = iter->next;
            }
            printf("\n\n-> %d. Not\n", counter++);
        }
        printf("%c", iter->ch);
        iter = iter->next;
        if (iter == NULL) break;
    }
    printf("\n\n");
}




void NotTekYazdir (liste *root, int NotNo) {
    liste *iter = root;

    if (NotNo == 1) {   // İlk not isteniyorsa: (Sadece burası çalışacak.
        goto yazdir;    // 2. while döngüsüne gönderiyor.
    }

    while (iter->next != NULL) {
        if (iter->ch == '>' && iter->next->ch == '-' && iter->next->next->ch == NotNo + 47 && iter->next->next->next->ch == '<') {
            for (int i = 0; i < 6; i++) {
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

    while (iter->next != NULL) {
        if (iter->ch == '>' && iter->next->ch == '-' && iter->next->next->ch == NotNo + 48 && iter->next->next->next->ch == '<') {
            printf("\nNot buraya kadardi!\n");
            break;
        }
        printf("%c", iter->ch);
        iter = iter->next;
    }
}





int DosyaSilme (void) {
    if (fopen("qwe.qwe", "r")) {
        remove("qwe.qwe");
        printf("\n\nDosya Silindi.\n");
        return 1;
    }
    printf("Dosya bulunamadi!");
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




void Menu1Fonk (void) {
    liste *root = DosyaListele();
    ListeSifreCoz(root);
    int NotAdedi = NoteCounter(root);
    printf("\n\nNot Adedi: %d\n", NotAdedi);
    FullListeYazdirma(root);
}
void Menu2Fonk (void) {
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
void Menu3Fonk (void) {
    DosyaSilme();
}
void Menu4Fonk (void) {
    SifresizDosyaOkuma();
}
void Menu5Fonk (void) {
    liste *root = DosyaListele();
    FullListeYazdirma(root);
}
void Menu6Fonk (void) {
    printf("\n\nDosya var mi: %d\n", DosyaVarlikKontrol());
}
void Menu7Fonk (void) {
    if (DosyaVarlikKontrol()) {
        liste *root = DosyaListele();
        ListeSifreCoz(root);
        NotOzelTamYazdir(root);
    }
    else printf("\n\nHerhangi bir dosya mevcut degil!\n\n");
}
void Menu8Fonk (void) {
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
