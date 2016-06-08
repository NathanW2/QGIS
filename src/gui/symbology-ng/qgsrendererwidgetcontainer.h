/***************************************************************************
    qgsrendererwidgetcontainer.h
    ---------------------
    begin                : June 2016
    copyright            : (C) 2016 by Nathan Woodrow
    email                :
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef QGSRENDERERWIDGETCONTAINER_H
#define QGSRENDERERWIDGETCONTAINER_H

#include <QWidget>
#include <QKeyEvent>
#include <QStackedWidget>

#include "ui_qgsrenderercontainerbase.h"


/**
 * @brief Base class for any widget that can be shown as a inline panel
 */
class GUI_EXPORT QgsPanelWidget : public QWidget
{
    Q_OBJECT
  public:
    /**
     * @brief Base class for any widget that can be shown as a inline panel
     * @param parent Parent widget.
     */
    QgsPanelWidget(QWidget *parent = 0 );

    /**
     * Set the title of the panel when shown in the interface.
     * @param panelTitle The panel title.
     */
    void setPanelTitle( QString panelTitle ) { mPanelTitle = panelTitle; }

    /**
     * The title of the panel.
     * @return The title pf the panel.
     */
    QString panelTitle() { return mPanelTitle; }

  signals:

    /**
     * Emiited when the panel is accpeted by the user.
     * @param panel The panel widget that was accepted.
     * @note This argument is normally raised with emit panelAccpeted(this)
     * so that callers can retrive the widget easier in calling code.
     */
    void panelAccepted( QgsPanelWidget* panel );

    /**
     * Emit when you require a panel to be show in the interface.
     * @param panel The panel widget to show.
     * @note If you are connected to this signal you should also connect
     * given panels showPanel signal as they can be nested.
     */
    void showPanel( QgsPanelWidget* panel );

    /**
     * Emiited when the widget state changes.
     * Connect to this to pull any changes off the widget when needed.
     * As panels are non blocking "dialogs" you should listen to this signal
     * to give the user feedback when something changes.
     * @param panel The panels whos state changed.
     * @note You can raise this easier from your own widget using emitWidgetChanged()
     * which emits the signal as emit widgetChanged(this)
     */
    void widgetChanged( QgsPanelWidget* panel );

  public slots:

    /**
     * Accept the panel. Causes panelAccepted to be emiited.
     * Widgets are normally removed form the interface using the panel manager or the caller.
     */
    void acceptPanel();

    /**
     * EMit the widgetChanged signal for this widget.
     * @note The same as doing emit widgetChanged(this);
     */
    void emitWidgetChanged();

  protected:
    /**
     * @brief Overriden key press event to handle the esc event on the widget.
     * @param event The key event
     */
    void keyPressEvent( QKeyEvent* event );

  private:
    QString mPanelTitle;


};


/**
 * A non model panel page that can get shown to the user.  Page will contain a close button and trigger the
 * internal widgets acceptPanel() on close.
 */
class GUI_EXPORT QgsPanelWidgetPage : public QgsPanelWidget, private Ui::QgsRendererWidgetContainerBase
{
    Q_OBJECT
  public:

  /**
    * A non model panel page that can get shown to the user.
   * @param widget The internal widget to show in the page.
   * @param parent THe parent widget.
   */
  QgsPanelWidgetPage( QgsPanelWidget* widget, QWidget* parent = nullptr );

  ~QgsPanelWidgetPage();
private:
  QWidget* mWidget;
};


/**
 * A stack widget to manage panels in the interface. Handles the open and close events
 * for added panels.
 * Any widgets that want to have a non blocking panel based interface should use this
 * class to manage the panels.
 */
class GUI_EXPORT QgsPanelWidgetStackWidget : public QStackedWidget
{
    Q_OBJECT
public:

/**
  * A stack widget to manage panels in the interface. Handles the open and close events
  * for added panels.
  * @param parent
  */
  QgsPanelWidgetStackWidget( QWidget* parent = nullptr);

public slots:
  /**
   * Show a panel in the stack widget. Will connect to the panels showPanel event to handle
   * nested panels. Auto switches the the given panel for the user.
   * @param panel The panel to show.
   */
  void showPanel( QgsPanelWidget* panel);

  /**
   * Closes the panel in the widget. Will also delete the widget.
   * This slot is normally auto connected to panelAccepted when a panel is shown.
   * @param panel The panel to close.
   */
  void closePanel( QgsPanelWidget* panel);
};


#endif // QGSRENDERERWIDGETCONTAINER_H
