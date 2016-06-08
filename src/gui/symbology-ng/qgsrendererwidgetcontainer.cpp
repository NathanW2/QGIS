/***************************************************************************
    qgsrendererwidgetcontainer.cpp
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
#include <QDialogButtonBox>
#include <QPushButton>

#include "qgsrendererwidgetcontainer.h"
#include "qgslogger.h"

QgsPanelWidget::QgsPanelWidget( QWidget *parent )
    : QWidget( parent )
{
}

void QgsPanelWidget::acceptPanel()
{
  emit panelAccepted( this );
}

void QgsPanelWidget::emitWidgetChanged()
{
  emit widgetChanged( this );
}

void QgsPanelWidget::keyPressEvent( QKeyEvent *event )
{
  if ( event->key() == Qt::Key_Escape )
  {
    QgsDebugMsg("ESC!!!!");
    acceptPanel();
  }
}

QgsPanelWidgetPage::QgsPanelWidgetPage(QgsPanelWidget *widget, QWidget *parent)
  : QgsPanelWidget( parent )
  , mWidget( widget )
{
  setupUi( this );
  mWidgetLayout->addWidget( widget );
  mWidgetLayout->setContentsMargins( 0, 0, 0, 0 );
  mTitleText->setText( widget->panelTitle() );
  QPushButton* button = mButtonBox->button( QDialogButtonBox::Close );
  button->setDefault( true );

  connect( button, SIGNAL( pressed() ), this, SLOT( acceptPanel() ) );
  connect( widget, SIGNAL( panelAccepted(QgsPanelWidget*)), this, SLOT(acceptPanel()));
  connect( widget, SIGNAL(showPanel(QgsPanelWidget*)), this, SIGNAL(showPanel(QgsPanelWidget*)));
}

QgsPanelWidgetPage::~QgsPanelWidgetPage()
{
}

QgsPanelWidgetStackWidget::QgsPanelWidgetStackWidget(QWidget *parent)
        : QStackedWidget( parent )
{

}

void QgsPanelWidgetStackWidget::connectPanels(QList<QgsPanelWidget *> panels)
{
  Q_FOREACH( QgsPanelWidget* widget, panels)
    {
       connectPanel(widget);
    }
}

void QgsPanelWidgetStackWidget::connectPanel(QgsPanelWidget *panel)
{
   connect( panel, SIGNAL( showPanel( QgsPanelWidget* ) ), this, SLOT( showPanel( QgsPanelWidget* ) ) );
}

void QgsPanelWidgetStackWidget::showPanel(QgsPanelWidget *panel)
{
  QgsPanelWidgetPage* page = new QgsPanelWidgetPage( panel, this );

  connect( page, SIGNAL( panelAccepted(QgsPanelWidget*)), this, SLOT( closePanel(QgsPanelWidget*)));
  connect( page, SIGNAL( showPanel(QgsPanelWidget*)), this, SLOT( showPanel(QgsPanelWidget*)));

  int index = this->addWidget( page );
  this->setCurrentIndex( index );
}

void QgsPanelWidgetStackWidget::closePanel(QgsPanelWidget *panel)
{
  this->setCurrentIndex( this->currentIndex() - 1 );
  this->removeWidget( panel );
  panel->deleteLater();
}
