#include "myf.h"

CvCapture *
pari_StartImageAcquisition ()
{
  CvCapture *capture = cvCaptureFromCAM (0);	//Capture using 1st camera: i.e., no. 0
  IplImage *frame = cvQueryFrame (capture);	//Update frame. Pointer does not change.
  src_imageG = cvCreateImage (cvGetSize (frame), IPL_DEPTH_8U, 3);	//create image for color (8 bits, 3 channels)
  dst_imageG = cvClone (src_imageG);	//create clone of source image
  return capture;
}

void
pari_PerformImageAcquisition (CvCapture * capt)
{
  static IplImage *frame;
  frame = cvQueryFrame (capt);	//Update frame pointer.
  cvCopy (frame, src_imageG, NULL);	//copy frame as it is (preserve color)
  cvCopy (src_imageG, dst_imageG, NULL);	//copy src into dst and ready to process (admitt similar image structure)
}

void
pari_ProcessUserOperations (IplImage * src, IplImage * dst)
{
/*If nothing is to be done at least the dst is the same as src*/
  cvCopy (src, dst, NULL);

  //Now operate all functions accumulated (one after one)
  pari_UserOperation1 (dst, dst, builderG, (gpointer) "checkbutton1",
		       (gpointer) "adjustment1");
  pari_UserOperation2 (dst, dst, builderG, (gpointer) "checkbutton2",
		       (gpointer) "adjustment2");

}

GdkPixbuf *
pari_ConvertOpenCv2Gtk (IplImage * image, int dst_w, int dst_h)
{
  IplImage *gtkMask = image;
  GdkPixbuf *pix, *rpix;
  cvCvtColor (image, gtkMask, CV_BGR2RGB);
  pix = gdk_pixbuf_new_from_data ((guchar *) gtkMask->imageData,
				  GDK_COLORSPACE_RGB,
				  FALSE,
				  gtkMask->depth,
				  gtkMask->width,
				  gtkMask->height,
				  gtkMask->widthStep, NULL, NULL);
  rpix = gdk_pixbuf_scale_simple (pix, dst_w, dst_h, GDK_INTERP_BILINEAR);	//rescale image
  g_object_unref (pix);		//free the intermediate pixbuf...
  return rpix;
}

//copy from IplImage to pixbuf and paint DA
void
pari_RefreshDrawingArea (char *widgetName, IplImage * img)
{
  GtkWidget *da = GTK_WIDGET (gtk_builder_get_object (builderG, widgetName));
  if (!da)
    {
      printf ("failed\n");
      return;
    }
  GdkPixbuf *pix =
    pari_ConvertOpenCv2Gtk (img, da->allocation.width, da->allocation.height);
  cairo_t *cr = gdk_cairo_create (gtk_widget_get_window (da));
  gdk_cairo_set_source_pixbuf (cr, pix, 0, 0);
  cairo_paint (cr);
  cairo_fill (cr);
  cairo_destroy (cr);
  g_object_unref (pix);		//free the pixbuf...
}

void pari_UserOperation1 ()
{
  IplImage *tmp_gray = cvCreateImage (cvSize (src->width, src->height), IPL_DEPTH_8U, 1);	//aux image
  cvCvtColor (src, tmp_gray, CV_RGB2GRAY);
  cvMerge (tmp_gray, tmp_gray, tmp_gray, NULL, dst);	//thee equal channels
  cvReleaseImage (&tmp_gray);	//free aux image
}

void pari_UserOperation2 ()
{
  IplImage *tmp_gray = cvCreateImage (cvSize (dst->width, dst->height), IPL_DEPTH_8U, 1);	//aux image
  cvCvtColor (dst, tmp_gray, CV_RGB2GRAY);
  cvCanny (tmp_gray, tmp_gray, 0, 30, 3);
  cvMerge (tmp_gray, tmp_gray, tmp_gray, NULL, dst);
  cvReleaseImage (&tmp_gray);
}
