#include <gtk/gtk.h>
#include "../header/fermeFenetre.h"
#include "../header/faireMenu.h"

extern GtkWidget *Option;
/**<
Cette fonction n'est appelée que lorsque on retourne au menu depuis options.
 */
void afficherMenu()
{
    faireMenu();
    g_timeout_add_seconds(0.1,G_SOURCE_FUNC(fermeFenetre),GTK_WIDGET(Option));//affiche le menu depuis le widget et supprime l ancienne fenetre

}
