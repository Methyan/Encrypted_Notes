#include <stdio.h>
#include <stdlib.h>

/*
 * Tanımlayıcı karakter dizini:  </13-?>
 */


typedef struct liste {
    char ch;
    struct liste *next;
} liste;



int DosyayaYazma (void);
void Liste_Yazdirma (liste *root);
void SifresizDosyaOkuma (void);
int NoteCounter (void);
void SifreliDosyaOkuma (void);

int main() {
    int secim;

    girdi1:
    printf("[1] Okuma \n[2] Yazma \n[3] Not Sil \n[4] Sifresiz Okuma \n--> Yapacaginiz işlemi giriniz: ");
    scanf("%d", &secim);
    getchar();

    if (secim == 1) { // Okuma yapılacak:
        SifreliDosyaOkuma();
    }

    else if (secim == 2) { // Dosyalara yazılacak:
        DosyayaYazma();
    }

    else if (secim == 3) { // Notlar silinecek
    }

    else if (secim == 4) { // Sifresiz dosya okuma:
        SifresizDosyaOkuma();
    }

    else {
        printf("Hatali bir giris yaptiniz!");
        goto girdi1;
    }



    return 0;
}





int DosyayaYazma (void) {
    int NotAdedi = NoteCounter();
    printf("\n\nNot adedi: %d\n\n", NotAdedi);

    FILE *dosya1 = fopen("qwe.qwe", "a+");


// Not girdisinin alınması:
    liste *root = (liste *) malloc(sizeof(liste));
    liste *iter = root;
    printf("\n\n--> Cumlenizi giriniz. Cikmak icin TAB+ENTER\n--------------------------------------------------------------------\n");
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
        iter->next = malloc(sizeof(liste));
        iter = iter->next;
    }



// Cyrpting & File Write:
    iter = root;
    int counter = 0;
    while (iter->next != NULL) {
        counter++;
        if (counter % 3 == 0) {
            char nmbr = iter->ch;
            nmbr += (counter % 7);
            printf("%d ", nmbr);
            fprintf(dosya1, "%c", nmbr);
        }
        else if (counter % 3 == 1) {
            char nmbr = iter->ch;
            nmbr += ((counter % 4) + 1);
            printf("%d ", nmbr);
            fprintf(dosya1, "%c", nmbr);
        }
        else if (counter % 3 == 2) {
            char nmbr = iter->ch;
            nmbr += (counter + 31);
            printf("%d ", nmbr);
            fprintf(dosya1, "%c", nmbr);
        }
        iter = iter->next;
    }


    // TKD'de fonksiyondan dönen sayaca göre sıra numarası verilecek (? işareti yerine).
    // 5. birime atanan değer Not adedinin karakter karşılığının bir fazlasıdır.
    // TANIMLAYICI KARAKTER DIZISI:  </13-?>   (? işareti yarine sıra numarası gelecek)

    char TKD[10] = {'<', '/', '1', '3', '-', NotAdedi + 49, '>'};
    fprintf(dosya1, "\n%s\n\n", TKD);


    fclose(dosya1);
    return 1;
}





int NoteCounter (void) {
    FILE *dosya1 = fopen("qwe.qwe", "a+");
    rewind(dosya1);
    int counter = 0;
    while (!feof(dosya1)) {
        char karakter = fgetc(dosya1);
        if (karakter == '<') {
            karakter = fgetc(dosya1);
            if (karakter == '/') {
                karakter = fgetc(dosya1);
                if (karakter == '1') {
                    karakter = fgetc(dosya1);
                    if (karakter == '3') {
                        karakter = fgetc(dosya1);
                        if (karakter == '-') {
                            fgetc(dosya1);
                            karakter = fgetc(dosya1);
                            if (karakter == '>') {
                                counter++;
                            }
                        }
                    }
                }
            }
        }
    }
    fclose(dosya1);
    return counter;
}


// İleriki aşamalarda istenilen notu göstermesi için notu numarası parametresi alabilir.
void SifreliDosyaOkuma (void) {
    printf("\n\nSifre Cozuldu.\nNotunuz:\n--------------------------------------------------------------------\n");
    FILE *dosya1 = fopen("qwe.qwe", "r+");
    int counter = 0;
    while (!feof(dosya1)) {
        counter++;
        if (counter % 3 == 0) {
            char nmbr;
            fscanf(dosya1, "%c", &nmbr);
            if (nmbr == 0) break;
            nmbr -= (counter % 7);
            printf("%c", nmbr);
        }
        else if (counter % 3 == 1) {
            char nmbr;
            fscanf(dosya1, "%c", &nmbr);
            if (nmbr == 0) break;
            nmbr -= ((counter % 4) + 1);
            printf("%c", nmbr);
        }
        else if (counter % 3 == 2) {
            char nmbr;
            fscanf(dosya1, "%c", &nmbr);
            if (nmbr == 0) break;
            nmbr -= (counter + 31);
            printf("%c", nmbr);
        }
    }
    fclose(dosya1);
    printf("\n--------------------------------------------------------------------\n");
}






void SifresizDosyaOkuma (void) {
    FILE *dosya1 = fopen("qwe.qwe", "r");
    while (!feof(dosya1)) {
        char karakter;
        fscanf(dosya1, "%c", &karakter);
        printf("%d ", karakter);
    }
    fclose(dosya1);
}




void Liste_Yazdirma (liste *root) {
    printf("\n\nListenin icindekiler:\n");
    while (root->next!= NULL) {
        printf("%c", root->ch);
        root = root->next;
    }
    printf("\n\n");
}
