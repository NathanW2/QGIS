/***************************************************************************
                         qgisappstylesheet.cpp
                         ----------------------
    begin                : Jan 18, 2013
    copyright            : (C) 2013 by Larry Shaffer
    email                : larrys at dakotacarto dot com

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "qgsstylesheet.h"
#include "qgsapplication.h"
#include "qgslogger.h"

#include <QFont>
#include <QSettings>
#include <QStyle>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

/** @class QgisAppStyleSheet
 * @brief Adjustable stylesheet for the Qgis application
 */

QgsStyleSheet::QgsStyleSheet( QObject *parent )
    : QObject( parent )
{
  setActiveValues();
}

QgsStyleSheet::~QgsStyleSheet()
{
}

QMap<QString, QVariant> QgsStyleSheet::defaultVariables()
{
  QMap<QString, QVariant> opts;

  // the following default values, before insertion in opts, can be
  // configured using the platforms and window servers defined in the
  // constructor to set reasonable non-Qt defaults for the app stylesheet
  QSettings settings;
  // handle move from old QSettings group (/) to new (/qgis/stylesheet)
  // NOTE: don't delete old QSettings keys, in case user is also running older QGIS
  QVariant oldFontPointSize = settings.value( "/fontPointSize" );
  QVariant oldFontFamily = settings.value( "/fontFamily" );

  settings.beginGroup( "qgis/stylesheet" );

  int fontSize = mDefaultFont.pointSize();
  if ( mAndroidOS )
  {
    // TODO: find a better default fontsize maybe using DPI detection or so (from Marco Bernasocchi commit)
    fontSize = 8;
  }
  if ( oldFontPointSize.isValid() && !settings.value( "fontPointSize" ).isValid() )
  {
    fontSize = oldFontPointSize.toInt();
  }

  opts.insert( "@qgis_font_size", settings.value( "fontPointSize", QVariant( fontSize ) ) );

  QString fontFamily = mDefaultFont.family();
  if ( oldFontFamily.isValid() && !settings.value( "fontFamily" ).isValid() )
  {
    fontFamily = oldFontFamily.toString();
  }
  fontFamily = settings.value( "fontFamily", QVariant( fontFamily ) ).toString();
  // make sure family exists on system
  if ( fontFamily != mDefaultFont.family() )
  {
    QFont *tempFont = new QFont( fontFamily );
    if ( tempFont->family() != fontFamily )
    {
      // missing from system, drop back to default
      fontFamily = mDefaultFont.family();
    }
    delete tempFont;
  }

  opts.insert( "@qgis_font_family", QVariant( fontFamily ) );

  settings.endGroup(); // "qgis/stylesheet"

  QString fontstyle = QString( "%1pt \"%2\"" ).arg( fontSize ).arg( fontFamily );
  opts.insert( "@qgis_font", fontstyle );
  opts.insert( "@qgis_icon_size", settings.value( "/IconSize", 24 ) );

  return opts;
}

QString QgsStyleSheet::generateStyleSheetFile( QString styleFolder, const QMap<QString, QVariant>& opts )
{
  QString stylesheetname = styleFolder + "/style.qss";
  QString autostylesheet = styleFolder + "/style.generated";

  QFile file( stylesheetname );
  QFile variablesfile( styleFolder + "/variables.qss" );
  QFile fileout( autostylesheet );

  QFileInfo variableInfo( variablesfile );

  QMap<QString, QVariant> variables = opts;
  if ( variableInfo.exists() && variablesfile.open( QIODevice::ReadOnly ) )
  {
    QTextStream in( &variablesfile );
    while ( !in.atEnd() )
    {
      QString line = in.readLine();
      // This is is a variable
      if ( line.startsWith( "@" ) )
      {
        int index = line.indexOf( ":" );
        QString name = line.mid( 0, index );
        QString value = line.mid( index + 1, line.length() );
        variables.insert( name, value );
      }
    }
    variablesfile.close();
  }

  if ( file.open( QIODevice::ReadOnly ) && fileout.open(QIODevice::WriteOnly) )
    {
    QString styledata = file.readAll();
  QMap<QString, QVariant>::iterator i;
  for (i = variables.begin(); i != variables.end(); ++i)
    {
        styledata.replace( i.key(), i.value().toString() );
    }

    QTextStream out( &fileout );
    out << styledata;
    fileout.close();
    file.close();
    stylesheetname = autostylesheet;
    }

  QString styleSheet = QLatin1String( "file:///" );
  styleSheet.append( stylesheetname );

  return styleSheet;
}

void QgsStyleSheet::saveToSettings( const QMap<QString, QVariant>& opts )
{
  QSettings settings;
  settings.beginGroup( "qgis/stylesheet" );

  QMap<QString, QVariant>::const_iterator opt = opts.constBegin();
  while ( opt != opts.constEnd() )
  {
    settings.setValue( QString( opt.key() ), opt.value() );
    ++opt;
  }
  settings.endGroup(); // "qgis/stylesheet"
}

void QgsStyleSheet::setActiveValues()
{
  mStyle = qApp->style()->objectName(); // active style name (lowercase)
  QgsDebugMsg( QString( "Style name: %1" ).arg( mStyle ) );

  mMotifStyle = mStyle.contains( "motif" ) ? true : false; // motif
  mCdeStyle = mStyle.contains( "cde" ) ? true : false; // cde
  mPlastqStyle = mStyle.contains( "plastique" ) ? true : false; // plastique
  mCleanLkStyle = mStyle.contains( "cleanlooks" ) ? true : false; // cleanlooks
  mGtkStyle = mStyle.contains( "gtk" ) ? true : false; // gtk+
  mWinStyle = mStyle.contains( "windows" ) ? true : false; // windows
  mWinXpStyle = mStyle.contains( "windowsxp" ) ? true : false; // windowsxp
  mWinVistaStyle = mStyle.contains( "windowsvista" ) ? true : false; // windowsvista
  mMacStyle = mStyle.contains( "macintosh" ) ? true : false; // macintosh (aqua)
  mOxyStyle = mStyle.contains( "oxygen" ) ? true : false; // oxygen

  mDefaultFont = qApp->font(); // save before it is changed in any way

  // platforms, specific
#ifdef Q_OS_LINUX
  mLinuxOS = true;
#else
  mLinuxOS = false;
#endif
#ifdef Q_OS_WIN
  mWinOS = true;
#else
  mWinOS = false;
#endif
#ifdef Q_OS_MAC
  mMacOS = true;
#else
  mMacOS = false;
#endif
#ifdef ANDROID
  mAndroidOS = true;
#else
  mAndroidOS = false;
#endif

  // platforms, general
#ifdef Q_OS_UNIX
  mUnix = true;
#else
  mUnix = false;
#endif

  // window servers
#if defined(Q_OS_UNIX) && !defined(Q_OS_MAC)
  mX11WS = true;
#else
  mX11WS = false;
#endif
#ifdef Q_OS_WIN
  mWinWS = true;
#else
  mWinWS = false;
#endif
#ifdef Q_OS_MAC
  mMacWS = true;
#else
  mMacWS = false;
#endif

}
