/***************************************************************************
  qgsuserprofilemanagerwidgetfactory.h - QgsUserProfileManagerWidgetFactory

 ---------------------
 begin                : 17.3.2017
 copyright            : (C) 2017 by
 email                : [your-email-here]
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef QGSUSERPROFILEMANAGERWIDGETFACTORY_H
#define QGSUSERPROFILEMANAGERWIDGETFACTORY_H

#include "qgsoptionswidgetfactory.h"
#include "qgsuserprofilemanagerwidget.h"

class QgsUserProfileManagerWidgetFactory : public QgsOptionsWidgetFactory
{
  public:
    QgsUserProfileManagerWidgetFactory( QgsUserProfileManager *manager );
    virtual QgsOptionsPageWidget *createWidget( QWidget *parent = nullptr ) const override;

  private:
    QgsUserProfileManager *mManager = nullptr;

};

#endif // QGSUSERPROFILEMANAGERWIDGETFACTORY_H
