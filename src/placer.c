#include <gtk/gtk.h>

#include "../header/supprimerBouton.h"
#include "../header/choisirDir.h"
#include "../header/mettreBateau.h"
#include "../header/modifgrilleCopie.h"
#include "../header/afficherPlateau.h"
#include "../header/message.h"

extern unsigned int top,left;
extern int direction,joueur,numJoueur,nbPoste;
int bateauplace=0;

/**< Place le bateau en definissant la colonne et la ligne la longueur du bateau et sa longueur.
A chaque placement demande et verifie la validité de la direction. Si valide on place sinon on redemande de placer le meme bateau. */

void placer(int plateau[11][11], char* navires[5], int longueur[6],int i)
{
    int colonne, ligne, j, possible;

    ligne=top;
    colonne=left;

    if(nbPoste==2&&numJoueur==joueur)
    {
        choisirDir();
    }
    else if(nbPoste==1)
    {
        choisirDir();
    }

    if(plateau[ligne][colonne] == 0)
    {
        for(j = 1; j < longueur[i]; j++)
        {
            possible = 0;
            if(direction == 1)
            {
                if (j == 1)
                {
                    for(int n = 1; n < longueur[i]; n++)
                    {
                        if(plateau[ligne - n][colonne] != 0)
                        {
                            possible = 1;
                        }
                    }
                }
                if(possible == 0)
                {
                    for(int k=0; k<longueur[i]; k++)
                    {
                        supprimerBouton(colonne,ligne-k);
                        modifgrilleCopie(colonne,ligne-k,joueur);
                        mettreBateau(colonne,ligne-k,k,direction,joueur,i);

                    }
                    plateau[ligne][colonne] = i+1;
                    plateau[ligne - j][colonne] = i+1;
                    if(j == longueur[i] - 1)
                    {
                        i++;
                    }
                }
                else
                {
                    printf("\nCette direction n'est pas possible.\n\n");
                    message("Cette direction n'est pas possible.");
                    direction=-1;
                    j = longueur[i];
                    bateauplace--;
                }
            }
            else if(direction == 2)
            {
                if(j == 1)
                {
                    for(int n = 1; n < longueur[i]; n++)
                    {
                        if(plateau[ligne + n][colonne] != 0)
                        {
                            possible = 1;

                        }
                    }
                }
                if(possible == 0)
                {
                    for(int k=0; k<longueur[i]; k++)
                    {
                        supprimerBouton(colonne,ligne+k);
                        modifgrilleCopie(colonne,ligne+k,joueur);
                        mettreBateau(colonne,ligne+k,k,direction,joueur,i);

                    }

                    plateau[ligne][colonne] = i+1;
                    plateau[ligne + j][colonne] = i+1;
                    if(j == longueur[i] - 1)
                    {
                        i++;
                    }
                }
                else
                {
                    printf("\nCette direction n'est pas possible.\n\n");
                    message("Cette direction n'est pas possible.");
                    direction=-1;
                    j = longueur[i];
                    bateauplace--;
                }
            }
            else if(direction == 3)
            {
                if(j == 1)
                {
                    for(int n = 1; n < longueur[i]; n++)
                    {
                        if(plateau[ligne][colonne - n] != 0)
                        {
                            possible = 1;
                        }
                    }
                }
                if(possible == 0)
                {
                    for(int k=0; k<longueur[i]; k++)
                    {
                        supprimerBouton(colonne-k,ligne);
                        modifgrilleCopie(colonne-k,ligne,joueur);
                        mettreBateau(colonne-k,ligne,k,direction,joueur,i);

                    }
                    plateau[ligne][colonne] = i+1;
                    plateau[ligne][colonne - j] = i+1;
                    if(j == longueur[i] - 1)
                    {
                        i++;
                    }
                }
                else
                {
                    printf("\nCette direction n'est pas possible.\n\n");
                    message("Cette direction n'est pas possible.");
                    direction=-1;
                    j = longueur[i];
                    bateauplace--;
                }
            }
            else if(direction == 4)
            {
                if(j == 1)
                {
                    for(int n = 1; n < longueur[i]; n++)
                    {

                        if(plateau[ligne][colonne + n] != 0)
                        {
                            possible = 1;

                        }

                    }
                }
                if(possible == 0)
                {
                    for(int k=0; k<longueur[i]; k++)
                    {
                        supprimerBouton(colonne+k,ligne);
                        modifgrilleCopie(colonne+k,ligne,joueur);
                        mettreBateau(colonne+k,ligne,k,direction,joueur,i);
                    }
                    plateau[ligne][colonne] = i+1;
                    plateau[ligne][colonne + j] = i+1;
                    if(j == longueur[i] - 1)
                    {
                        i++;

                    }


                }
                else
                {
                    printf("\nCette direction n'est pas possible.\n\n");
                    message("Cette direction n'est pas possible.");
                    direction=-1;
                    j = longueur[i];
                    bateauplace--;

                }
            }
        }
        bateauplace++;
        if(nbPoste!=2)
        {
            if(bateauplace<5)
            {
                message(g_strdup_printf("Veuillez placer le %s",navires[bateauplace]));
            }
        }
        else
        {
            if(bateauplace<5&&numJoueur==joueur)
            {
                message(g_strdup_printf("Veuillez placer le %s",navires[bateauplace]));
            }
        }

        afficherPlateau(plateau);

    }
}

