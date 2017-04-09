#include "qgsuserprofilemanager.h"
#include "qgsuserprofile.h"
#include "qgsapplication.h"

#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QProcess>


void QgsUserProfileManager::setRootLocation( QString rootProfileLocation )
{
  mRootProfilePath = rootProfileLocation + QDir::separator() + "profiles";
  mSettings = new QSettings( settingsFile(), QSettings::IniFormat );
  emit profilesChanged();
}

bool QgsUserProfileManager::rootLocationIsSet() const
{
  return !mRootProfilePath.isEmpty();
}

QString QgsUserProfileManager::defaultProfileName() const
{
  QString profileName = "default";
  mSettings->value( "/defaultProfile", "default" );
  return profileName;
}

void QgsUserProfileManager::setDefaultProfileName( const QString &name )
{
  mSettings->setValue( "/defaultProfile", name );
  mSettings->sync();
}

void QgsUserProfileManager::setDefaultFromActive()
{
  setDefaultProfileName( userProfile()->name() );
}

QStringList QgsUserProfileManager::allProfiles() const
{
  return QDir( mRootProfilePath ).entryList( QDir::Dirs | QDir::NoDotAndDotDot );
}

QgsUserProflie *QgsUserProfileManager::profileForName( const QString name ) const
{
  QString profilePath = mRootProfilePath + QDir::separator() + name;
  return new QgsUserProflie( profilePath );
}

QgsError QgsUserProfileManager::createUserProflie( const QString name )
{
  QgsError error;
  QDir folder( mRootProfilePath + QDir::separator() + name );
  if ( !folder.exists() )
  {
    QDir().mkdir( folder.absolutePath() );
  }

  QFile qgisPrivateDbFile( folder.absolutePath() + QDir::separator() + "qgis.db" );

  // first we look for ~/.qgis/qgis.db
  if ( !qgisPrivateDbFile.exists() )
  {
    // if it doesn't exist we copy it in from the global resources dir
    QString qgisMasterDbFileName = QgsApplication::qgisMasterDatabaseFilePath();
    QFile masterFile( qgisMasterDbFileName );

    //now copy the master file into the users .qgis dir
    masterFile.copy( qgisPrivateDbFile.fileName() );
  }

  if ( error.isEmpty() )
  {
    emit profilesChanged();
  }
  return error;
}

QgsError QgsUserProfileManager::deleteProfile( const QString name )
{
  QgsError error;
  QDir folder( mRootProfilePath + QDir::separator() + name );

  // This might have be changed to something better.
  bool deleted = folder.removeRecursively();
  if ( !deleted )
  {
    error.append( ( tr( "Unable to fully delete user profile folder" ) ) );
  }
  return error;
}

QString QgsUserProfileManager::settingsFile()
{
  return  mRootProfilePath + QDir::separator() + "profiles.ini";
}

QgsUserProflie *QgsUserProfileManager::userProfile()
{
  return mUserProfile;
}

void QgsUserProfileManager::loadUserProfile( const QgsUserProflie *profile )
{
  QString path = QDir::toNativeSeparators( QCoreApplication::applicationFilePath() );
  QStringList arguments;
  arguments << "--profile" << profile->name();
  QProcess::startDetached( path, arguments, QDir::toNativeSeparators( QCoreApplication::applicationDirPath() ) );
}

void QgsUserProfileManager::setUserProfile( QgsUserProflie *profile )
{
  if ( ! mUserProfile )
  {
    mUserProfile = profile;
  }
}
