
/**< creer les plateaux sur lesquels se basent le jeu */

void creerPlateau(int plateau[11][11])
{
    int i, j;
    for(i=0; i < 11; i++)
    {
        plateau[0][i] = i;
        plateau[i][0] = i;
        for(j=1; j < 11; j++)
        {
            if(i>0)
            {
                plateau[i][j] = 0;
            }
        }
    }
}
