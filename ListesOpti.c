#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                type booleen                   */
/*                                               */
/*************************************************/

typedef enum {false, true} bool;

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc {
    int valeur ;
    struct Bloc * suite;
} Bloc;

typedef Bloc* Liste ;

typedef struct LBloc {
    Liste valeur ;
    struct LBloc* suite;
} LBloc;

typedef LBloc* LListe ;

/*****************************/
/*                           */
/*         Compteurs         */
/*                           */
/*****************************/

int malloc_count_liste = 0;
int malloc_count_lliste = 0;

int free_count_liste = 0;
int free_count_lliste = 0;

/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/

void depile(Liste *L) {
    Liste tmp = *L ;
    *L = (*L)->suite ;
    free_count_liste++;
    free(tmp);
}

void VideListe(Liste *L) {
    if ( *L != NULL ) {
        depile(L);
        VideListe(L);
    }
}

void depileL(LListe* LL) {
    LListe tmp = *LL;
    *LL = (*LL)->suite;
    VideListe(&(tmp->valeur));
    free_count_lliste++;
    free(tmp);
}

void VideLListe(LListe *LL) {
    if ( *LL != NULL ) {
        depileL(LL);
        VideLListe(LL);
    }
}

void depileL_SSL(LListe* LL) { // SSL : sans vider les sous listes
    LListe tmp = *LL;
    *LL = (*LL)->suite;
    free_count_lliste++;
    free(tmp);
}

void VideLListeSSL(LListe *LL) { // SSL : sans vider les sous listes
    if ( *LL != NULL ) {
        depileL_SSL(LL);
        VideLListeSSL(LL);
    }
}

Liste ajoute(int x, Liste l) {
    Liste tmp = (Liste) malloc(sizeof(Bloc));
    if (tmp == NULL) {
        perror("erreur malloc\n");
        exit(EXIT_FAILURE);
    }
    malloc_count_liste++;
    tmp->valeur = x ;
    tmp->suite = l ;
    return tmp ;
}

LListe ajouteL(Liste l, LListe ll) {
    LListe tmp = (LListe) malloc(sizeof(LBloc));
    if (tmp == NULL) {
        perror("erreur malloc\n");
        exit(EXIT_FAILURE);
    }
    malloc_count_lliste++;
    tmp->valeur = l;
    tmp->suite = ll;
    return tmp;
}

void empile(int x, Liste *L) { *L = ajoute(x,*L) ; }

void empileL(Liste l, LListe *LL) { *LL = ajouteL(l,*LL) ; }

/*****************************/
/*                           */
/*          Affiche          */
/*                           */
/*****************************/

void affiche_iter(Liste l) {
    Liste L2 = l;
    printf("[");
    while( L2 != NULL ) {
        if (L2->suite == NULL) printf("%d", L2->valeur);
        else printf("%d, ", L2->valeur);
        L2 = L2->suite;
    }
    printf("]\n");
}

void affiche_iter_sans_retour_ligne(Liste l) {
    Liste L2 = l;
    printf("[");
    while( L2 != NULL ) {
        if (L2->suite == NULL) printf("%d", L2->valeur);
        else printf("%d, ", L2->valeur);
        L2 = L2->suite;
    }
    printf("]");
}

void affiche_iterLL(LListe ll) {
    LListe LL2 = ll;
    printf("[");
    while(LL2 != NULL) {
        if (LL2->suite == NULL) affiche_iter_sans_retour_ligne(LL2->valeur);
        else {affiche_iter_sans_retour_ligne(LL2->valeur); printf(", ");}
        LL2 = LL2->suite;
    }
    printf("]\n");
}

/****************************/
/*                          */
/*         Copie            */
/*                          */
/****************************/

Liste copieListe(Liste l) {
    if (l == NULL) return NULL;
    return ajoute(l->valeur, copieListe(l->suite));
}

LListe copieLListe(LListe ll) {
    if (ll == NULL) return NULL;
    return ajouteL(copieListe(ll->valeur), copieLListe(ll->suite));
}

/****************************/
/*                          */
/*         Concat           */
/*                          */
/****************************/

LListe concat(LListe ll1, LListe ll2) { // copies sans free
    if (ll1 == NULL) return ll2;
    else {
        return ajouteL(ll1->valeur, concat(ll1->suite, ll2));
    }
}

/*************************************************/
/*                                               */
/*               Interclassement                 */
/*                                               */
/*************************************************/

LListe AETTL(int x, LListe ll) {
    if (ll == NULL) return NULL;
    else {
        LListe aettl = AETTL(x, ll->suite);
        LListe result = ajouteL(ajoute(x, ll->valeur), aettl);
        return result;
    }
}

LListe Interclassements(Liste l1, Liste l2) {
    LListe result;
    if (l1 == NULL) {
        Liste copieL2 = copieListe(l2);
        result = ajouteL(copieL2, NULL);
    }
    else if (l2 == NULL) {
        Liste copieL1 = copieListe(l1);
        result = ajouteL(copieL1, NULL);
    }
    else {
        Liste copieL1 = copieListe(l1);
        Liste copieL2 = copieListe(l2);
        LListe interclass1 = Interclassements(copieL1->suite, copieL2);
        LListe interclass2 = Interclassements(copieL1, copieL2->suite);
        VideListe(&copieL1);
        VideListe(&copieL2);

        LListe aettl1 = AETTL(l1->valeur, interclass1);
        LListe aettl2 = AETTL(l2->valeur, interclass2);
        result = concat(aettl1, aettl2);

        VideLListeSSL(&aettl1);
        VideLListeSSL(&interclass1);
        VideLListeSSL(&interclass2);
    }
    return result;
}

/*************************************************/
/*                                               */
/*                    Main                       */
/*                                               */
/*************************************************/


int main(int argc, char** argv) {

    printf("------------------------------------------------------\n");

    //Liste l1 = ajoute(1, ajoute(2, ajoute(3, NULL)));
    //Liste l2 = ajoute(4, ajoute(5, NULL));


    Liste l1 = ajoute(1, ajoute(2, NULL));
    Liste l2 = ajoute(2, ajoute(3, NULL));

    LListe ll = Interclassements(l1, l2);
    printf("|>  l1 = "); affiche_iter(l1);
    printf("|>  l2 = "); affiche_iter(l2);
    printf("|>  ll = "); affiche_iterLL(ll);

    printf("------------------------------------------------------\n");

    VideListe(&l1);
    VideListe(&l2);
    VideLListe(&ll);
    printf("Listes videes avec succes\n");

    printf("------------------------------------------------------\n");

    printf("Nombre de MALLOCs du type Liste = %d\n", malloc_count_liste);
    printf("Nombre de MALLOCs du type LListe = %d\n", malloc_count_lliste);
    printf("Nombre de FREEs du type Liste = %d\n", free_count_liste);
    printf("Nombre de FREEs du type LListe = %d\n", free_count_lliste);

    printf("------------------------------------------------------\n");

    if (malloc_count_liste != free_count_liste) {
        printf("Fuite memoire detectee dans Liste : %d blocs non liberes\n",
               malloc_count_liste - free_count_liste);
    }
    if (malloc_count_lliste != free_count_lliste) {
        printf("Fuite memoire detectee dans LListe : %d blocs non liberes\n",
               malloc_count_lliste - free_count_lliste);
    }

    return 0;

}
