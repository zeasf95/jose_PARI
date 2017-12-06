/**
 *       @file  myf.h
 *      @brief  
 *
 * 
 *
 *     @author  José Ferreira, 71852, ferreira.jose@ua.pt
 *
 *   @internal
 *     Created  27-Set-2017
 *     Company  University of Aveiro
 *   Copyright  Copyright (c) 2017, José Ferreira
 *
 * =====================================================================================
 */
//#include <cv.h>
#include <string.h>
//#include <highgui.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <gtk/gtk.h>
#include <cairo.h>

#ifndef _MYF_H
#define _MYF_H

#include <gtk/gtk.h>
#include <cv.h>
#include <highgui.h>

#include "prototypes.h"

#endif /* _MYF_H */

#if defined (_MAIN_C_)
        GtkBuilder *builderG;
        IplImage *dst_imageG , *src_imageG;
        CvCapture *captureG;
#else
        extern GtkBuilder *builderG;
        extern IplImage *dst_imageG , *src_imageG;
        extern CvCapture *captureG;
#endif


#define SHM_SIZE 128 /**< 128 bytes for shared memory */
#define PARENTDELAY 300000   /**<parent period in us*/
#define CHILDDELAY 900000    /**<child delay in us*/
#define MAXFFBUFFER 1000
typedef struct {
  int count;
  double x[MAXFFBUFFER];
  double y[MAXFFBUFFER];
} free_form;

//e as variáveis globais sugeridas são:
#if defined (_MAIN_C_)
        GtkBuilder *builderG;
        double xoffG=100;
        double yoffG=150;
	double fontSizeFactorG=1;
        free_form ffG={0};   //init count to zero. Do not affect x and y.
#else
        extern GtkBuilder *builderG;
        extern double xoffG;
        extern double yoffG;
	extern double fontSizeFactorG;
        extern free_form ffG;
#endif

/* Some definitions*/
#define NAME_IMG_ORG "ImagemOriginal"
#define NAME_IMG_BIN "ImagemBinarizada"
#define NAME_IMG_TAB "ImagemTabuleiro"
#define NAME_IMG_PRC "ImagemTratada"


typedef int byte;		// cria um novo tipo chamado byte que é o mesmo que int


typedef struct
{
  double r;	  /**< @brief Parte real do tipo complexo */
  double i;	  /**< @brief Parte imaginário do tipo complexo */
} complexo;


typedef struct
{
  int horas;	   /**< @brief horas do tempo */
  int minutos;	     /**< @brief minutos do tempo */
  int segundos;	      /**< @brief segundos do tempo */
} tempo;

typedef struct
{
  int totA, totE, totI, totO, totU, totY;
} vStat;

typedef enum
{ imBIN = 0, imCANNY, imERODE, imROTATE } im_operation;
#define MAXFFBUFFER 1000

#include "prototypes.h"
