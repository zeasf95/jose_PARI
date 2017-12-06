/**
 *       @file  callback.c
 *      @brief  Breve Descrição
 *
 * Ficheiro com callbacks.
 *
 *     @author  José Ferreira, 71852, ferreira.jose@ua.pt
 *
 *   @internal
 *     Created  29-Nov-2017
 *     Company  University of Aveiro
 *   Copyright  Copyright (c) 2017, José Ferreira
 *
 * =====================================================================================
 */

#include "myf.h"

gboolean pari_UpdateImageAreas(gpointer data)
{
        //generate an expose event (draw event) on drawingarea1
        GtkWidget *da1 = GTK_WIDGET(gtk_builder_get_object(builderG, "drawingarea1"));
        gtk_widget_queue_draw(da1);
        return TRUE;
}

gboolean on_drawingarea1_expose_event(GtkWidget * widget, GdkEvent * event, gpointer user_data)
{
        pari_PerformImageAcquisition(captureG);             //acquire new image
        pari_ProcessUserOperations(src_imageG, dst_imageG); // Perform here the openCV transformations

        //update the drawing area displays
        pari_RefreshDrawingArea("drawingarea1", src_imageG);
        pari_RefreshDrawingArea("drawingarea2", dst_imageG);
        return TRUE;
}

