#include "qgsuserprofile.h"

#include <QDir>
#include <QTextStream>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>

QgsUserProflie::QgsUserProflie( QString folder )
{
  mProfileFolder = folder;
}

const QString QgsUserProflie::folder() const
{
  return mProfileFolder;
}

const QString QgsUserProflie::name() const
{
  QDir dir( mProfileFolder );
  return dir.dirName();
}

const QString QgsUserProflie::alias() const
{
  QFile qgisPrivateDbFile( qgisDB() );

  // Looks for qgis.db
  // If it's not there we can just return name.
  if ( !qgisPrivateDbFile.exists() )
  {
    return name();
  }

  QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );
  db.setDatabaseName( qgisDB() );
  if ( !db.open() )
    return name();

  QSqlQuery query;
  query.prepare( "SELECT value FROM tbl_config_variables WHERE variable = 'ALIAS'" );
  QString profileAlias = name();
  if ( query.exec() )
  {
    query.next();
    QString alias = query.value( 0 ).toString();
    if ( !alias.isEmpty() )
      profileAlias = alias;
  }
  db.close();
  return profileAlias;
}

bool QgsUserProflie::setAlias( const QString &alias )
{
  QFile qgisPrivateDbFile( qgisDB() );

  if ( !qgisPrivateDbFile.exists() )
  {
    return false;
  }

  QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );
  db.setDatabaseName( qgisDB() );
  if ( !db.open() )
    return false;

  QSqlQuery query;
  QString sql = "INSERT OR REPLACE INTO tbl_config_variables VALUES ('ALIAS', :alias);";
  query.prepare( sql );
  query.bindValue( ":alias", alias );
  query.exec();
  db.close();
}

const QIcon QgsUserProflie::icon() const
{
  QString path = mProfileFolder + QDir::separator() + "icon.svg";
  return QIcon( path );
}

QString QgsUserProflie::qgisDB() const
{
  return mProfileFolder + QDir::separator() + "qgis.db" ;
}
