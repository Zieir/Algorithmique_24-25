/*******************************{    RENDU PARTIE2    }********************************/
/**                                                                                  **/
/**   1. MEDJADJ Mohamed Abderraouf:   mohamed-abderraouf.medjadj@etu-upsaclay.fr    **/
/**                                                                                  **/
/**   2. KERMADJ Zineddine:   zineddine.kermadj@etu-upsaclay.fr                      **/
/**                                                                                  **/
/**************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                type bool�en                   */
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

/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/


/*** les 5 fonctionnalit�s suivantes sont plus du sucre syntaxique que du code utile  ***/
/*** sauf � vouloir pouvoir basculer � moindre frais sur une impl�menation des listes ***/
/**** diff�rentes des listes chain�es propos�es dans le cadre de ce projet            ***/

// Liste Vide() { return NULL ; }
// void initVide(Liste *L) { *L = NULL ; }
// bool estVide(Liste l) { return l == NULL ; }
// int premier(Liste l) { return l->valeur ; }
// Liste suite(Liste l) { return l->suite ; }

/****************/

void depile(Liste *L) {
    Liste tmp = *L ;
    *L = (*L)->suite ;
    free(tmp) ;
}

Liste ajoute(int x, Liste l) {
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->valeur = x ;
    tmp->suite = l ;
    return tmp ;
}

void empile(int x, Liste *L) { *L = ajoute(x,*L) ; }

/*****************************/
/*                           */
/*       Affiche             */
/*                           */
/*****************************/

void affiche_rec(Liste l) {
    if (l == NULL)
        printf("\n");
    else {
        printf("%d ", l->valeur);
        affiche_rec(l->suite);
    }
}

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

/****************************/
/*                          */
/*       Longueur           */
/*                          */
/****************************/

int longueur_rec (Liste l) {
    if (l == NULL)
        return 0 ;
    else return (1 + longueur_rec(l->suite)) ;
}


int longueur_iter (Liste l) {
    Liste P = l;
    int cpt = 0 ;
    while (P != NULL) {
        P = P->suite ;
        cpt++ ;
    }
    return cpt ;
}

/*****************************************/
/*                                       */
/*                 VireDernier           */
/*     avec un depile                    */
/* � la main opportuniste (version iter) */
/* ou en utilisant depiie (version rec ) */
/*                                       */
/*****************************************/

void VD (Liste *L) {     // *L non NULL ie liste non vide
    if ( (*L)->suite == NULL )
        depile(L) ;   // moralement : depile(& (*L)) ;
    else VD (& (*L)->suite) ;
}

void VireDernier_rec (Liste *L)
{
    if ( *L != NULL )
          VD(L);        // moralement : VD(& (*L)) ;
}

/*************/

void VireDernier_iter (Liste *L) {
    if ( *L != NULL) {
        while ( (*L)->suite != NULL )
                 L = &  (*L)->suite  ;
        free(*L) ;
        *L = NULL ;
    }
}


/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L) {
    if ( *L != NULL ) {
        depile(L);
        VideListe(L);
    }
}

/********************************************/
/*                                          */
/*          DeuxEgalX                       */
/*                                          */
/********************************************/

bool DeuxEgalX (Liste L, int x) {
    if ((L == NULL) || (L->suite == NULL)) return (x == 0);
    else return (L->suite->valeur == x);
}


/********************************************/
/*                                          */
/*          ContientZero                    */
/*                                          */
/********************************************/

bool ContientZero (Liste L) {
    if (L == NULL) return false;
    if (L->valeur == 0) return true;
    else return ContientZero(L->suite);
}

bool ContientZero_iter (Liste L) {
    while (L != NULL) {
        if (L->valeur == 0) return true;
        L = L->suite;
    }
    return false;
}


/********************************************/
/*                                          */
/*          SousEnsemble                    */
/*                                          */
/********************************************/

bool SousEnsemble(Liste L1, Liste L2) {
    if (L1 == NULL) return true;
    if (L2 == NULL) return false;

    while (L1 != NULL && L2 != NULL) {
        if (L1->valeur == L2->valeur) {
            L1 = L1->suite;
            L2 = L2->suite;
        }
        else if (L1->valeur < L2->valeur) return false;
        else L2 = L2->suite;
    }

    return (L1 == NULL);
}

bool SousEnsembleRec(Liste L1, Liste L2) {
    if (L1 == NULL) return true;
    if (L2 == NULL) return false;

    if (L1->valeur == L2->valeur) return SousEnsembleRec(L1->suite, L2->suite);
    else if(L1->valeur > L2->valeur)return SousEnsembleRec(L1, L2->suite);
    return false;
}


/********************************************/
/*                                          */
/*          SommeAvantKieme0                */
/*                                          */
/********************************************/


int SAvK0_rec(int k, Liste l) {
    if (l == NULL || k == 0) return 0;
    else if (l->valeur == 0) return SAvK0_rec(k-1, l->suite);
    else return  l->valeur + SAvK0_rec(k, l->suite);
}

int SAvK0_iter(int k, Liste l) {
    int somme = 0;

    while (l != NULL && k != 0) {
        somme += l->valeur;
        if (l->valeur == 0) k--;
        l = l->suite;
    }

    return somme;
}

int f(int k, Liste l, int s) {
    if (l == NULL || k == 0) return s;
    else if (l->valeur == 0) return f(k-1, l->suite, s);
    else return  f(k, l->suite, l->valeur + s);
}

int SAvK0_rec_f(int k, Liste l) {
    return f(k, l, 0);
}

void p(int k, Liste l, int* s) {
    if (l != NULL && k != 0) {
        if (l->valeur == 0) p(k-1, l->suite, s);
        else {
            *s += l->valeur;
            p(k, l->suite, s);
        }
    }
}

int SAvK0_rec_p(int k, Liste l) {
    int s = 0;
    p(k, l, &s);
    return s;
}


/********************************************/
/*                                          */
/*           SommeApresRetroKieme0          */
/*                                          */
/********************************************/


int aux_SApRK0(int* k, Liste l) {
    if (l == NULL) return 0;
    else {
        int x = aux_SApRK0(k, l->suite);
        if (*k == 0) return x;
        if (l->valeur == 0) {
            (*k)--;
            return x;
        }
        else return x + l->valeur;
    }
}

int SApRK0(int k, Liste l) { // pour ne pas modifier k de l'appelant
    int k_loc = k;
    return aux_SApRK0(&k_loc, l);
}


/********************************************/
/*                                          */
/*          TueDoublons                     */
/*                                          */
/********************************************/


bool EstDans(int x, Liste l) {
    while (l != NULL) {if (x == l->valeur) return true; else l = l->suite;}
    return false;
}

void TueDoublons1(Liste* L) {
    if (*L != NULL) {
        if (EstDans((*L)->valeur, (*L)->suite)) {depile(L); TueDoublons1(L);}
        else TueDoublons1(&(*L)->suite);
    }
}

void aux_TD2(Liste* L, int valeur) { // ça elimine les doublons
    if (*L != NULL) {
        if ((*L)->valeur == valeur) {
            depile(L);
            aux_TD2(L, valeur);
        }
        else aux_TD2(&(*L)->suite, valeur);
    }
}

void TueDoublons2_rec(Liste* L) {
    if (*L != NULL) {
        aux_TD2(&(*L)->suite, (*L)->valeur);
        TueDoublons2_rec(&(*L)->suite);
    }
}

void TueDoublons2_iter(Liste* L) {
    Liste* p = L;

    while (*p != NULL) {
        Liste* q = &(*p)->suite;

        while (*q != NULL) {
            if ((*p)->valeur == (*q)->valeur) depile(q);
            else q = &(*q)->suite;
        }

        p = &(*p)->suite;
    }
}


/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/


int main(int argc, char** argv) {
    printf("------------------------------------------------------\n");
    Liste l = NULL ;
    VireDernier_rec  (&l);
    VireDernier_iter (&l);
    empile(0, &l);
    empile(1, &l);
    empile(1, &l);
    printf("|>  l = "); affiche_rec(l);

    printf("  %-23s %d \n", "Longueur_iter(l) = ", longueur_iter(l));
    printf("  %-23s %d \n", "Longueur_rec(l) = ", longueur_rec(l));
    printf("  %-23s %d \n", "DeuxEgalX(l, 0) = ", DeuxEgalX(l,0));
    printf("  %-23s %d \n", "DeuxEgalX(l, 1) = ", DeuxEgalX(l,1));
    printf("  %-23s %d \n", "ContientZero(l) = ", ContientZero(l));
    printf("  %-23s %d \n", "ContientZero_iter(l) = ", ContientZero_iter(l));

    printf("------------------------------------------------------\n");

    Liste ll = ajoute(1, ajoute(3,ajoute(5, NULL)));
    Liste lll = ajoute(1, ajoute(2, ajoute(3, ajoute(4, ajoute(5, NULL)))));
    printf("|>  l1 = "); affiche_rec(ll);
    printf("|>  l2 = "); affiche_rec(lll);

    printf("  %-20s %d \n", "SousEnsemble(l) = ", SousEnsemble(ll, lll));
    printf("  %-20s %d \n", "SousEnsembleRec(l) = ", SousEnsembleRec(ll, lll));

    printf("------------------------------------------------------\n");

    Liste l1 = ajoute(2, ajoute(3, ajoute(0, ajoute(1, ajoute(0, ajoute(4, ajoute(9, ajoute(0, ajoute(0, ajoute(8, ajoute(2, ajoute(0, NULL))))))))))));
    printf("l = "); affiche_iter(l1);
    int k = 4;
    printf("  %-20s %d \n", "SAvK0_rec(4, l) = ", SAvK0_rec(k, l1));
    printf("  %-20s %d \n", "SAvK0_iter(4, l) = ", SAvK0_iter(k, l1));
    printf("  %-20s %d \n", "SAvK0_rec_f(4, l) = ", SAvK0_rec_f(k, l1));
    printf("  %-20s %d \n", "SAvK0_rec_p(4, l) = ", SAvK0_rec_p(k, l1));
    printf("  %-20s %d \n", "SApRK0(4, l) = ", SApRK0(k, l1));

    printf("------------------------------------------------------\n");

    Liste l2 = ajoute(34, ajoute(56, ajoute(34, ajoute(23, ajoute(12, ajoute(34, ajoute(23, NULL)))))));
    Liste l3 = ajoute(34, ajoute(56, ajoute(34, ajoute(23, ajoute(12, ajoute(34, ajoute(23, NULL)))))));
    Liste l4 = ajoute(34, ajoute(56, ajoute(34, ajoute(23, ajoute(12, ajoute(34, ajoute(23, NULL)))))));
    printf("l = "); affiche_iter(l2);

    TueDoublons1(&l2);
    TueDoublons2_rec(&l3);
    TueDoublons2_iter(&l4);
    printf("  %-25s ", "TueDoublons1(l) = "); affiche_iter(l2);
    printf("  %-25s ", "TueDoublons2_rec(l) = "); affiche_iter(l3);
    printf("  %-25s ", "TueDoublons2_iter(l) = "); affiche_iter(l4);

    printf("------------------------------------------------------\n");

    VideListe(&l);
    VideListe(&l1);
    VideListe(&l2);
    VideListe(&l3);
    VideListe(&l4);
    VideListe(&ll);
    VideListe(&lll);
    return 0;
}




