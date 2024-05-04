#include <stdio.h>
#include <string.h>
#define MAX_PERSONA 3

struct person {
    char emri [20];
    char mbiemri [20];
    int mosha;
} person[MAX_PERSONA];

struct student {
    char nrMatrikullimi [20];
};

int personi_vjeter (struct person p[]){
    int i;
    int max = 0;
    for(i=0; i<MAX_PERSONA; i++){
        if(p[i].mosha > max){
            max = p[i].mosha;
        }
    }
    return max;
}

void emriPerpara(struct person p[]){
    int i;
    for(i=0; i<MAX_PERSONA-1; i++){
        if((strcmp(p[i].emri, p[i+1].emri)) == 1){
            printf("\nEmri %s eshte mbrapa emrit %s", p[i].emri, p[i+1].emri);
        }else if((strcmp(p[i].emri, p[i+1].emri)) == 0){
            printf("\nEmrat %s dhe %s jane njesoj",p[i].emri, p[i+1].emri);
        }else if((strcmp(p[i].emri, p[i+1].emri)) == -1){
            printf("\nEmri %s eshte me perpara se emri %s", p[i].emri, p[i+1].emri);
        }
    }
}

void rendit(struct person p[]){
    int i, j;
    for(i=0; i<MAX_PERSONA-1; i++){
        for(j=i+1; j<MAX_PERSONA; j++){
            if((strcmp(p[i].emri, p[j].emri)) == 1){
                struct person temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
            else if((strcmp(p[i].emri, p[j].emri)) == 0){
                if((strcmp(p[i].mbiemri, p[j].mbiemri)) == 1){
                    struct person temp = p[i];
                    p[i] = p[j];
                    p[j] = temp;
            }
            }
}
    }}


struct person printoDhena(struct person person){
    printf("\nEmri: %s", strlwr(person.emri));
    printf("\nMbiemri: %s", strupr(person.mbiemri));
    //printf("\nEmri.Mbiemri: %s", strcpy(p.emri, p.mbiemri));
    printf("\nMosha: %d", person.mosha);
    return person;
}

int u_fillon_emri_me(char shkronja, struct person p[], int numriPersonave) {
    int numri = 0;
    for (int i = 0; i < numriPersonave; i++) {
        if (p[i].emri[0] == shkronja || p[i].emri[0] == (shkronja + 32) || p[i].emri[0] == (shkronja - 32)) {
            numri++;
        }
    }
    return numri;
}

struct person personMeMbiemrinMeTeGjate(struct person p[], int numriPersonave) {
    struct person personMeMbiemrinGjate = p[0];

    for (int i = 1; i < numriPersonave; i++) {
        if (strlen(p[i].mbiemri) > strlen(personMeMbiemrinGjate.mbiemri)) {
            personMeMbiemrinGjate = p[i];
        }
    }

    return personMeMbiemrinGjate;
}

int main(){
    int i;

    int numriPersonave;
    printf("Jep numrin e personave: ");
    scanf("%d", &numriPersonave);

    if (numriPersonave > MAX_PERSONA) {
        printf("Numri i personave eshte me i madh se %d. Programi do te mbyllet.", MAX_PERSONA);
        return 1;
    }
    for(i=0; i<numriPersonave; i++){
        printf("Jep emrin e personit: ");
        scanf("%s", &person[i].emri);
        //printf("Jep emrin e personit: ");
        //gets(person[i].emri);
        printf("Jep mbiemrin e personit: ");
        scanf("%s", &person[i].mbiemri);
        printf("Jep moshen e personit: ");
        scanf("%d", &person[i].mosha);
    }

    printf("\nMosha me e madhe: %d", personi_vjeter(person));
    emriPerpara(person);

    for(i=0; i<MAX_PERSONA; i++){
        printoDhena(person[i]);
    }

    char shkronja;
    printf("\nJep shkronjen per te numeruar personat: ");
    scanf(" %c", &shkronja);

    int c = u_fillon_emri_me(shkronja, person, numriPersonave);
    printf("Numri i personave qe fillon emri me shkronjen '%c' eshte: %d\n", shkronja, c);

    struct person personMbiemriGjate = personMeMbiemrinMeTeGjate(person, numriPersonave);
    printf("Personi me mbiemrin me te gjate:\n");
    printf("Emri: %s\n", personMbiemriGjate.emri);
    printf("Mbiemri: %s\n", personMbiemriGjate.mbiemri);
    printf("Mosha: %d\n", personMbiemriGjate.mosha);

    return 0;
}