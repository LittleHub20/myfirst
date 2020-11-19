/********************************************************************************
** Form generated from reading UI file 'netactuator.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETACTUATOR_H
#define UI_NETACTUATOR_H

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
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NetActuator
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_1;
    QPushButton *btnConnect;
    QLineEdit *editServer;
    QLineEdit *editPort;
    QLabel *label_2;
    QLineEdit *editPrefix;
    QLabel *label_3;
    QPushButton *btnHide;
    QPlainTextEdit *editCommand;
    QHBoxLayout *horizontalLayout;
    QLabel *label_21;
    QPushButton *btnSend;
    QLabel *label_22;

    void setupUi(QDialog *NetActuator)
    {
        if (NetActuator->objectName().isEmpty())
            NetActuator->setObjectName(QStringLiteral("NetActuator"));
        NetActuator->resize(666, 400);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/resources/netactuator.png"), QSize(), QIcon::Normal, QIcon::Off);
        NetActuator->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(NetActuator);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_1 = new QLabel(NetActuator);
        label_1->setObjectName(QStringLiteral("label_1"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(2);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_1->sizePolicy().hasHeightForWidth());
        label_1->setSizePolicy(sizePolicy);
        label_1->setMinimumSize(QSize(0, 0));
        label_1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_1, 0, 0, 1, 1);

        btnConnect = new QPushButton(NetActuator);
        btnConnect->setObjectName(QStringLiteral("btnConnect"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(btnConnect->sizePolicy().hasHeightForWidth());
        btnConnect->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnConnect, 0, 3, 1, 1);

        editServer = new QLineEdit(NetActuator);
        editServer->setObjectName(QStringLiteral("editServer"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(2);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(editServer->sizePolicy().hasHeightForWidth());
        editServer->setSizePolicy(sizePolicy2);
        editServer->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(editServer, 1, 0, 1, 1);

        editPort = new QLineEdit(NetActuator);
        editPort->setObjectName(QStringLiteral("editPort"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(editPort->sizePolicy().hasHeightForWidth());
        editPort->setSizePolicy(sizePolicy3);
        editPort->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(editPort, 1, 1, 1, 1);

        label_2 = new QLabel(NetActuator);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(1);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy4);
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        editPrefix = new QLineEdit(NetActuator);
        editPrefix->setObjectName(QStringLiteral("editPrefix"));
        sizePolicy2.setHeightForWidth(editPrefix->sizePolicy().hasHeightForWidth());
        editPrefix->setSizePolicy(sizePolicy2);
        editPrefix->setMinimumSize(QSize(0, 0));
        editPrefix->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(editPrefix, 1, 2, 1, 1);

        label_3 = new QLabel(NetActuator);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(0, 0));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 0, 2, 1, 1);

        btnHide = new QPushButton(NetActuator);
        btnHide->setObjectName(QStringLiteral("btnHide"));
        sizePolicy1.setHeightForWidth(btnHide->sizePolicy().hasHeightForWidth());
        btnHide->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnHide, 1, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);

        editCommand = new QPlainTextEdit(NetActuator);
        editCommand->setObjectName(QStringLiteral("editCommand"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(4);
        sizePolicy5.setHeightForWidth(editCommand->sizePolicy().hasHeightForWidth());
        editCommand->setSizePolicy(sizePolicy5);

        verticalLayout->addWidget(editCommand);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_21 = new QLabel(NetActuator);
        label_21->setObjectName(QStringLiteral("label_21"));
        sizePolicy4.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
        label_21->setSizePolicy(sizePolicy4);
        label_21->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_21);

        btnSend = new QPushButton(NetActuator);
        btnSend->setObjectName(QStringLiteral("btnSend"));
        sizePolicy1.setHeightForWidth(btnSend->sizePolicy().hasHeightForWidth());
        btnSend->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(btnSend);

        label_22 = new QLabel(NetActuator);
        label_22->setObjectName(QStringLiteral("label_22"));
        sizePolicy4.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
        label_22->setSizePolicy(sizePolicy4);
        label_22->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_22);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(NetActuator);

        QMetaObject::connectSlotsByName(NetActuator);
    } // setupUi

    void retranslateUi(QDialog *NetActuator)
    {
        NetActuator->setWindowTitle(QApplication::translate("NetActuator", "Dialog", Q_NULLPTR));
        label_1->setText(QApplication::translate("NetActuator", "ServerName", Q_NULLPTR));
        btnConnect->setText(QApplication::translate("NetActuator", "Connect", Q_NULLPTR));
        label_2->setText(QApplication::translate("NetActuator", "Port", Q_NULLPTR));
        editPrefix->setText(QApplication::translate("NetActuator", "ID001CH", Q_NULLPTR));
        label_3->setText(QApplication::translate("NetActuator", "Prefix", Q_NULLPTR));
        btnHide->setText(QApplication::translate("NetActuator", "Hide", Q_NULLPTR));
        label_21->setText(QString());
        btnSend->setText(QApplication::translate("NetActuator", "Send", Q_NULLPTR));
        label_22->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class NetActuator: public Ui_NetActuator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETACTUATOR_H
