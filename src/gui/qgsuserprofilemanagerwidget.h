/***************************************************************************
  qgsuserprofilemanagerwidget.h - QgsUserProfileManagerWidget

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
#ifndef QGSUSERPROFILEMANAGERWIDGET_H
#define QGSUSERPROFILEMANAGERWIDGET_H

#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>

#include "qgsoptionswidgetfactory.h"
#include "qgspanelwidget.h"

#include <ui_qgsuserprofilemanagerwidget.h>

class QgsUserProfileManager;
class QgsUserProfile;

class QgsEditProfileWidget : public QgsPanelWidget
{
    Q_OBJECT

  public:
    enum Mode
    {
      Add,
      Edit
    };

    QgsEditProfileWidget( Mode mode, QWidget *parent = nullptr );

    void setProfile( QgsUserProfile *profile );

  private slots:
    void updateFolderName( const QString text );
    void saveProfile();

  private:
    Mode mMode = Mode::Add;
    QPushButton *mSaveButton = nullptr;
    QLineEdit *mFolderName = nullptr;
    QLineEdit *mAlias = nullptr;
    QListWidget *mIconPicker = nullptr;
};

/**
 * Widget for managing user profiles on the machine.
 */
class GUI_EXPORT QgsUserProfileManagerWidget : public QgsOptionsPageWidget, private Ui::QgsUserProfileManagerWidget
{
    Q_OBJECT
  public:

    /**
    * Widget for managing user profiles on the machine.
    * @param manager The user profile manager for the widget to use.
    * @param parent The parent widget.
    */
    QgsUserProfileManagerWidget( QgsUserProfileManager *manager, QWidget *parent = nullptr );

    /**
     * Apply any changes to the settings object.
     */
    void apply() override;

    /**
     * Refresh the list of profiles.
     */
    void refreshProfiles();

  protected:
    void showEvent( QShowEvent *event );

  private slots:

    /**
     * Open the profiles root folder.
     */
    void openProfilesFolder();

    /**
     * Adds a new profile.
     */
    void addNewProfile();

    /**
     * Removes the selected profile.
     */
    void removeProfile();


  private:
    QgsUserProfileManager *mManager = nullptr;
};

#endif // QGSUSERPROFILEMANAGERWIDGET_H
