/*
 * Soluzione ricorsiva in C, a beneficio solo di chi conosce la
 * ricorsione (non e' argomento del corso)
 *
 */

#include <stdio.h>

int e = 5, d = 173, r = 323; // Chiave cifratura/decifratura

int potenza_modulo(int N, int e)
{
    if (e == 0)
       return 1;
    return (N * potenza_modulo(N, e - 1)) % r ;
}

int cifra(int N, int e)
{
    if (N <= 0 || N >= r) {
       printf("Errore: il numero da criptare "
             "e' fuori dall'intervallo consentito\n") ;
       exit(1) ;
    }
    return potenza_modulo(N, e);
}

int main()
{
  while (1) {
    int scelta ;
    
    printf("\tChiave attualmente in uso: (%d, %d, %d)\n", e, d, r) ;
    printf("\n\t1 Cambiamento chiave RSA\n");
    printf("\t2 Cifratura di un numero\n");
    printf("\t3 Decifratura di un numero\n");
    printf("\t4 Uscita\n");
    printf("Scelta ");
    scanf("%d", &scelta);
    
    switch(scelta) {
      
      int N;
      
    case 1:
      printf("Inserisci e ");
      scanf("%d", &e);
      printf("Inserisci d ");
      scanf("%d", &d);
      printf("Inserisci r ");
      scanf("%d", &r);
      break;
    case 2:
      printf("Inserisci il numero da cifrare ");
      scanf("%d", &N);
      printf("Il numero cifrato e' %d\n\n", cifra(N, e));
                 break;
    case 3:
      printf("Inserisci il numero da decifrare ");
      scanf("%d", &N);
      printf("Il numero decifrato e' %d\n\n", cifra(N, d)) ;
      break;
    case 4:
      return 0;
    default:
      printf("Scelta non valida\n");
    }
  }
  
  return 0;
}
