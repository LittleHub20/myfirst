/********************************************************************************
** Form generated from reading UI file 'netmarker.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETMARKER_H
#define UI_NETMARKER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NetMarker
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_1;
    QPushButton *btnConnect;
    QLineEdit *editServer;
    QLabel *label_3;
    QPushButton *btnHide;
    QLineEdit *editPort;
    QLineEdit *editEvent;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_21;
    QPushButton *btnSend;
    QLabel *label_22;

    void setupUi(QDialog *NetMarker)
    {
        if (NetMarker->objectName().isEmpty())
            NetMarker->setObjectName(QStringLiteral("NetMarker"));
        NetMarker->resize(730, 190);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/resources/netmarker.png"), QSize(), QIcon::Normal, QIcon::Off);
        NetMarker->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(NetMarker);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(7);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_1 = new QLabel(NetMarker);
        label_1->setObjectName(QStringLiteral("label_1"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_1->sizePolicy().hasHeightForWidth());
        label_1->setSizePolicy(sizePolicy);
        label_1->setMinimumSize(QSize(0, 0));
        label_1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_1, 0, 0, 1, 1);

        btnConnect = new QPushButton(NetMarker);
        btnConnect->setObjectName(QStringLiteral("btnConnect"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnConnect->sizePolicy().hasHeightForWidth());
        btnConnect->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnConnect, 0, 3, 1, 1);

        editServer = new QLineEdit(NetMarker);
        editServer->setObjectName(QStringLiteral("editServer"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(3);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(editServer->sizePolicy().hasHeightForWidth());
        editServer->setSizePolicy(sizePolicy2);
        editServer->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(editServer, 1, 0, 1, 1);

        label_3 = new QLabel(NetMarker);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(0, 0));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 0, 2, 1, 1);

        btnHide = new QPushButton(NetMarker);
        btnHide->setObjectName(QStringLiteral("btnHide"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(2);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(btnHide->sizePolicy().hasHeightForWidth());
        btnHide->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(btnHide, 1, 3, 1, 1);

        editPort = new QLineEdit(NetMarker);
        editPort->setObjectName(QStringLiteral("editPort"));
        sizePolicy3.setHeightForWidth(editPort->sizePolicy().hasHeightForWidth());
        editPort->setSizePolicy(sizePolicy3);
        editPort->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(editPort, 1, 1, 1, 1);

        editEvent = new QLineEdit(NetMarker);
        editEvent->setObjectName(QStringLiteral("editEvent"));
        sizePolicy3.setHeightForWidth(editEvent->sizePolicy().hasHeightForWidth());
        editEvent->setSizePolicy(sizePolicy3);
        editEvent->setMinimumSize(QSize(0, 0));
        editEvent->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(editEvent, 1, 2, 1, 1);

        label_2 = new QLabel(NetMarker);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_21 = new QLabel(NetMarker);
        label_21->setObjectName(QStringLiteral("label_21"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(1);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
        label_21->setSizePolicy(sizePolicy4);
        label_21->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_21);

        btnSend = new QPushButton(NetMarker);
        btnSend->setObjectName(QStringLiteral("btnSend"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy5.setHorizontalStretch(1);
        sizePolicy5.setVerticalStretch(5);
        sizePolicy5.setHeightForWidth(btnSend->sizePolicy().hasHeightForWidth());
        btnSend->setSizePolicy(sizePolicy5);

        horizontalLayout->addWidget(btnSend);

        label_22 = new QLabel(NetMarker);
        label_22->setObjectName(QStringLiteral("label_22"));
        sizePolicy4.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
        label_22->setSizePolicy(sizePolicy4);
        label_22->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_22);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(NetMarker);

        QMetaObject::connectSlotsByName(NetMarker);
    } // setupUi

    void retranslateUi(QDialog *NetMarker)
    {
        NetMarker->setWindowTitle(QApplication::translate("NetMarker", "Dialog", Q_NULLPTR));
        label_1->setText(QApplication::translate("NetMarker", "ServerName", Q_NULLPTR));
        btnConnect->setText(QApplication::translate("NetMarker", "Connect", Q_NULLPTR));
        label_3->setText(QApplication::translate("NetMarker", "Event", Q_NULLPTR));
        btnHide->setText(QApplication::translate("NetMarker", "Hide", Q_NULLPTR));
        label_2->setText(QApplication::translate("NetMarker", "Port", Q_NULLPTR));
        label_21->setText(QString());
        btnSend->setText(QApplication::translate("NetMarker", "Send", Q_NULLPTR));
        label_22->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class NetMarker: public Ui_NetMarker {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETMARKER_H
