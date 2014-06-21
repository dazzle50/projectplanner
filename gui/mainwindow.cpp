/***************************************************************************
 *   Copyright (C) 2014 by Richard Crook                                   *
 *   http://code.google.com/p/projectplanner                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "maintabwidget.h"

/*************************************************************************************************/
/********************* Main application window showing tabbed main screens ***********************/
/*************************************************************************************************/

/****************************************** constructor ******************************************/

MainWindow::MainWindow( QWidget* parent ) : QMainWindow( parent ), ui( new Ui::MainWindow )
{
  // initialise private variables
  m_undoview = nullptr;
  m_tabs     = new MainTabWidget();

  // setup ui for main window including central widget of tabs
  ui->setupUi( this );
  setCentralWidget( m_tabs );
  resize( 900, 450 );

  // ensure plan tab and is kept up-to-date when plan signals changes
  //connect( plan, SIGNAL(signalPlanUpdated()), m_tabs, SLOT(slotUpdatePlanTab()),
  //         Qt::UniqueConnection );

  // ensure menus and plan tab are kept up-to-date when current tab changes
  //slotTabChange( m_tabs->currentIndex() );
  //connect( m_tabs, SIGNAL(currentChanged(int)), this, SLOT(slotTabChange(int)),
  //         Qt::UniqueConnection );

  // update edit menu with undostack undo & redo actions
  setModels();
}

/******************************************* setModels *******************************************/

void MainWindow::setModels()
{
  // set undostack for edit menu undo/redo

}

/******************************************* message *********************************************/

void MainWindow::message( QString msg )
{
  // raise other windows
  foreach( MainTabWidget* tabs, m_windows )
    if (tabs) tabs->raise();

  // show message on status bar and enure is top & active
  raise();
  activateWindow();
  ui->statusBar->showMessage( msg );
}

/******************************************* slotIndent ******************************************/

void MainWindow::slotIndent()
{
  // indent task(s) - determine unique rows selected

}

/****************************************** slotOutdent ******************************************/

void MainWindow::slotOutdent()
{
  // outdent task(s) - determine unique rows selected

}

/****************************************** slotFileNew ******************************************/

void MainWindow::slotFileNew()
{
  // slot for file new plan action

  qDebug("MainWindow::slotFileNew() - TODO !!!!");
}

/****************************************** slotFileOpen *****************************************/

bool MainWindow::slotFileOpen()
{
  // slot for file open plan action - get user to select filename and location
  m_tabs->endEdits();
  QString filename = QFileDialog::getOpenFileName();
  if ( filename.isEmpty() )
  {
    message();
    return false;
  }

  return false; // loadPlan( filename );
}

/****************************************** slotFileSave *****************************************/

bool MainWindow::slotFileSave()
{
  // slot for file save plan action - if plan has filename, save to same file and location
  m_tabs->endEdits();

}

/***************************************** slotFileSaveAs ****************************************/

bool MainWindow::slotFileSaveAs()
{
  // slot for file saveAs plan action - get user to select filename and location
  m_tabs->endEdits();

}

/***************************************** slotFilePrint *****************************************/

void MainWindow::slotFilePrint()
{
  // slot for file saveAs plan action
  m_tabs->endEdits();
  qDebug("MainWindow::slotFilePrint() - TODO !!!!");
}

/************************************** slotFilePrintPreview *************************************/

void MainWindow::slotFilePrintPreview()
{
  // slot for file saveAs plan action
  m_tabs->endEdits();
  qDebug("MainWindow::slotFilePrintPreview() - TODO !!!!");
}

/****************************************** slotFileExit *****************************************/

void MainWindow::slotFileExit()
{
  // slot for file saveAs plan action
  m_tabs->endEdits();
  qDebug("MainWindow::slotFileExit() - TODO !!!!");
}

/*************************************** slotAboutQPlanner ***************************************/

void MainWindow::slotAboutQPlanner()
{
  // slot for file saveAs plan action
  m_tabs->endEdits();
  qDebug("MainWindow::slotAboutQPlanner() - TODO !!!!");
}

/**************************************** slotSchedulePlan ***************************************/

void MainWindow::slotSchedulePlan()
{
  // get plan to reschedule all the tasks
  m_tabs->endEdits();
  //plan->schedule();
}

/*************************************** slotStretchTasks ****************************************/

void MainWindow::slotStretchTasks( bool checked )
{
  // if stretch tasks flag is changed, trigger redraw of gantt
  m_tabs->endEdits();

}

/***************************************** slotNewWindow *****************************************/

void MainWindow::slotNewWindow()
{
  // open new window
  MainTabWidget*  tabWidget = new MainTabWidget();
  tabWidget->setAttribute( Qt::WA_QuitOnClose, false );
  tabWidget->setAttribute( Qt::WA_DeleteOnClose, true );
  //tabWidget->removePlanTab();
  tabWidget->setWindowTitle( windowTitle() );
  tabWidget->show();
  m_windows.append( tabWidget );
}

/*************************************** slotViewUndoStack ***************************************/

void MainWindow::slotUndoStackView( bool checked )
{
  // show undo stack view window if checked, otherwise hide
  m_tabs->endEdits();

}

/*********************************** slotUndoStackViewDestroyed **********************************/

void MainWindow::slotUndoStackViewDestroyed()
{
  // undo stack view window closed and destroyed so reset pointer and uncheck action
  m_undoview = nullptr;
  ui->actionUndoStackView->setChecked( false );
}

/***************************************** slotTabChange *****************************************/

void MainWindow::slotTabChange( int index )
{
  // check if switched to tasks/gantt tab, enable its menu & actions, otherwise hide them

}
