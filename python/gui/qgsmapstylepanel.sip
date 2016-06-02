class QgsMapStylePanel : public QWidget
{
%TypeHeaderCode
#include <qgsmapstylepanel.h>
%End
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
class QgsMapStylePanelFactory
{
%TypeHeaderCode
#include <qgsmapstylepanel.h>
%End
  public:
    /** Constructor */
    QgsMapStylePanelFactory();

    /** Destructor */
    virtual ~QgsMapStylePanelFactory();

    virtual QIcon icon() = 0;
    virtual QString title() = 0;
    virtual QList<QgsMapLayer::LayerType> layerTypes() = 0;
    virtual QgsMapStylePanel* createPanel( QgsMapLayer* layer, QgsMapCanvas *canvas, QWidget* parent ) = 0;
};
