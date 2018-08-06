/***************************************************************************
  qgsmapswipecanvasmap.h - QgsMapSwipeCanvasMap

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
#ifndef QGSMAPSWIPECANVASMAP_H
#define QGSMAPSWIPECANVASMAP_H

#include "qgsmapcanvasmap.h"


class QgsMapCanvas;

// TODO
//  - Add mode
//  - Add slider tool
// -  Add fade in/out
class QgsMapSwipeCanvasMap : public QgsMapCanvasMap
{

  public:
    QgsMapSwipeCanvasMap( QgsMapCanvas *canvas );

    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};

#endif // QGSMAPSWIPECANVASMAP_H
