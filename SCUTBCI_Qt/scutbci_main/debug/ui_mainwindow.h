/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNetPresenter;
    QAction *actionStart;
    QAction *actionStop;
    QAction *actionNetReader;
    QAction *actionNetMarker;
    QAction *actionNetActuator;
    QAction *actionStimSeq;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuSetting;
    QMenu *menuControl;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1440, 900);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/resources/scutbci.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionNetPresenter = new QAction(MainWindow);
        actionNetPresenter->setObjectName(QStringLiteral("actionNetPresenter"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/resources/netpresenter.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNetPresenter->setIcon(icon1);
        actionStart = new QAction(MainWindow);
        actionStart->setObjectName(QStringLiteral("actionStart"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/resources/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStart->setIcon(icon2);
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName(QStringLiteral("actionStop"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/resources/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStop->setIcon(icon3);
        actionNetReader = new QAction(MainWindow);
        actionNetReader->setObjectName(QStringLiteral("actionNetReader"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/resources/netreader.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNetReader->setIcon(icon4);
        actionNetMarker = new QAction(MainWindow);
        actionNetMarker->setObjectName(QStringLiteral("actionNetMarker"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/resources/netmarker.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNetMarker->setIcon(icon5);
        actionNetActuator = new QAction(MainWindow);
        actionNetActuator->setObjectName(QStringLiteral("actionNetActuator"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/images/resources/netactuator.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNetActuator->setIcon(icon6);
        actionStimSeq = new QAction(MainWindow);
        actionStimSeq->setObjectName(QStringLiteral("actionStimSeq"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/images/resources/stimseq.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStimSeq->setIcon(icon7);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1440, 26));
        menuSetting = new QMenu(menubar);
        menuSetting->setObjectName(QStringLiteral("menuSetting"));
        menuControl = new QMenu(menubar);
        menuControl->setObjectName(QStringLiteral("menuControl"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuSetting->menuAction());
        menubar->addAction(menuControl->menuAction());
        menuSetting->addAction(actionNetPresenter);
        menuSetting->addAction(actionNetReader);
        menuSetting->addAction(actionNetMarker);
        menuSetting->addAction(actionNetActuator);
        menuControl->addAction(actionStart);
        menuControl->addAction(actionStop);
        menuControl->addAction(actionStimSeq);
        toolBar->addAction(actionNetReader);
        toolBar->addAction(actionNetMarker);
        toolBar->addAction(actionNetActuator);
        toolBar->addAction(actionNetPresenter);
        toolBar->addSeparator();
        toolBar->addAction(actionStimSeq);
        toolBar->addAction(actionStart);
        toolBar->addAction(actionStop);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionNetPresenter->setText(QApplication::translate("MainWindow", "\345\237\272\346\234\254\350\256\276\347\275\256", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionNetPresenter->setToolTip(QApplication::translate("MainWindow", "\345\237\272\346\234\254\350\256\276\347\275\256", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionStart->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213", Q_NULLPTR));
        actionStop->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionStop->setToolTip(QApplication::translate("MainWindow", "\345\201\234\346\255\242", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionNetReader->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\350\256\276\347\275\256", Q_NULLPTR));
        actionNetMarker->setText(QApplication::translate("MainWindow", "\346\211\223\346\240\207\350\256\276\347\275\256", Q_NULLPTR));
        actionNetActuator->setText(QApplication::translate("MainWindow", "\350\276\223\345\207\272\350\256\276\347\275\256", Q_NULLPTR));
        actionStimSeq->setText(QApplication::translate("MainWindow", "\345\210\272\346\277\200\345\272\217\345\210\227", Q_NULLPTR));
        menuSetting->setTitle(QApplication::translate("MainWindow", "\350\256\276\347\275\256", Q_NULLPTR));
        menuControl->setTitle(QApplication::translate("MainWindow", "\346\216\247\345\210\266", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
