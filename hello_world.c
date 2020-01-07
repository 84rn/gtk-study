#include <gtk/gtk.h>

// callback function for clicked button
static void print_hello(GtkWidget *widget, gpointer data)
{
    // print message to stdout
    g_print("Hello World\n");
}

// callback function for activated app
static void activate(GtkApplication* app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *button_box;

    // create the main window and then add some widgets
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Okno");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

    // add button container
    button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_container_add(GTK_CONTAINER(window), button_box);

    // add button with label
    button = gtk_button_new_with_label("Hello world!");
    // add two signals
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    // finally, add the button to the container box
    gtk_container_add(GTK_CONTAINER(button_box), button);

    // show everything
    gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
    // main application pointer
    GtkApplication *app;
    // window exit status
    int status;

    // create new app
    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    // connect handler to "activate" signal
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    // run the app and wait for exit status
    status = g_application_run(G_APPLICATION(app), argc, argv);
    // remove app object from memory
    g_object_unref(app);

    return status;
}
