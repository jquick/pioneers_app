/* example-start helloworld2 helloworld2.c */

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>`
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <gtkosxapplication.h>

/* Our new improved callback.  The data passed to this function
 * is printed to stdout. */
void callback( GtkWidget *widget,
               gpointer   data )
{
/* start system job
 *  g_print ("Hello again - %s was pressed\n", (char *) data);
 */
	char *dir = (char *) getenv("APP_ROOT");

	char *in = (char *) data;
	char path[200];

	strcpy(path,dir);
	strcat(path,in);

	g_print ("Executing - %s\n", (char *) path);
	
pid_t pid=fork();
	if (pid==0) { /* child process */
		if(execl(path,path,NULL) == -1){
			fprintf(stderr,"execl Error!");
		}
	}
 
    gtk_main_quit();
}

/* another callback */
gint delete_event( GtkWidget *widget,
                   GdkEvent  *event,
                   gpointer   data )
{
    gtk_main_quit();
    return(FALSE);
}

int main( int   argc,
          char *argv[] )
{
    /* GtkWidget is the storage type for widgets */
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *box1;
	GtkWidget *label;

    /* This is called in all GTK applications. Arguments are parsed
     * from the command line and are returned to the application. */
    gtk_init (&argc, &argv);


	GtkOSXApplication *theApp = g_object_new(GTK_TYPE_OSX_APPLICATION, NULL);

    /* Create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
gtk_window_set_default_size(GTK_WINDOW(window), 290, 200);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    /* This is a new call, which just sets the title of our
     * new window to "Hello Buttons!" */
    gtk_window_set_title (GTK_WINDOW (window), "Pioneers");

    /* Here we just set a handler for delete_event that immediately
     * exits GTK. */
    gtk_signal_connect (GTK_OBJECT (window), "delete_event",
                        GTK_SIGNAL_FUNC (delete_event), NULL);

    /* Sets the border width of the window. */
    gtk_container_set_border_width (GTK_CONTAINER (window), 25);

    /* We create a box to pack widgets into.  This is described in detail
     * in the "packing" section. The box is not really visible, it
     * is just used as a tool to arrange widgets. */
    box1 = gtk_vbox_new(FALSE, 0);

    /* Put the box into the main window. */
    gtk_container_add (GTK_CONTAINER (window), box1);

   label = gtk_label_new ("Select an option:");
        gtk_misc_set_alignment (GTK_MISC (label), 0, 0);
        gtk_box_pack_start (GTK_BOX (box1), label, FALSE, FALSE, 0);
        gtk_widget_show (label);
    /* Creates a new button with the label "Button 1". */
    button = gtk_button_new_with_label ("Client");

    /* Now when the button is clicked, we call the "callback" function
     * with a pointer to "button 1" as its argument */
    gtk_signal_connect (GTK_OBJECT (button), "clicked",
                        GTK_SIGNAL_FUNC (callback), (gpointer) "/pioneers-client");

    /* Instead of gtk_container_add, we pack this button into the invisible
     * box, which has been packed into the window. */
    gtk_box_pack_start(GTK_BOX(box1), button, TRUE, TRUE, 5);

    /* Always remember this step, this tells GTK that our preparation for
     * this button is complete, and it can now be displayed. */
    gtk_widget_show(button);

    /* Do these same steps again to create a second button */
    button = gtk_button_new_with_label ("Server");

    /* Call the same callback function with a different argument,
     * passing a pointer to "button 2" instead. */
    gtk_signal_connect (GTK_OBJECT (button), "clicked",
                        GTK_SIGNAL_FUNC (callback), (gpointer) "/pioneers-server-gtk");

    gtk_box_pack_start(GTK_BOX(box1), button, TRUE, TRUE, 5);

    /* The order in which we show the buttons is not really important, but I
     * recommend showing the window last, so it all pops up at once. */
    gtk_widget_show(button);

    /* Creates a new button with the label "Button 1". */
    button = gtk_button_new_with_label ("Editor");

    /* Now when the button is clicked, we call the "callback" function
     * with a pointer to "button 1" as its argument */
    gtk_signal_connect (GTK_OBJECT (button), "clicked",
                        GTK_SIGNAL_FUNC (callback), (gpointer) "/pioneers-editor");

    /* Instead of gtk_container_add, we pack this button into the invisible
     * box, which has been packed into the window. */
    gtk_box_pack_start(GTK_BOX(box1), button, TRUE, TRUE, 5);

    /* Always remember this step, this tells GTK that our preparation for
     * this button is complete, and it can now be displayed. */

    gtk_widget_show(button);

    gtk_widget_show(box1);

	gtk_widget_show(window);

	gtk_osxapplication_ready(theApp);
    /* Rest in gtk_main and wait for the fun to begin! */
    gtk_main ();

    return(0);
}
/* example-end */
