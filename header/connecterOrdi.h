#ifndef CONNECTERORDI_H_INCLUDED
#define CONNECTERORDI_H_INCLUDED

void fermer();

void creerServ();
void creerClient();

void host();
void guest();

void afficherMsg();

char* recevoirCo();
void envoyerCo(char MessageEnvoi[3]);

void connecterOrdi();
#endif // CONNECTERORDI_H_INCLUDED
