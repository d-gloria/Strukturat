#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_AUTOR 10
#define MAX_LIBRA 20

struct libri {
    int id;
    int faqe;
    char isbn[13];
    char titulli[21];
} librat[MAX_LIBRA];

struct autori {
    int id;
    char emri[20];
    char mbiemri[20];
    struct libri librat[5];
} autoret[MAX_AUTOR];

int nr_librave = 0;
int nr_autoreve = 0;

int nr_librave_isbn_shkronje(struct libri librat[]) {
    int i;
    int counter = 0;
    for (i = 0; i < nr_librave; i++) {
        if (isalpha(librat[i].isbn[0]) && islower(librat[i].isbn[0])) {
            counter++;
        }
    }
    return counter;
}

int nr_librave_autor(struct autori autor) {
    int length = 0;
    while (autor.librat[length].id != -1) {
        length++;
    }
    return length;
}

char* me_shume_libra(struct autori autoret[]) {
    int i, max = 0;
    char* emri;
    int j;
    for (i = 0; i < nr_autoreve; i++) {
        if (nr_librave_autor(autoret[i]) > max) {
            max = nr_librave_autor(autoret[i]);
            j = i;
            emri = autoret[i].emri;
        }
    }
    return emri;
}

int gjej_liber_titull(char titull[]) {
    int i;
    for (i = 0; i < nr_librave; i++)
        if (strcmp(librat[i].titulli, titull) == 0)
            return i;
    return -1;
}

int gjej_liber_isbn(char isbn[]) {
    int i;
    for (i = 0; i < nr_librave; i++)
        if (strcmp(librat[i].isbn, isbn) == 0)
            return i;
    return -1;
}

void shtoLibra() {
    if (nr_librave == MAX_LIBRA) {
        printf("Nuk mund te shtohet");
        return;
    }
    printf("Vendos titullin:");
    scanf("%s", librat[nr_librave].titulli);
    printf("Vendos isbn:");
    scanf("%s", librat[nr_librave].isbn);
    printf("Vendos nr e faqeve:");
    scanf("%d", &librat[nr_librave].faqe);
    if (gjej_liber_isbn(librat[nr_librave].isbn) >= 0) {
        printf("Kjo isbn ekziston");
    } else {
        nr_librave++;
    }
}

struct libri titulli_me_i_gjate(struct libri librat[]) {
    int i;
    int poz = 0;
    int max = 0;
    for (i = 0; i < nr_librave; i++) {
        if (strlen(librat[i].titulli) > max) {
            max = strlen(librat[i].titulli);
            poz = i;
        }
    }
    return librat[poz];
}

char* gjej_libri_faqe(struct libri librat[]) {
    int i;
    int min = librat[0].faqe;
    int j;
    char* temp;
    for (i = 1; i < nr_librave; i++) {
        if (librat[i].faqe < min) {
            min = librat[i].faqe;
            j = i;
        }
    }
    return librat[j].titulli;
}

void shtoAutorLibra() {
    if (nr_autoreve == MAX_AUTOR) {
        printf("Nuk mund te shtohet ky autor.\n");
        return;
    }

    printf("Vendos emrin e autorit: ");
    scanf("%s", autoret[nr_autoreve].emri);

    printf("Vendos mbiemrin e autorit: ");
    scanf("%s", autoret[nr_autoreve].mbiemri);

    printf("Vendos ID e autorit: ");
    scanf("%d", &autoret[nr_autoreve].id);

    printf("Vendos numrin e librave qe ka autori, deri ne 5: ");
    int nr_libra;
    scanf("%d", &nr_libra);

    if (nr_libra < 1 || nr_libra > 5) {
        printf("Numri i librave i pavlefshem.\n");
        return;
    }

    int i;
    for (i = 0; i < nr_libra; i++) {
        printf("Vendos ID e librit %d: ", i + 1);
        int libri_id;
        scanf("%d", &libri_id);

        int libri_index = gjej_liber_titull(libri_id);
        if (libri_index != -1) {
            autoret[nr_autoreve].librat[i] = librat[libri_index];
        } else {
            printf("Libri me ID %d nuk ekziston.\n", libri_id);
            return;
        }
    }

    nr_autoreve++;
    printf("Autori u shtua me sukses.\n");
}

void listeMeLibratAutor() {
    char emri_autor[20];
    printf("Vendos emrin e autorit per te shfaqur librat e tij: ");
    scanf("%s", emri_autor);

    int i, j;
    for (i = 0; i < nr_autoreve; i++) {
        if (strcmp(autoret[i].emri, emri_autor) == 0) {
            printf("Librat e autorit %s:\n", emri_autor);
            for (j = 0; j < nr_librave_autor(autoret[i]); j++) {
                printf("%d. %s\n", j + 1, autoret[i].librat[j].titulli);
            }
            return;
        }
    }
    printf("Autori %s nuk u gjet ne sistemin tone.\n", emri_autor);
}

void menuja() {
    printf("\nMENU:\n");
    printf("1. Shto liber\n");
    printf("2. Shto autor dhe atribuo librat\n");
    printf("3. Shfaq librat e nje autorit\n");
    printf("4. Numer librat me ISBN shkronje\n");
    printf("5. Emri i autorit qe ka me shume libra\n");
    printf("6. Titulli me i gjate i librit\n");
    printf("7. Gjej librin me faqet me te pakta\n");
    printf("8. Dil\n");
}

int main() {
    int zgjedhja;
    do {
        menuja();
        printf("Zgjedhja juaj: ");
        scanf("%d", &zgjedhja);
        switch (zgjedhja) {
            case 1:
                shtoLibra();
                break;
            case 2:
                shtoAutorLibra();
                break;
            case 3:
                listeMeLibratAutor();
                break;
            case 4:
                printf("Numeri i librave me ISBN shkronje: %d\n", nr_librave_isbn_shkronje(librat));
                break;
            case 5:
                printf("Emri i autorit qe ka me shume libra: %s\n", me_shume_libra(autoret));
                break;
            case 6:
                printf("Titulli me i gjate i librit: %s\n", titulli_me_i_gjate(librat).titulli);
                break;
            case 7:
                printf("Libri me faqet me te pakta: %s\n", gjej_libri_faqe(librat));
                break;
            case 8:
                printf("Duke mbyllur programin.\n");
                break;
            default:
                printf("Zgjedhje e pavlefshme, provo perseri.\n");
                break;
        }
    } while (zgjedhja != 8);

    return 0;
}