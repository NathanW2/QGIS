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

#include <QLine>
#include <QImage>
#include <QRect>

QgsMapSwipeCanvasMap::QgsMapSwipeCanvasMap( QgsMapCanvas *canvas )
  : QgsMapCanvasMap( canvas )

{

}

void QgsMapSwipeCanvasMap::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  int height = boundingRect().height() - 2;
  int width = (boundingRect().width() / 50) * 100;
  QImage image = contentImage().copy(0, 0, width, height);
  painter->drawImage(QRect(0,0, width, height), image);
}
