#ifndef QGSMAPSTYLEPANEL_H
#define QGSMAPSTYLEPANEL_H

#include <QWidget>
#include <QIcon>

#include "qgsmaplayer.h"

class QgsMapCanvas;

class GUI_EXPORT QgsMapStylePanel : public QWidget
{
  Q_OBJECT
public:
  QgsMapStylePanel(QgsMapLayer* layer, QgsMapCanvas *canvas, QWidget *parent = 0);

signals:
  void widgetChanged();

public slots:
  virtual void apply() = 0;
};


/** \ingroup gui
 * \class QgsMapStylePanelFactory
 * \note added in QGIS 2.16
 */
class GUI_EXPORT QgsMapStylePanelFactory
{
  public:
    /** Constructor */
    QgsMapStylePanelFactory();

    /** Destructor */
    virtual ~QgsMapStylePanelFactory();

    virtual QIcon icon() = 0;
    virtual QString title() = 0;
    virtual QList<QgsMapLayer::LayerType> layerTypes() = 0;
    virtual QgsMapStylePanel* createPanel( QgsMapLayer* layer, QWidget* parent ) = 0;
};


#endif // QGSMAPSTYLEPANEL_H
