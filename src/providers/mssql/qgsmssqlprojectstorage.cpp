/***************************************************************************
  qgsmssqlprojectstorage.cpp - qgsmssqlprojectstorage

 ---------------------
 begin                : 16.4.2018
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
#include "qgsmssqlprojectstorage.h"

QStringList QgsMssqlProjectStorage::listProjects( const QString &uri )
{

}

bool QgsMssqlProjectStorage::readProject( const QString &uri, QIODevice *device, QgsReadWriteContext &context )
{

}

bool QgsMssqlProjectStorage::writeProject( const QString &uri, QIODevice *device, QgsReadWriteContext &context )
{

}

bool QgsMssqlProjectStorage::removeProject( const QString &uri )
{

}

bool QgsMssqlProjectStorage::readProjectStorageMetadata( const QString &uri, QgsProjectStorage::Metadata &metadata )
{

}

#ifdef HAVE_GUI

QString QgsMssqlProjectStorage::visibleName()
{

}

QString QgsMssqlProjectStorage::showLoadGui()
{

}

QString QgsMssqlProjectStorage::showSaveGui()
{

}

#endif
