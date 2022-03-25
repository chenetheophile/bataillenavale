#include <gtk/gtk.h>
#include <winsock2.h>

#include "../header/Jouer.h"

/**< Ces focntions et variables ne servent qu'au cas ou les joueurs jouent en réseau local */

SOCKADDR_IN serveur_adresse;
SOCKADDR_IN client_adresse;

SOCKET serveur_socket;
SOCKET client_socket;


GtkWidget*connexion=NULL;
GtkWidget *gridFenetre;

int reponse=-1,id=0,id2=0,numJoueur,isSuppr=0;;

extern int width,height,phaseDeJeu;


/**< fermer la fenetre de demande de connexion et arrete les boucles issues de g_timeout_add */
void fermer()
{
    if(isSuppr!=1)
    {
        if(id!=0)
        {
            g_source_remove(id);
        }
        if(id2!=0)
        {
            g_source_remove(id2);
        }
        isSuppr=1;
        gtk_widget_destroy(connexion);
        phaseDeJeu++;
        Jouer();
    }
}


/**< CreerServ et CreerClient servent a connecter 1 fois les instances de l'app pour etre sur que les deux joueurs sont
bien connecter entre eux */
void creerServ()
{

    WSADATA data;
    WSAStartup(MAKEWORD(2,2),&data);

    // Cr?ation d'un socket pour notre serveur
    serveur_socket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);

    serveur_adresse.sin_family = AF_INET; // Type d'adresse
    serveur_adresse.sin_port = htons (2712); // Num?ro du port ? l'?coute : 2712
    serveur_adresse.sin_addr.s_addr = INADDR_ANY; // Adresse automatique du serveur
    memset (serveur_adresse.sin_zero, 0, 8); // Mise ? zero des 8 derniers octets de la structure

    // Ligature du socket et de l'adresse
    bind (serveur_socket, (SOCKADDR*)&serveur_adresse, sizeof (serveur_adresse));

    // Mise a l'ecoute du serveur
    listen (serveur_socket, 5);


    // On memorise la taille de l'adresse dans un variable
    int taille_client_adresse = sizeof (client_adresse);

    // On accepte une demande de connexion
    if((client_socket = accept (serveur_socket, (SOCKADDR*)&client_adresse, &taille_client_adresse)))
    {
        printf("Connexion au serveur reussi");
        WSACleanup();
        fermer();

    }

}

void creerClient()
{
    WSADATA data;
    WSAStartup(MAKEWORD(2,2),&data);
    // On cree un socket pour notre client
    client_socket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // On defini l'adresse IP et le port du serveur
    serveur_adresse.sin_family = AF_INET;
    serveur_adresse.sin_port = htons (2712);
    serveur_adresse.sin_addr.s_addr = inet_addr ("127.0.0.1");
    memset (serveur_adresse.sin_zero, 0, 8);

    // On fait une demande de connexion aupres du serveur

    if (connect (client_socket, (SOCKADDR*)&serveur_adresse, sizeof(serveur_adresse)) == -1)
    {
        // La tentative de connexion a echoue

        printf ("Connexion echoue !\n");
    }
    else
    {
        // La connexion a bien eu lieu, on peu continuer

        printf ("Connexion reussie !\n");
        WSACleanup();
        fermer();
    }

}

/**< Host et guest servent a dire qu'elle est le joueur qui sera meneur et qui sera le suiveur.
D'autre part elle servent a etre sur que les deux joueur joue vraiment ensemble*/
void host()
{
    numJoueur=1;
    id=g_timeout_add(1000,G_SOURCE_FUNC(creerServ),0);
}
void guest()
{
    numJoueur=2;
    id2=g_timeout_add(1000,G_SOURCE_FUNC(creerClient),0);
}

/**< Affiche un message à deux lignes donc pas possible d'utiliser la fct message */
void afficherMsg()
{

    gtk_widget_destroy(gtk_grid_get_child_at(GTK_GRID(gridFenetre),0,0));
    gtk_widget_destroy(gtk_grid_get_child_at(GTK_GRID(gridFenetre),2,0));

    GtkWidget*Init=gtk_label_new("Initialisation de la connexion");

    GtkWidget*Attente=gtk_label_new("Attente de connexion");

    gtk_grid_attach(GTK_GRID(gridFenetre),Init,1,0,1,1);
    gtk_grid_attach(GTK_GRID(gridFenetre),Attente,1,1,1,1);

    gtk_widget_show_all(gridFenetre);
}

/**< Recevoir co et Envoyer Co sont les fonctions qui nous permettent d'envoyer des données entre les 2 instances de l'app
Le message envoyer est un int qu'on convertit en str qu'on envoi puis qu'on recupere dans l'autre instance
 */
char recevoirCo()
{
    WSADATA data;
    int OptVal=1;

    printf("startup=%d",WSAStartup(MAKEWORD(2,2),&data));
    char ContenueMsg[3];
    int TailleContenueMsg = 3;

    SOCKET Destination;
    SOCKADDR_IN AddrDestination;


    SOCKADDR_IN Expediteur;
    int ExpediteurAddr = sizeof (Expediteur);

    Destination = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if(setsockopt(Destination,SOL_SOCKET,SO_REUSEADDR,(char *)&OptVal,sizeof(OptVal))==SOCKET_ERROR)
    {
        wprintf(L"socket failed with error %d\n", WSAGetLastError());
    }

    if (Destination == INVALID_SOCKET)
    {
        wprintf(L"socket failed with error %d\n", WSAGetLastError());
    }

    AddrDestination.sin_family = AF_INET;
    AddrDestination.sin_port = htons (27015);
    AddrDestination.sin_addr.s_addr = htonl(INADDR_ANY);


    if (bind(Destination, (SOCKADDR *) & AddrDestination, sizeof (AddrDestination)) != 0)
    {
        wprintf(L"bind failed with error %d\n", WSAGetLastError());
    }


    if (recvfrom(Destination,ContenueMsg, TailleContenueMsg, 0, (SOCKADDR *) & Expediteur, &ExpediteurAddr) == SOCKET_ERROR)
    {
        wprintf(L"recvfrom failed with error %d\n", WSAGetLastError());
    }


    if (closesocket(Destination) == SOCKET_ERROR)
    {
        wprintf(L"closesocket failed with error %d\n", WSAGetLastError());
    }
    printf("Cleanup=%d",WSACleanup());
    return *ContenueMsg;
}

void envoyerCo(char MessageEnvoi[3])
{
    WSADATA data;
    printf("startup=%d",WSAStartup(MAKEWORD(2,2),&data));

    SOCKET Expediteur = INVALID_SOCKET;
    SOCKADDR_IN AddrDest;

    int TailleMessage = 3;

    Expediteur = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (Expediteur == INVALID_SOCKET)
    {
        wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
    }

    AddrDest.sin_family = AF_INET;
    AddrDest.sin_port = htons(27015);
    AddrDest.sin_addr.s_addr = inet_addr("127.0.0.1");


    wprintf(L"Message Envoye...\n");

    if (sendto(Expediteur,MessageEnvoi, TailleMessage, 0, (SOCKADDR *) & AddrDest, sizeof (AddrDest)) == SOCKET_ERROR)
    {

        wprintf(L"sendto failed with error: %d\n", WSAGetLastError());
        closesocket(Expediteur);
    }

    wprintf(L"Fermeture du socket.\n");

    if (closesocket(Expediteur) == SOCKET_ERROR)
    {

        wprintf(L"closesocket failed with error: %d\n", WSAGetLastError());
    }
    printf("Cleanup=%d",WSACleanup());

}
/**< Afficher le popup qui permet de decider qui crée ou qui rejoins le jeu. */
void connecterOrdi()
{

    GtkWidget *creerpartie;
    GtkWidget *rejoindre;
    GtkWidget *Annuler;



    int hauteurbouton=50,largeurbouton=100;


    gridFenetre=gtk_grid_new();

    for(int i=0; i<3; i++)
    {
        gtk_grid_insert_column(GTK_GRID(gridFenetre),0);
        gtk_grid_insert_row(GTK_GRID(gridFenetre),0);
    }
    gtk_grid_set_row_spacing(GTK_GRID(gridFenetre),20);
    gtk_grid_set_column_spacing(GTK_GRID(gridFenetre),20);

    connexion=gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"N");

    gtk_widget_destroy(gtk_bin_get_child(GTK_BIN(connexion)));

    gtk_window_resize(GTK_WINDOW(connexion),500,500);

    creerpartie=gtk_button_new_with_label("creer");
    gtk_widget_set_size_request(creerpartie,largeurbouton,hauteurbouton);
    g_signal_connect(creerpartie,"clicked",host,NULL);
    g_signal_connect(creerpartie,"clicked",afficherMsg,NULL);


    rejoindre=gtk_button_new_with_label("rejoindre");
    gtk_widget_set_size_request(rejoindre,largeurbouton,hauteurbouton);
    g_signal_connect(rejoindre,"clicked",guest,NULL);
    g_signal_connect(rejoindre,"clicked",afficherMsg,NULL);


    Annuler=gtk_button_new_with_label("Annuler");
    gtk_widget_set_size_request(Annuler,largeurbouton,hauteurbouton);
    g_signal_connect(Annuler,"clicked",fermer,NULL);

    gtk_grid_attach(GTK_GRID(gridFenetre),creerpartie,0,0,1,1);
    gtk_grid_attach(GTK_GRID(gridFenetre),rejoindre,2,0,1,1);
    gtk_grid_attach(GTK_GRID(gridFenetre),Annuler,1,2,1,1);

    gtk_container_add(GTK_CONTAINER(connexion),gridFenetre);
    gtk_window_move(GTK_WINDOW(connexion),(int)width/2-width/14,(int)height/2-height/14);
    gtk_widget_show_all(connexion);

}
