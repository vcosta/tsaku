#include <gtk/gtk.h>


/* Surface to store current scribbles */
static cairo_surface_t *surface = NULL;

/* Redraw the screen from the surface. Note that the draw
 * callback receives a ready-to-be-used cairo_t that is already
 * clipped to only draw the exposed areas of the widget
 */
static void
draw_cb(GtkDrawingArea *drawing_area, cairo_t *cr, int width, int height, gpointer data) {
	cairo_set_source_surface(cr, surface, 0, 0);
	cairo_paint(cr);
}

/* Create a new surface of the appropriate size to store our scribbles */
static void
resize_cb(GtkWidget *widget, int width, int height, gpointer data) {
	if (surface) {
		cairo_surface_destroy(surface);
		surface = NULL;
	}

	if (gtk_native_get_surface(gtk_widget_get_native(widget))) {
		surface = gdk_surface_create_similar_surface(gtk_native_get_surface(gtk_widget_get_native(widget)),
				CAIRO_CONTENT_COLOR,
				gtk_widget_get_width(widget),
				gtk_widget_get_height(widget));

		cairo_t *cr;

		cr = cairo_create(surface);
		cairo_set_source_rgb(cr, 0.5, 0, 0);
		cairo_paint(cr);
		cairo_destroy(cr);
	}
}

static double color = 0.0;

gboolean
mystify_animate(GtkWidget *window) {
	cairo_t *cr;

	color += 0.1;

	cr = cairo_create(surface);

	cairo_save(cr);
	cairo_set_source_rgb(cr, 0, color, 0);
	cairo_rectangle(cr, 5, 5, 25, 25);
	cairo_clip(cr);
	cairo_paint(cr);
	cairo_restore(cr);

	cairo_save(cr);
	cairo_set_source_rgb(cr, 0, 0, color);
	cairo_rectangle(cr, 5, 35, 25, 25);
	cairo_clip(cr);
	cairo_paint(cr);
	cairo_restore(cr);

	cairo_save(cr);
	cairo_set_line_width(cr, 2.);
	cairo_set_source_rgb(cr, 0, color, 0);
	cairo_move_to(cr, 55, 55);
	cairo_line_to(cr, 75, 75);
	cairo_stroke(cr);
	cairo_restore(cr);

	cairo_destroy(cr);

	gtk_widget_queue_draw(window);

	if (color >= 1.0)
		color = 0.0;

	return TRUE;
}

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

	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
	gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(box, GTK_ALIGN_CENTER);

	button1 = gtk_button_new_with_label("SUBMIT");
	gtk_box_append(GTK_BOX(tbox), button1);

	GtkWidget *frame = gtk_frame_new (NULL);

	GtkWidget *drawing_area;
	drawing_area = gtk_drawing_area_new();
	gtk_widget_set_size_request(drawing_area, 100, 100);
	gtk_frame_set_child(GTK_FRAME(frame), drawing_area);

	gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawing_area), draw_cb, NULL, NULL);
	g_signal_connect_after(drawing_area, "resize", G_CALLBACK (resize_cb), NULL);

	gtk_box_append(GTK_BOX(tbox), frame);

	button1 = gtk_button_new_with_label("SUBMIT");
	gtk_box_append(GTK_BOX(tbox), button1);

	gtk_window_set_child(GTK_WINDOW(window), tbox);

	gtk_widget_show(window);

	g_timeout_add(20, (GSourceFunc)mystify_animate, drawing_area);
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

