#include <stdio.h>
#include <stdbool.h>
#define GJAT_EMER 25
#define MAX_ARTIKULL 100

struct artikull {
    int numri;
    char emri[GJAT_EMER + 1];
    int gjendja;
} inventari[MAX_ARTIKULL];

int nr_artikull = 0;
int gjej_artikull(int numer);
void shto(void);
void kerko(void);
void update(void);
void printo(void);
int lexo_rresht(char str[], int n);
int artikuj_zero_gjendje(void);
int artikuj_nje_shifror(void);
bool eshte_nje_shifror(int numri);

int main()
{
    char kodi[10];

    for (;;)
    {
        printf("\nZgjidhni nje nga veprimet:\n");
        printf("1. Shto artikull\n");
        printf("2. Kerko artikull\n");
        printf("3. Update artikull\n");
        printf("4. Printo inventarin\n");
        printf("5. Numri i artikujve me gjendje zero\n");
        printf("6. Artikujt me kod nje shifror\n");
        printf("7. Dil\n");
        printf("Zgjidhja: ");

        scanf("%s", kodi);

        switch (kodi[0])
        {
        case '1':
            shto();
            break;
        case '2':
            kerko();
            break;
        case '3':
            update();
            break;
        case '4':
            printo();
            break;
        case '5':
            printf("Numri i artikujve me gjendje zero: %d\n", artikuj_zero_gjendje());
            break;
        case '6':
            printf("Artikujt me kod nje shifror:\n");
            artikuj_nje_shifror();
            break;
        case '7':
            return 0; // Exit
        default:
            printf("Zgjidhje e pasakte. Ju lutem zgjidhni nga opsionet e dhena.\n");
        }
    }
    return 0;
}

int gjej_artikull(int numri)
{
    int i;
    for (i = 0; i < nr_artikull; i++)
        if (inventari[i].numri == numri)
            return i;
    return -1;
}

void shto(void)
{
    int artikull_nr;
    if (nr_artikull == MAX_ARTIKULL)
    {
        printf("Databaza eshte plot; nuk mund te shtohet asnje artikull.\n");
        return;
    }
    printf("Fut numrin e artikullit: ");
    scanf("%d", &artikull_nr);
    if (gjej_artikull(artikull_nr) >= 0)
    {
        printf("Artikulli egziston.\n");
        return;
    }

    inventari[nr_artikull].numri = artikull_nr;
    printf("Jep emrin e artikullit: ");
    lexo_rresht(inventari[nr_artikull].emri, GJAT_EMER);
    printf("\nJep gjendjen e artikullit:");
    scanf("%d", &inventari[nr_artikull].gjendja);
    nr_artikull++;
}

void kerko(void)
{
    int i, numer;
    printf("Jep numrin e artikullit: ");
    scanf("%d", &numer);
    i = gjej_artikull(numer);
    if (i >= 0)
    {
        printf("Emri i artikullit: %s\n", inventari[i].emri);
        printf("Gjendja e artikullit: %d\n", inventari[i].gjendja);
    }
    else
        printf("Artikulli nuk u gjet.\n");
}

void update(void)
{
    int i, numer, ndryshimi;
    printf("Jep numrin e artikullit: ");
    scanf("%d", &numer);
    i = gjej_artikull(numer);
    if (i >= 0)
    {
        printf("Jep ndryshimin ne gjendje te artikullit: ");
        scanf("%d", &ndryshimi);
        inventari[i].gjendja += ndryshimi;
    }
    else
        printf("Artikulli nuk u gjet.\n");
}

void printo(void)
{
    int i;
    printf("Numri i Artikullit Emri i Artikullit "
           "Gjendja e Artikullit\n");
    for (i = 0; i < nr_artikull; i++)
        printf("%7d %25s %25d\n", inventari[i].numri, inventari[i].emri, inventari[i].gjendja);
}

int lexo_rresht(char str[], int n){
    int ch, i = 0;
    while ((ch = getchar()) == ' ')
        ;
    while ((ch = getchar()) != '\n')
    {
        if (i < n)
            str[i++] = ch;
    }
    str[i] = '\0';
    return i;
}
int artikuj_zero_gjendje(void){
    int i, count = 0;
    for (i = 0; i < nr_artikull; i++)
    {
        if (inventari[i].gjendja == 0)
            count++;
    }
    return count;
}
int artikuj_nje_shifror(void){
    int i, count = 0;
    printf("Numri\tEmri\tGjendja\n");
    for (i = 0; i < nr_artikull; i++)
    {
        if (eshte_nje_shifror(inventari[i].numri))
        {
            printf("%d\t%s\t%d\n", inventari[i].numri, inventari[i].emri, inventari[i].gjendja);
            count++;
        }
    }
    return count;
}

bool eshte_nje_shifror(int numri){
    return (numri >= 0 && numri < 10);
}
