#include <gtk/gtk.h>

static void
activate(GtkApplication* app, gpointer user_data) {
	GtkWidget *window;
	GtkWidget *tbox;
	GtkWidget *box;
	GtkWidget *button1, *button2, *button3;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Hello, World!");
//	gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

	tbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);

	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
	gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
	gtk_box_append(GTK_BOX(tbox), box);

	button1 = gtk_toggle_button_new_with_label("Left");
	gtk_box_append(GTK_BOX(box), button1);

	button2 = gtk_toggle_button_new_with_label("Center");
	gtk_box_append(GTK_BOX(box), button2);

	button3 = gtk_toggle_button_new_with_label("Right");
	gtk_box_append(GTK_BOX(box), button3);

	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
	gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(box, GTK_ALIGN_CENTER);

	button1 = gtk_toggle_button_new_with_label("!Left");
	gtk_box_append(GTK_BOX(box), button1);

	button2 = gtk_toggle_button_new_with_label("!Center");
	gtk_box_append(GTK_BOX(box), button2);

	button3 = gtk_toggle_button_new_with_label("!Right");
	gtk_box_append(GTK_BOX(box), button3);
	gtk_box_append(GTK_BOX(tbox), box);

	gtk_window_set_child(GTK_WINDOW(window), tbox);

	gtk_widget_show(window);
}

int
main(int argc, char **argv) {
	GtkApplication *app;
	int status;

	app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return status;
}

