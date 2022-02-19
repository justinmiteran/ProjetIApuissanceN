#include <gtk/gtk.h>


static void activate (GtkApplication *app, gpointer user_data){

  GtkWidget *window;
  GtkWidget* init_box; //box qui va contenir les box qui vont contenir les boutons
  GtkWidget* image;
  gchar* presentation;
  GtkWidget* label;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Jeu : Puissance N");
  gtk_window_set_default_size (GTK_WINDOW (window), 1000, 600);
  init_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
  gtk_window_set_child (GTK_WINDOW (window), init_box);

  presentation = g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#73b5aa\" size=\"xx-large\"> <i> \n Jouez contre notre IA au Puissance N ! </i> \n Choisissez un mode de jeu : \n </span> ", -1, NULL, NULL, NULL);
  label = gtk_label_new(presentation);
  g_free(presentation);
  gtk_label_set_use_markup(GTK_LABEL(label), TRUE); // On dit que l'on utilise les balises pango
  gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
  gtk_box_append(GTK_BOX(init_box), label);

  //MENU
  GMenu *menu_bar;
  GMenu *menu;
  GMenuItem *new;
  GMenuItem *quit;
  GMenu *info;
  GMenuItem *rules;
  GMenuItem *about;

  // barre de menu
  menu_bar = g_menu_new();

  // nom menu
  menu = g_menu_new();
  g_menu_append_submenu(menu_bar, "Paramètres", G_MENU_MODEL(menu));

  // déroulé
  new = g_menu_item_new("Nouvelle partie", NULL);
  g_menu_append_item(menu, new);

  quit = g_menu_item_new("Quitter", NULL);
  g_menu_append_item(menu, quit);

  info = g_menu_new();
  g_menu_append_submenu (menu, "Informations", G_MENU_MODEL(info));

  // sous-menu
  rules = g_menu_item_new("Règles du jeu", NULL);
  g_menu_append_item(info, rules);

  about = g_menu_item_new("A propos", NULL);
  g_menu_append_item(info, about);

  // pour afficher
  gtk_application_set_menubar(GTK_APPLICATION(app), G_MENU_MODEL (menu_bar));
  gtk_application_window_set_show_menubar(GTK_APPLICATION_WINDOW(window), TRUE);
  gtk_widget_show (window);

  // Clean
  g_object_unref(about);
  g_object_unref(rules);
  g_object_unref(info);
  g_object_unref(quit);
  g_object_unref(new);
  g_object_unref(menu);
  g_object_unref(menu_bar);

  //CHOIX CONFIG
  GtkWidget *choix1, *choix2, *choix3;

  choix1 = gtk_check_button_new_with_label("Puissance 4");
  choix2 = gtk_check_button_new_with_label("Puissance 6");
  choix3 = gtk_check_button_new_with_label("Puissance 8");

  //pour pouvoir cocher que 1 choix
  gtk_check_button_set_group(GTK_CHECK_BUTTON(choix2), GTK_CHECK_BUTTON(choix1));
  gtk_check_button_set_group(GTK_CHECK_BUTTON(choix3), GTK_CHECK_BUTTON(choix1));

  //afficher par la box
  gtk_box_append(GTK_BOX(init_box), choix1);
  gtk_box_append(GTK_BOX(init_box), choix2);
  gtk_box_append(GTK_BOX(init_box), choix3);
  gtk_widget_set_halign (choix1, GTK_ALIGN_CENTER);
  gtk_widget_set_halign (choix2, GTK_ALIGN_CENTER);
  gtk_widget_set_halign (choix3, GTK_ALIGN_CENTER);

  //bouton ok pour valider choix
  GtkWidget *ok;
  ok = gtk_button_new_with_label("JOUER");
  gtk_box_append(GTK_BOX(init_box), ok);
  gtk_widget_set_halign (ok, GTK_ALIGN_CENTER);
  //si choix a été fait alors quand on appuie sur jouer ça lance le board correspondant

  //affichage
  gtk_widget_show (window);
}


// MAIN
int main (int argc, char **argv) {
  GtkApplication *app;
  int status;
  app = gtk_application_new ("puissance.N", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);
  return status;
}


//A FAIRE
// quand on appuie sur jouer: afficher board et cacher le reste (plus simple que de faire une autre fenêtre)
// Au clic sur un bouton du board, on envoie à la fonction qui vérifie si on peut jouer dans cette colonne (toujours sauf si la colonne est pleine)
// Si on peut jouer, on modifie la couleur du bouton ou on transforme le bouton en une image d'un pion
//callbacks à l'IA
