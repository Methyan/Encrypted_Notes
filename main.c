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



// FONKSİYONLAR:
void NotGirdisi (liste *root, int NotAdedi);
void ListeSifrele  (liste *root);
liste * DosyaListele (void);
void FullListeYazdirma (liste *root);
void ListeDosyala (liste *root);
void ListeSifreCoz (liste *root);
int DosyaVarlikKontrol (void);
int NoteCounter (liste *root);

int DosyaSilme (void);
void SifresizDosyaOkuma (void);


int main() {
    int secim;

    girdi1:
    printf("[1] Okuma \n[2] Yazma \n[3] Not Sil \n[4] Sifresiz Okuma \n[5] Dosya Listele - Liste Yazdir \n[6]Dosya Varlık Kontrol\n--> Yapacaginiz işlemi giriniz: ");
    scanf("%d", &secim);
    getchar();

    if (secim == 1) { // Okuma yapılacak:
        liste *root = DosyaListele();
        ListeSifreCoz(root);
        int NotAdedi = NoteCounter(root);
        printf("\n\nNot Adedi: %d\n", NotAdedi);
        FullListeYazdirma(root);
    }

    else if (secim == 2) { // Dosyaya yazılacak:
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

    else if (secim == 3) { // Notlar silinecek:
        DosyaSilme();
    }

    else if (secim == 4) { // Sifresiz dosya okuma:
        SifresizDosyaOkuma();
    }

    else if (secim == 5) {
        liste *root = DosyaListele();
        FullListeYazdirma(root);
    }

    else if (secim == 6) {
        printf("\n\nDosya var mi: %d\n", DosyaVarlikKontrol());
    }

    else {
        printf("Hatali bir giris yaptiniz!");
        goto girdi1;
    }


    return 0;
}



/*      FONKSİYON NOTU:      */
// Eğer dosya varsa, dosya listeye atanacak.
// listenin rootu bu fonksiyına gönderilecek.
// Eğer daha önceden dosya yoksa, root'a malloc gönderilecek.

void NotGirdisi (liste *root, int NotAdedi) {  // Kullanıcıdan not girdisi alacak ve listeye yazacak:
    liste *iter = root;
    if (NotAdedi > 0) {
        while (iter->next != NULL) iter = iter->next;
        iter->next = malloc(sizeof(liste));
        iter = iter->next;
    }

    printf("\n\n--> Cumlenizi giriniz. Cikmak icin TAB+ENTER\n--------------------------------------------------------------------\n");
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
