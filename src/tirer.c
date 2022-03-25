#include <stdio.h>

#include "../header/afficherTir.h"
#include "../header/resultatTir.h"
#include "../header/afficherPlateau.h"
#include "../header/supprimerBouton.h"

extern int t1, t2, joueur;
extern unsigned left,top;
int touche;

/**< Fonction tir: regarde le plateau et si y a quelque chose au coord du tir alors touche sinon plouf */

void tirer(int plateau[11][11], int plateau2[11][11], int plateau3[11][11], int plateau4[11][11])
{
    int colonne, ligne;
    printf("Au joueur %d ! Tirez : \n", joueur);
    if(joueur == 1)
    {
        afficherPlateau(plateau3);
    }
    else
    {
        afficherPlateau(plateau4);
    }


    ligne=top;
    colonne=left;
    supprimerBouton(colonne,ligne);

    if(joueur == 1)
    {
        if(plateau2[ligne][colonne] != 0)
        {
            plateau3[ligne][colonne] = 1;
            t1++;
            touche=1;
            afficherPlateau(plateau3);
            afficherTir(ligne,colonne,1);
            printf("Touche !\n\n");
        }
        else
        {
            touche=0;
            plateau3[ligne][colonne] = 2;
            afficherTir(ligne,colonne,0);
            afficherPlateau(plateau3);
            printf("Loupe !\n\n");
        }
    }
    else
    {
        if(plateau4[ligne][colonne] != 0)
        {
            printf("Veuillez tirer dans une case vide.\n\n");
            joueur --;
            return;
        }
        if(plateau[ligne][colonne] != 0)
        {
            plateau4[ligne][colonne] = 1;
            t2++;
            touche=1;
            afficherPlateau(plateau4);
            printf("Touche !\n\n");
            afficherTir(ligne,colonne,1);
        }
        else
        {
            touche=0;
            plateau4[ligne][colonne] = 2;
            afficherPlateau(plateau4);
            afficherTir(ligne,colonne,0);
            printf("Loupe !\n\n");
        }
    }

}
