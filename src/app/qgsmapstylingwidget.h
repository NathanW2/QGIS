#ifndef QGSMAPSTYLESDOCK_H
#define QGSMAPSTYLESDOCK_H

#include <QListView>
#include <QToolButton>
#include <QWidget>
#include <QLabel>
#include <QTabWidget>
#include <QStackedWidget>
#include <QDialogButtonBox>
#include <QCheckBox>
#include <QUndoCommand>
#include <QDomNode>
#include <QTimer>
#include <QStandardItemModel>

class QgsLabelingWidget;
class QgsMapLayer;
class QgsMapCanvas;
class QgsRendererV2PropertiesDialog;
class QgsUndoWidget;
class QgsMapRendererSequentialJob;

class APP_EXPORT QgsMapLayerStyleManagerWidget : public QWidget
{
    Q_OBJECT
  public:
    explicit QgsMapLayerStyleManagerWidget( QgsMapCanvas* canvas, QWidget *parent = 0 );

    void setLayer( QgsMapLayer* mapLayer );

  public slots:
    void updateCurrent();
    void updateThumbnails();

  private slots:
    void styleClicked( QModelIndex index );
    void currentStyleChanged( QString name );
    void styleAdded( QString name );
    void styleRemoved( QString name );
    void styleRenamed( QString oldname, QString newname );
    void addStyle();
    void removeStyle();

  private:
    QgsMapCanvas* mCanvas;
    QgsMapLayer* mLayer;
    QStandardItemModel* mModel;
    QListView* mStyleList;
    QMap<QString, QImage> mImageCache;
    QgsMapRendererSequentialJob* mJob;
};

class APP_EXPORT QgsMapLayerStyleCommand : public QUndoCommand
{
  public:
    QgsMapLayerStyleCommand( QgsMapLayer* layer, const QDomNode& current, const QDomNode& last );

    virtual void undo() override;
    virtual void redo() override;

  private:
    QgsMapLayer* mLayer;
    QDomNode mXml;
    QDomNode mLastState;
};

class APP_EXPORT QgsMapStylingWidget : public QWidget
{
    Q_OBJECT
  public:
    explicit QgsMapStylingWidget( QgsMapCanvas *canvas, QWidget *parent = 0 );
    QgsMapLayer* layer() { return mCurrentLayer; }

  signals:
    void styleChanged( QgsMapLayer* layer );

  public slots:
    void setLayer( QgsMapLayer* layer );
    void apply();
    void autoApply();

  private slots:
    void updateCurrentWidgetLayer( int currentPage );
    void styleChanged();

  private:
    int mNotSupportedPage;
    int mVectorPage;
    int mStyleTabIndex;
    int mLabelTabIndex;
    int mMapStyleManagerIndex;
    QTimer* mAutoApplyTimer;
    QDomNode mLastStyleXml;
    QgsMapCanvas* mMapCanvas;
    bool mBlockAutoApply;
    QgsUndoWidget* mUndoWidget;
    QLabel* mLayerTitleLabel;
    QgsMapLayer* mCurrentLayer;
    QStackedWidget* mStackedWidget;
    QTabWidget *mMapStyleTabs;
    QgsLabelingWidget *mLabelingWidget;
    QgsRendererV2PropertiesDialog* mVectorStyleWidget;
    QDialogButtonBox* mButtonBox;
    QCheckBox* mLiveApplyCheck;
    QToolButton* mUndoButton;
    QToolButton* mRedoButton;
    QgsMapLayerStyleManagerWidget* mStyleManager;
};

#endif // QGSMAPSTYLESDOCK_H
