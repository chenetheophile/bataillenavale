#include <stdlib.h>
#include <stdio.h>

/**< Cette fonction sert à afficher le plateau passé en argument dans la console */
void afficherPlateau(int plateau[11][11])
{
    int a, b;
    for(a=0; a < 11; a++)
    {
        for(b = 0; b < 11; b++)
        {
            if(b > 0)
            {
                printf("%4d", plateau[a][b]);
            }
            else
            {
                printf("%4d", plateau[a][b]);
                printf("  ");
            }
        }
        if(a == 0)
        {
            printf("\n");
        }
        printf("\n");
    }
    printf("\n");
}
