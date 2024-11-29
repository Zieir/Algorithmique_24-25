/******************************** RENDU PARTIE2.2-LZ  *********************************/
/**                                                                                  **/
/**   1. MEDJADJ Mohamed Abderraouf:   mohamed-abderraouf.medjadj@etu-upsaclay.fr    **/
/**                                                                                  **/
/**   2. KERMADJ Zineddine:   zineddine.kermadj@etu-upsaclay.fr                      **/
/**                                                                                  **/
/**************************************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct Bloc {
    int valeur;
    struct Bloc* next;
    struct Bloc** prec;
} Bloc;

typedef Bloc*** ListeZ;


void initVideZ(ListeZ *listeZ)
{
    *listeZ = NULL;
}

bool estVide(ListeZ listeZ)
{
    return listeZ == NULL;
}
void afficherListeZ(ListeZ listeZ) {
    if (estVide(listeZ)) {
        printf("La liste est  vide.\n");
        return;
    }

    Bloc* start = **listeZ; // Récupérer le premier bloc de la liste circulaire
    Bloc* current = start;

    printf("Liste circulaire :\n");
    do {
        printf("Bloc -> valeur: %d, next: %p, prec: %p\n", current->valeur, current->next, current->prec);
        current = current->next;
    } while (current != start);
}


int premierZ(ListeZ access)
{
    return (***access).valeur;
}


Bloc *ajoute(int x, ListeZ access)
{

    Bloc *tmp = (Bloc *)malloc(sizeof(Bloc));
    tmp->valeur = x;
    if (access == NULL)
    {
        tmp->next = tmp;
        tmp->prec = &(tmp->next);
    }
    else
    {
        tmp->next = **access;
        tmp->prec = *access;
        **access = tmp;
        *access = &(tmp->next);
    }
    return tmp;
}

void ZAjouteAvant(int x, ListeZ *access)
{

    *access = &(ajoute(x, *access)->prec);
}

void ZElimine(ListeZ* access){
    if((estVide(*access))){return;}
    if((***access)->next == (***access)){
        (*access) = NULL;
        return;
    }

    ((****access).next)->prec = (****access).prec;
    ((***access)) =  (****access).next;
    access = &((****access).prec);

}


int main() {

    ListeZ access;
    initVideZ(&access);
    ZAjouteAvant(42, &access);
    ZAjouteAvant(93, &access);
    ZAjouteAvant(17, &access);
    ZAjouteAvant(23, &access);

    afficherListeZ(access);

    ZElimine(&access);
    afficherListeZ(access);
    ZElimine(&access);
    afficherListeZ(access);
    ZElimine(&access);
    afficherListeZ(access);
    ZElimine(&access);
    afficherListeZ(access);
    ZElimine(&access);
    afficherListeZ(access);


    return 0;
}
