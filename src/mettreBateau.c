#include <gtk/gtk.h>

extern GtkWidget*copieJ1Bateau,*copieJ2Bateau;
extern int width,height,ModeDeJeu;

/**< Mettre bateau sert a afficher les bateau dans la grille copié (inerte) Change la rotation de l'image pour savoir la direction d'origine*/

void mettreBateau(int ligne,int colonne,int k,int direction,int joueur,int bateau)
{
    char*listefichier[5]= {"photo/porteavion%d.png", "photo/croiseur%d.png", "photo/contretorpilleur%d.png", "photo/sousmarin%d.png", "photo/torpilleur%d.png"};
    GtkWidget*image=gtk_image_new();
    GdkPixbuf*pix;

    char*nomfichier=g_strdup_printf(listefichier[bateau],k+1);
    gtk_image_set_from_file(GTK_IMAGE(image),nomfichier);

    if(direction==1)
    {

        pix=gdk_pixbuf_rotate_simple(gtk_image_get_pixbuf(GTK_IMAGE(image)),GDK_PIXBUF_ROTATE_COUNTERCLOCKWISE);
        pix=gdk_pixbuf_scale_simple(GDK_PIXBUF(pix),(int)width/22,(int)height/22,GDK_INTERP_BILINEAR);
        image=gtk_image_new_from_pixbuf(GDK_PIXBUF(pix));
    }
    else if(direction==2)
    {
        pix=gdk_pixbuf_rotate_simple(gtk_image_get_pixbuf(GTK_IMAGE(image)),GDK_PIXBUF_ROTATE_CLOCKWISE);
        pix=gdk_pixbuf_flip(GDK_PIXBUF(pix),TRUE);
        pix=gdk_pixbuf_scale_simple(GDK_PIXBUF(pix),(int)width/22,(int)height/22,GDK_INTERP_BILINEAR);
        image=gtk_image_new_from_pixbuf(GDK_PIXBUF(pix));
    }
    else if(direction==3)
    {
        pix=gdk_pixbuf_rotate_simple(gtk_image_get_pixbuf(GTK_IMAGE(image)),GDK_PIXBUF_ROTATE_UPSIDEDOWN);
        pix=gdk_pixbuf_flip(GDK_PIXBUF(pix),FALSE);
        pix=gdk_pixbuf_scale_simple(GDK_PIXBUF(pix),(int)width/22,(int)height/22,GDK_INTERP_BILINEAR);
        image=gtk_image_new_from_pixbuf(GDK_PIXBUF(pix));
    }
    else
    {
        pix=gdk_pixbuf_scale_simple(gtk_image_get_pixbuf(GTK_IMAGE(image)),(int)width/22,(int)height/22,GDK_INTERP_BILINEAR);
        image=gtk_image_new_from_pixbuf(GDK_PIXBUF(pix));
    }
    if(joueur==1)
    {
        if(gtk_grid_get_child_at(GTK_GRID(copieJ1Bateau),ligne, colonne)==NULL)
        {
            gtk_grid_attach(GTK_GRID(copieJ1Bateau),image,ligne,colonne,1,1);
        }
    }
    else if(joueur==2)
    {
        if(gtk_grid_get_child_at(GTK_GRID(copieJ2Bateau),ligne,colonne)==NULL)
        {
            gtk_grid_attach(GTK_GRID(copieJ2Bateau),image,ligne,colonne,1,1);
        }
    }
}
