/***************************************************************************
  qgsuserprofilemanagerwidgetfactory.cpp - QgsUserProfileManagerWidgetFactory

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

#include "qgsuserprofilemanagerwidgetfactory.h"

#include "qgsuserprofilemanagerwidget.h"
#include "qgsapplication.h"

QgsUserProfileManagerWidgetFactory::QgsUserProfileManagerWidgetFactory( QgsUserProfileManager *manager )
  : QgsOptionsWidgetFactory( QObject::tr( "User Profiles" ), QgsApplication::getThemeIcon( "user" ) ),
    mManager( manager )
{
}

QgsOptionsPageWidget *QgsUserProfileManagerWidgetFactory::createWidget( QWidget *parent ) const
{
  return new QgsUserProfileManagerWidget( mManager );
}
