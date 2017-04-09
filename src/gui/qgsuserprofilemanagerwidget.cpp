/***************************************************************************
  qgsuserprofilemanagerwidget.cpp - QgsUserProfileManagerWidget

 ---------------------
 begin                : 16.3.2017
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

#include <QDesktopServices>
#include <QUrl>
#include <QInputDialog>
#include <QMessageBox>
#include <QSize>

#include <QFormLayout>

#include "qgsuserprofilemanagerwidget.h"
#include "qgssettings.h"
#include "qgsuserprofile.h"
#include "qgsuserprofilemanager.h"
#include "qgsapplication.h"
#include <qgserror.h>

QgsUserProfileManagerWidget::QgsUserProfileManagerWidget( QgsUserProfileManager *manager, QWidget *parent )
  : QgsOptionsPageWidget( parent ),
    mManager( manager )
{
  setupUi( this );
  setObjectName( "ProfileManager" );
  connect( mProfilesFolder, &QPushButton::clicked, this, &QgsUserProfileManagerWidget::openProfilesFolder );
  connect( mAddProfile, &QToolButton::clicked, this, &QgsUserProfileManagerWidget::addNewProfile );
  connect( mRemoveProfile, &QToolButton::clicked, this, &QgsUserProfileManagerWidget::removeProfile );
  setDockMode( true );
}

void QgsUserProfileManagerWidget::apply()
{
}

void QgsUserProfileManagerWidget::refreshProfiles()
{
  mProfileList->clear();
  QStringList profiles = mManager->allProfiles();
  Q_FOREACH ( const QString &profileName, profiles )
  {
    QgsUserProflie *profile = mManager->profileForName( profileName );
    QListWidgetItem *item = new QListWidgetItem( profile->icon(), profile->alias() );
    item->setData( Qt::UserRole + 1, profile->name() );
    mProfileList->addItem( item );
  }
}

void QgsUserProfileManagerWidget::showEvent( QShowEvent *event )
{
  refreshProfiles();
}

void QgsUserProfileManagerWidget::openProfilesFolder()
{
  QDesktopServices::openUrl( QUrl::fromLocalFile( mManager->rootLocation() ) );
}

void QgsUserProfileManagerWidget::addNewProfile()
{
  QgsEditProfileWidget *widget = new QgsEditProfileWidget( QgsEditProfileWidget::Add );
  showPanel( widget );
//  bool ok;
//  QString text = QInputDialog::getText( this, tr( "Profile folder name." ),
//                                        tr( "Profile name:" ), QLineEdit::Normal,
//                                        "", &ok );
//  if ( ok && !text.isEmpty() )
//  {
//    text = text.trimmed();
//    mManager->createUserProflie( text );
//    refreshProfiles();
//  }
}

void QgsUserProfileManagerWidget::removeProfile()
{

  QListWidgetItem *item = mProfileList->currentItem();
  if ( !item )
    return;

  QString name = item->data( Qt::UserRole + 1 ).toString();
  QgsError error = mManager->deleteProfile( name );
  if ( !error.isEmpty() )
  {
    QMessageBox::warning( this, tr( "Error deleting profile" ), error.message() );
  }
  else
  {
    refreshProfiles();
  }
}

QgsEditProfileWidget::QgsEditProfileWidget( Mode mode, QWidget *parent )
  : QgsPanelWidget( parent ),
    mMode( mode )
{
  mSaveButton = new QPushButton();
  mSaveButton->setText( tr( "Save Profile" ) );

  mFolderName = new QLineEdit();
  mFolderName->setEnabled( false );
  mFolderName->hide();
  mAlias = new QLineEdit();
  mIconPicker = new QListWidget();
  mIconPicker->setIconSize( QSize( 48, 48 ) );
  mIconPicker->setViewMode( QListWidget::IconMode );
  mIconPicker->setMovement( QListWidget::Snap );

  switch ( mode )
  {
    case Mode::Add:
    {
      setPanelTitle( tr( "Add Profile" ) );
      connect( mAlias, &QLineEdit::textEdited, this, &QgsEditProfileWidget::updateFolderName );
      break;
    }
    case Mode::Edit:
    {
      setPanelTitle( tr( "Edit Profile" ) );
      break;
    }
  }

  for ( int var = 0; var < 20; ++var )
  {
    mIconPicker->addItem( new QListWidgetItem( QIcon( "F:\\icons\\SVG\\pacman.svg" ), QStringLiteral( "" ) ) );
  }

  QFormLayout *formLayout = new QFormLayout();
  setLayout( formLayout );
  formLayout->addRow( tr( "Name" ), mAlias );
  formLayout->addRow( tr( "Icon" ), mIconPicker );
  formLayout->addRow( QStringLiteral( "" ), mSaveButton );
}

void QgsEditProfileWidget::setProfile( QgsUserProfile *profile )
{

}

void QgsEditProfileWidget::updateFolderName( const QString text )
{
  QString folderName = "profile_" + text.toLower().replace( " ", "_" );
  mFolderName->setText( folderName );
}

void QgsEditProfileWidget::saveProfile()
{
  // Create the user profile.
  if ( mMode == Mode::Add )
  {

  }
}







