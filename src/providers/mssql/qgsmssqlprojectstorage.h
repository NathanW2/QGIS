/***************************************************************************
  qgsmssqlprojectstorage.h - qgsmssqlprojectstorage

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
#ifndef QGSMSSQLPROJECTSTORAGE_H
#define QGSMSSQLPROJECTSTORAGE_H

#include "qgsconfig.h"
#include "qgsprojectstorage.h"

#include "qgsdatasourceuri.h"


class QgsMssqlProjectStorage : public QgsProjectStorage
{
  public:
    virtual QString type() override { return QStringLiteral( "mssql" ); }

    virtual QStringList listProjects( const QString &uri ) override;

    virtual bool readProject( const QString &uri, QIODevice *device, QgsReadWriteContext &context ) override;

    virtual bool writeProject( const QString &uri, QIODevice *device, QgsReadWriteContext &context ) override;

    virtual bool removeProject( const QString &uri ) override;

    virtual bool readProjectStorageMetadata( const QString &uri, QgsProjectStorage::Metadata &metadata ) override;

#ifdef HAVE_GUI
    // GUI support
    virtual QString visibleName() override;
    virtual QString showLoadGui() override;
    virtual QString showSaveGui() override;
#endif

//    static QString encodeUri( const QgsPostgresProjectUri &postUri );
//    static QgsPostgresProjectUri decodeUri( const QString &uri );
};

#endif // QGSMSSQLPROJECTSTORAGE_H
