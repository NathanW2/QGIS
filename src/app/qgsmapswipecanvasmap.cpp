/***************************************************************************
  qgsmapswipecanvasmap.cpp - QgsMapSwipeCanvasMap

 ---------------------
 begin                : 6.8.2018
 copyright            : (C) 2018 by nathan
 email                : [your-email-here]
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include "qgsmapswipecanvasmap.h"
#include "qgsmapcanvas.h"
#include "qgslogger.h"

QgsMapSwipeCanvasMap::QgsMapSwipeCanvasMap( QgsMapCanvas *canvas )
  : QgsMapCanvasMap( canvas )
{

}

void QgsMapSwipeCanvasMap::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  QgsDebugMsg("PAINT");
}
