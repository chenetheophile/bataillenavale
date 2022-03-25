#include <windows.h>
#include <stdio.h>

/**< Placement des bateau de l'ia dans sa grilles de bateau */

void placementIA(int plateau[11][11], char* navires[5], int longueur[6])
{
    int colonne, ligne, i = 0;
    int direction;
    while(i < 5)
    {
        int directions[4] = {1,2,3,4};
        ligne = (rand()%10) + 1;
        colonne = (rand()% 10) + 1;
        while(colonne < 1 || ligne < 1)
        {
            ligne = (rand()%10) + 1;
            colonne = (rand()% 10) + 1;
        }
        if(plateau[ligne][colonne] == 0)
        {
            for(int n = 1; n < longueur[i]; n++)
            {
                if(plateau[ligne - n][colonne] != 0 || ligne < longueur[i])
                {
                    directions[0] = 0;
                }
                if(plateau[ligne + n][colonne] != 0 || ligne > 11 - longueur[i])
                {
                    directions[1] = 0;
                }
                if(plateau[ligne][colonne - n] != 0 || colonne < longueur[i])
                {
                    directions[2] = 0;
                }
                if(plateau[ligne][colonne + n] != 0 || colonne > 11 - longueur[i])
                {
                    directions[3] = 0;
                }
            }
            if(directions[0] != 0 || directions[1] != 0 || directions[2] != 0 || directions[3] != 0)
            {
                direction = directions[rand()%4];
                while(direction == 0)
                {
                    direction = directions[rand()%4];
                }
                plateau[ligne][colonne] = i + 1;
                for(int j = 0; j < longueur[i]; j++)
                {
                    if(direction == 1)
                    {
                        plateau[ligne - j][colonne] = i+1;
                        if(j == longueur[i] - 1)
                        {
                            i++;
                        }
                    }
                    else if(direction == 2)
                    {
                        plateau[ligne + j][colonne] = i+1;
                        if(j == longueur[i] - 1)
                        {
                            i++;
                        }
                    }
                    else if(direction == 3)
                    {
                        plateau[ligne][colonne - j] = i+1;
                        if(j == longueur[i] - 1)
                        {
                            i++;
                        }
                    }
                    else if(direction == 4)
                    {
                        plateau[ligne][colonne + j] = i+1;
                        if(j == longueur[i] - 1)
                        {
                            i++;
                        }
                    }
                }
            }
        }
    }
    for(int i=0; i<10; i++)
    {
        printf("\n");
    }
    printf("L'IA a placé ses navires.\n\n");
}
