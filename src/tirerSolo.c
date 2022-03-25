#include <windows.h>
#include "../header/tirer.h"
#include "../header/afficherPlateau.h"
#include "../header/afficherTirIA.h"
#include "../header/modifgrilleCopie.h"
extern int t1, t2, joueur, consec, dir, lp, cp, l1, c1, essais,touche;

/**< Tire au coordonnées donné par un random. Si difficulté = 1 Tir a chaque fois au hasard
Si difficulté 2 elle vise autour de la première case mais recommence à viser au hasard si elle loupe
Si difficulté 3 elle vise autour après une touche et vise dans la ligne après 2 touches jusqu'à-ce qu'elle loupe de chaque côté
  */
void tirerSolo(int plateau[11][11], int plateau2[11][11], int plateau3[11][11], int plateau4[11][11],int joueur,int diff)
{
    int colonne, ligne;
    if(joueur!=1)
    {
        if(consec == 0)
        {
            do
            {
                ligne = (rand()%10) + 1;
                colonne = (rand()% 10) + 1;
            }
            while(colonne < 1 || ligne < 1 || plateau4[ligne][colonne] != 0);
            l1 = ligne;
            c1 = colonne;
        }
        else if(consec == 1)
        {
            if(essais == 0)
            {
                if(cp == 1 || plateau4[lp][cp - 1] != 0)
                {
                    essais++;
                }
                if(cp == 10 || plateau4[lp][cp + 1] != 0)
                {
                    essais++;
                }
                if(lp == 1 || plateau4[lp + 1][cp] != 0)
                {
                    essais++;
                }
                if(lp == 10 || plateau4[lp - 1][cp] != 0)
                {
                    essais++;
                }
            }
            if(essais < 4)
            {
                do
                {
                    dir = rand()%4 + 1;
                    if(dir == 1)
                    {
                        ligne = lp - 1;
                        colonne = cp;
                    }
                    else if(dir == 2)
                    {
                        ligne = lp + 1;
                        colonne = cp;
                    }
                    else if(dir == 3)
                    {
                        ligne = lp;
                        colonne = cp - 1;
                    }
                    else if(dir == 4)
                    {
                        ligne = lp;
                        colonne = cp + 1;
                    }
                }
                while(ligne > 10 || ligne < 1 || colonne > 10 || colonne < 1 || plateau4[ligne][colonne] != 0);
            }
            else
            {
                consec = 0;
                do
                {
                    ligne = (rand()%10) + 1;
                    colonne = (rand()% 10) + 1;
                }
                while(colonne < 1 || ligne < 1 || colonne >10 || ligne >10 || plateau4[ligne][colonne] != 0);
            }
        }
        else if(consec > 1)
        {
            if(essais == 0)
            {
                if(dir == 1)
                {
                    ligne = lp - 1;
                    colonne = cp;
                }
                else if(dir == 2)
                {
                    ligne = lp + 1;
                    colonne = cp;
                }
                else if(dir == 3)
                {
                    ligne = lp;
                    colonne = cp - 1;
                }
                else if(dir == 4)
                {
                    ligne = lp;
                    colonne = cp + 1;
                }
                if(ligne > 10 || ligne < 1 || colonne > 10 || colonne < 1 || plateau4[ligne][colonne] != 0)
                {
                    essais++;
                }
            }
            if(essais == 1)
            {
                if(dir%2 == 0)
                {
                    dir--;
                }
                else
                {
                    dir++;
                }
                lp = l1;
                cp = c1;
                if(dir == 1)
                {
                    ligne = lp - 1;
                    colonne = cp;
                }
                else if(dir == 2)
                {
                    ligne = lp + 1;
                    colonne = cp;
                }
                else if(dir == 3)
                {
                    ligne = lp;
                    colonne = cp - 1;
                }
                else if(dir == 4)
                {
                    ligne = lp;
                    colonne = cp + 1;
                }
                if(ligne > 10 || ligne < 1 || colonne > 10 || colonne < 1 || plateau4[ligne][colonne] != 0)
                {
                    consec = 0;
                    do
                    {
                        ligne = (rand()%10) + 1;
                        colonne = (rand()% 10) + 1;
                    }
                    while(colonne < 1 || ligne < 1 || colonne >10 || ligne >10 || plateau4[ligne][colonne] != 0);
                }
            }
        }
    }
    if(joueur == 1)
    {
        tirer(plateau,plateau2,plateau3,plateau4);
    }
    else
    {
        if(plateau[ligne][colonne] != 0)
        {
            plateau4[ligne][colonne] = 1;
            t2++;
            afficherPlateau(plateau4);
            touche=1;
            afficherTirIA(ligne,colonne,1);
            modifgrilleCopie(colonne,ligne,1);
            lp = ligne;
            cp = colonne;
            essais = 0;
            if((diff == 2 && consec < 1) || diff == 3)
            {
                consec++;
            }
        }
        else
        {
            plateau4[ligne][colonne] = 2;
            touche=0;
            afficherTirIA(ligne,colonne,0);
            modifgrilleCopie(colonne,ligne,1);
            afficherPlateau(plateau4);
            if(consec == 1 && essais == 4)
            {
                consec = 0;
            }
            else if(consec > 1)
            {
                if(essais != 0)
                {
                    consec = 0;
                }
                else
                {
                    essais++;
                }
            }
        }
    }
}

