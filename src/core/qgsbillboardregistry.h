/***************************************************************************
                              qgsbillboardregistry.h
                              ----------------------
  begin                : February 2016
  copyright            : (C) 2016 by Sandro Mani
  email                : smani@sourcepole.ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSBILLBOARDREGISTRY_H
#define QGSBILLBOARDREGISTRY_H

#include <QObject>
#include <QImage>
#include "qgspoint.h"

class QgsMapCanvasItem;

/** \ingroup core
 * \class QgsBillBoardItem
 * \note added in QGIS 2.16
 * A billboard item stored in the QgsBillBoardRegistry.
 */
class CORE_EXPORT QgsBillBoardItem
{
  public:
    //! The image of the billboard
    QImage image;
    //! The WGS84 world position of the billboard
    QgsPoint worldPos;
    //! The layer which the image is part of, if any
    QString layerId;
};

/** \ingroup core
 * \class QgsBillBoardRegistry
 * \note added in QGIS 2.16
 * @brief The QgsBillBoardRegistry class stores images which should
 * be displayed as billboards in the globe plugin.
 * Map canvas items and layers may decide to add items which should
 * be drawn as billboards in the globe.
 *
 * Retrieve the instance pointer to a QgsBillBoardRegistry for a
 * project via QgsProject::instance()->billboardRegistry().
 */
class CORE_EXPORT QgsBillBoardRegistry : public QObject
{
    Q_OBJECT
  public:

    ~QgsBillBoardRegistry();

    /**
     * @brief Adds a billboard to the registry.
     * @param parent The parent (i.e. a QgsMapLayer or a QgsMapCanvasItem) which is creating the billboard.
     * Each parent can only have a single billboard - if a billboard for the parent already exists, it will
     * be updated to match to new image and settings.
     * @param image The billboard image
     * @param worldPos The geo position of the image, in WGS84
     * @param layerId The id of the layer to which the item belongs, if any
     */
    void addItem( void* parent, const QImage& image, const QgsPoint& worldPos, const QString& layerId = QString() );

    /**
     * @brief Removes all billboards which were created by the specified parent
     * @param parent The parent
     */
    void removeItem( void* parent );

    /**
     * @brief Retreive all registered billboard items
     * @return List of registered billboard items
     */
    QList<QgsBillBoardItem*> items() const;

  signals:
    /** Emitted when an item is added to the registry */
    void itemAdded( QgsBillBoardItem* item );
    /** Emitted when an item is removed from the registry */
    void itemRemoved( QgsBillBoardItem* item );

  private:
    friend class QgsProject; // Only QgsProject is allowed to construct this class
    QgsBillBoardRegistry( QObject* parent = nullptr ) : QObject( parent ) {}

    QMap<void*, QgsBillBoardItem*> mItems;
};

#endif // QGSBILLBOARDREGISTRY_H
