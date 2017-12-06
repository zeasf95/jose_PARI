/*File generated automatically in Jose by jose_ferrreira on Qua Dez  6 12:07:02 WET 2017*/
#ifdef __cplusplus
extern "C" {
#endif
/* callback.c */
gboolean on_drawingarea1_expose_event (GtkWidget * widget, GdkEvent * event, gpointer user_data);
gboolean pari_UpdateImageAreas (gpointer data);
/* main.c */
int main (int argc, char *argv[]);
/* myf.c */
GdkPixbuf *pari_ConvertOpenCv2Gtk (IplImage * image, int dst_w, int dst_h);
void pari_PerformImageAcquisition (CvCapture * capt);
void pari_ProcessUserOperations (IplImage * src, IplImage * dst);
void pari_RefreshDrawingArea (char *widgetName, IplImage * img);
CvCapture *pari_StartImageAcquisition ();
#ifdef __cplusplus
}
#endif
