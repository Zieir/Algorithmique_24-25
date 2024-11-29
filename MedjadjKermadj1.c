/*****************************{      RENDU PARTIE1      }******************************/
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
/*                type booléen                   */
/*                                               */
/*************************************************/

typedef enum {false, true} bool;

/*************************************************/
/*                                               */
/*                    pow                        */
/*                                               */
/*************************************************/

long long power (int n, int k) {
    long long pow = 1;

    for (int i = 0; i < k; i++) pow *= n;

    return pow;
}

/*************************************************/
/*                                               */
/*                factorielle                    */
/*                                               */
/*************************************************/

long long fact (int n) {
    if (n==0) return 1;
    else return n * fact(n-1);
}

/*************************************************/

// itou avec un argument out => passage par adresse

void bisfact(int n, long long * r) {
    if (n==0) *r = 1.0;
    else {
        bisfact(n-1,r);
        *r = *r *n;
    }
}

long long fact2 (int n) {
    long long r;
    bisfact(n,&r);
    return r;
}

/*************************************************/

// itou en stoquant tout dans un tableau... (très bof en complexité espace)

long long fact3(int n) {
    long long * T = (long long *) malloc((n+1)*sizeof(long long));
    T[0] = 1;
    for (int i=1 ; i <= n ; i++) T[i] = i* T[i-1];
    long long r = T[n];
    free(T);
    return r;
}


/*************************************************/
/*                                               */
/*                  Calcul de e                  */
/*                                               */
/*************************************************/

  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995
  //       9574966967 6277240766 3035354759 4571382178 5251664274
  // il est bien sûr interdit d'injecter directement cette approximation

float Efloat ()
{
    float e = 1.0;  // Initialiser avec le premier terme (1/0!)
    int n = 1;


    for (float terme = 1.0; terme > 1e-15; n++) {
        terme /= n;

        e += terme;  // Ajouter le terme � la somme
    }
    return e;
}

/*************************************************/

double Edouble ()
{
    double e = 1.0;  // Initialiser avec le premier terme (1/0!)
    int n = 1;

    for (double terme = 1.0; terme > 1e-30; n++) {
        terme /= n;

        e += terme;  // Ajouter le terme � la somme
    }
    return e;
}

/*************************************************/
/*                                               */
/*            Suite Y                            */
/*                                               */
/*************************************************/

void afficheYfloat (int n){
    float result = Efloat() - 1;
    for(int i=1;i<n;i++){
        result = i*result - 1;
        printf("Y(%d)=%f\n",i, result);
    }
}

/*************************************************/

void afficheYdouble (int n){
    double result = Edouble() - 1;
    for(int i=1;i<n;i++){
        result = i*result - 1;
        printf("Y(%d)=%f\n",i, result);
    }
}


/*************************************************/
/*                                               */
/*                       X                       */
/*                                               */
/*************************************************/

double X1(int n) {
    double x = 1.0;

    for (int i = 1; i <= n; i++) x = x + (1 / x);

    return x;
}

long double X1_recoded(long long n) {
    long double x = 1.0;

    for (int i = 1; i <= n; i++) x = x + (1 / x);

    return x;
}

double X2(int n) {
    if (n == 0) return 1.0;
    else {
        double x = X2(n-1);
        return x + (1 / x);
    }
}

static double aux_X3(int n, double x) {
    if (n == 0) return x;
    else return aux_X3(n-1, x + (1 / x));
}

double X3(int n) {
    return aux_X3(n, 1.0);
}

static void aux_X4(int n, double* x) {
    if (n != 0) {
        *x = *x + (1 / *x);
        aux_X4(n-1, x);
    }
}

double X4(int n) {
    double x = 1.0;
    aux_X4(n, &x);
    return x;
}

/*************************************************/
/*                                               */
/*                  Binomiaux                    */
/*                                               */
/*************************************************/

long long BadCpn (int p, int n) { // 0 <= p <= n
    if (p == 0 || n == p) return 1;
    else return BadCpn(p, n-1) + BadCpn(p-1, n-1);
}

/*************************************************/

long long aux_Cpn(int p, int n, long long** table) {
    if (p == 0 || n == p) return 1;
    if (table[n][p] != 0) return table[n][p];
    else {
        table[n][p] = aux_Cpn(p, n-1, table) + aux_Cpn(p-1, n-1, table);
        return table[n][p];
    }
}

static long long GoodCpn (int p, int n) { // 0 <= p <= n
    long long** table = (long long**)malloc((n + 1) * sizeof(long long*));
    for (int i = 0; i <= n; i++) {
        table[i] = (long long*)calloc((p + 1), sizeof(long long)); // Initialize to 0
    }
    long long resultat = aux_Cpn(p, n, table);

    for (int i = 0; i <= n; i++) {
        free(table[i]);
    }
    free(table);

    return resultat;
}

/*************************************************/
/*                                               */
/*                     main                      */
/*                                               */
/*************************************************/


int main(int argc, char** argv) {

    float z1;
    double z2;
    long double z3;
    int cpt;

/************************************************************************/

      // mettre "if true" vs "if false" selon que vous voulez les tests ou pas

/************************  taille des nombres  *************************/

if (true) {
    printf("====================================================================\n");

    printf("tailles des entiers (peuvent varier selon le compilo) :\n") ;

    printf("short : %d octets\n", (int) sizeof(short));
    printf("int : %d octets\n", (int) sizeof(int));
    printf("long : %d octets\n", (int) sizeof(long));
    printf("long long : %d octets\n", (int) sizeof(long long));
    printf("float : %d octets\n", (int) sizeof(float));
    printf("double : %d octets\n", (int) sizeof(double));
    printf("long double : %d octets\n", (int) sizeof(long double));
    printf("\n") ;

    printf("limite des flottants (peuvent varier selon le compilo) :\n") ;

    z1 = 2.0 ; cpt = 0 ;
    while ( z1 > 1 ) { z1 = (z1-1)/10+1 ; cpt ++ ; }
    printf("1+1/10^c devient 1 a partir de c=%d pour les float\n", cpt) ;

    z2 = 2.0 ; cpt = 0 ;
    while ( z2 > 1 ) { z2 = (z2-1)/10+1 ; cpt ++ ; }
    printf("1+1/10^c devient 1 a partir de c=%d pour les double\n", cpt) ;

    z3 = 2.0 ; cpt = 0 ;
    while ( z3 > 1 ) { z3 = (z3-1)/10+1 ; cpt ++ ; }
    printf("1+1/10^c devient 1 a partir de c=%d pour les long double\n", cpt) ;

    z1 = 1.0 ; cpt = 0 ;
    while ( z1 > 0 ) { z1 = z1/10 ; cpt ++ ; }
    printf("1/10^c devient 0 a partir de c=%d pour les float\n", cpt) ;

    z2 = 1.0 ; cpt = 0 ;
    while ( z2 > 0 ) { z2 = z2/10 ; cpt ++ ; }
    printf("1/10^c devient 0 a partir de c=%d pour les double\n", cpt) ;

    z3 = 1.0 ; cpt = 0 ;
    while ( z3 > 0 ) { z3 = z3/10 ; cpt ++ ; }
    printf("1/10^c devient 0 a partir de c=%d pour les long double\n", cpt) ;

    printf("\nce programme suppose que les \"long\" font au moins 8 octets\n") ;
    printf("Si ce n'est pas le cas, utiliser des \"long long\" ? \n\n") ;
}

/************************  factorielle  *************************/
    printf("====================================================================\n");

    if (true) {

        printf("factorielles de 0, de 5, de 20, trois codes : \n") ;
        printf("%lld \n",fact(0)) ;
        printf("%lld \n",fact2(0)) ;
        printf("%lld \n",fact3(0)) ;
        printf("%lld \n",fact(5)) ;
        printf("%lld \n",fact2(5)) ;
        printf("%lld \n",fact3(5)) ;
        printf("%lld \n",fact(20)) ;
        printf("%lld \n",fact2(20)) ;
        printf("%lld \n",fact3(20)) ;
        printf("Note : fact(20) est le dernier qui passe correctement avec 8 octets \n") ;
        printf("\n") ;

    }


/******************    Autour de e      *******************************/
    printf("====================================================================\n");

    // d'après google,
    // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995
    //       9574966967 6277240766 3035354759 4571382178 5251664274
    if (true) {

        printf("Valeurs de e en float et en double :\n") ;
        printf(" e1 = %.20f  \n", Efloat() ) ;
        printf(" e2 = %.30lf \n", Edouble() ) ;

    }

    if (true) {

        printf("Valeurs de Y, selon float, double :\n") ;
        afficheYfloat(30) ;
        afficheYdouble(30) ;

    }

/******************    X      *******************************/
    printf("====================================================================\n");
    if (true) {

        printf(" X1(100) = %.30lf \n", X1(100));
        printf(" X2(100) = %.30lf \n", X2(100));
        printf(" X3(100) = %.30lf \n", X3(100));
        printf(" X4(100) = %.30lf \n", X4(100));
        printf("------------------------------------\n");

        long long p;
        for (int i = 1; i <= 9; i++) {
            p = power(10, i);

            printf(" X1(10^%d) = %.30lf \n", i, X1(p));       // seule la version itérative ne cause pas de plantage.
//            printf(" X2(10^%d) = %.30lf \n", i, X2(p));     // le programme plante à X2(10^5).
//            printf(" X3(10^%d) = %.30lf \n", i, X3(p));     // de même pour X3 et X4, donc mon compilateur n'optimise pas le récursif terminal.
//            printf(" X4(10^%d) = %.30lf \n", i, X4(p));
        }
        printf("------------------------------------\n");

        for (int i = 1; i <= 12; i++) {
            p = power(10, i);

//            printf(" X1(10^%d) = %.30Lf \n", i, X1(p));       // X1(10^12) = 1.
        }

    }

/******************    Binomiaux      *******************************/
    printf("====================================================================\n");

    if (true) {

        for (int i = 0; i <= 30; i++) {
//           printf("Cpn[%d, %d] = %lld \n", i, 2*i, BadCpn(i, 2*i));   // temps d'exécution tend vers l'infini (métaphoriquement),
        }                                                               // i.e. complexité exponentielle

        for (int i = 0; i <= 30; i++) {
           printf("Cpn[%d, %d] = %lld \n", i, 2*i, GoodCpn(i, 2*i));
        }
    }

    return 0;
}





