#ifndef QGSUSERPROFILE_H
#define QGSUSERPROFILE_H

#include "qgis.h"

#include <QIcon>

/** \ingroup core
 * User profile contains information about the user profile folders on the machine.
 * In QGIS 3 all settings, plugins, etc were moved into a %APPDATA%/profiles folder for each platform.
 * This allows for manage different user profiles per machine vs the single default one that was allowed in the
 * pass.
 *
 * A user profile is all settings and anything that used to be found in .qgis2/3.
 */
class CORE_EXPORT QgsUserProflie
{
  public:
    QgsUserProflie( QString folder );

    /**
     * The base folder for the user profile.
     * @return
     */
    const QString folder() const;

    /**
     * The name for the user profile.
     * @return
     */
    const QString name() const;

    /**
     * Return the alias for the user profile. Reads the alias from .profile
     * in the profile folder.
     * @return If no alais is set name() is returned.
     */
    const QString alias() const;

    bool setAlias( const QString &alias );

    /**
     * The icon for the user profile.
     * @return
     */
    const QIcon icon() const;

  private:
    QString qgisDB() const;
    QString mProfileFolder;
};

#endif
