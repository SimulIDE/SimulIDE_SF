/***************************************************************************
 *   Copyright (C) 2012 by santiago González                               *
 *   santigoro@gmail.com                                                   *
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
 *   along with this program; if not, see <http://www.gnu.org/licenses/>.  *
 *                                                                         *
 ***************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QDomDocument>

#include "QPropertyEditorWidget.h"
//#include "editorwindow.h"
#include "componentselector.h"
#include "circuitwidget.h"

class MAINMODULE_EXPORT MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow();
        ~MainWindow();

 static MainWindow* self() { return m_pSelf; }

        QSettings* settings() { return &m_settings; }

        void loadPlugins();
        void unLoadPugin( QString pluginName );
        
        void readSettings();

        QTabWidget*   m_sidepanel;
        QSplitter*    m_Centralsplitter;
        QWidget*      m_ramTabWidget;
        QGridLayout*  m_ramTabWidgetLayout;
        
        QPropertyEditorWidget* m_itemprop;
        //EditorWindow* m_editorWindow;

    public slots:
        void openCirc();
        void newCircuit();
        void saveCirc();
        bool saveCircAs();

    protected:
        void closeEvent(QCloseEvent* event);

    private slots:
        void about();
        void openInfo();

    private:

 static MainWindow* m_pSelf;

        bool m_blocked;

        void createWidgets();
        void createMenus();
        void createToolBars();
        void writeSettings();

        void applyStile();
        
        QSettings m_settings;
        
        QString m_version;
        QString m_styleSheet;

        QString     m_curCirc;
        QString     m_lastCircDir;
        QStringList m_docList;
        //QStringList m_plugins;
        QHash<QString, QPluginLoader*>  m_plugins;
        CircuitWidget* m_circuit;
        ComponentSelector* components;

        QLineEdit m_findLabel;

        QAction* exitAct;
        QAction* aboutAct;
        QAction* aboutQtAct;

        QAction* stepAct;
        QAction* runAct;
        QAction* pauseAct;
        QAction* resetAct;
        QAction* stopAct;
};

#endif
