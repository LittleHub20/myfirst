/********************************************************************************
** Form generated from reading UI file 'netpresenter.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETPRESENTER_H
#define UI_NETPRESENTER_H

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

class Ui_NetPresenter
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_1;
    QPushButton *btnConnect;
    QLineEdit *editServer;
    QLineEdit *editPort;
    QLabel *label_2;
    QLineEdit *editContent;
    QLabel *label_3;
    QPushButton *btnHide;
    QHBoxLayout *horizontalLayout;
    QLabel *label_21;
    QPushButton *btnSend;
    QLabel *label_22;

    void setupUi(QDialog *NetPresenter)
    {
        if (NetPresenter->objectName().isEmpty())
            NetPresenter->setObjectName(QStringLiteral("NetPresenter"));
        NetPresenter->resize(702, 147);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/resources/netpresenter.png"), QSize(), QIcon::Normal, QIcon::Off);
        NetPresenter->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(NetPresenter);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_1 = new QLabel(NetPresenter);
        label_1->setObjectName(QStringLiteral("label_1"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(2);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_1->sizePolicy().hasHeightForWidth());
        label_1->setSizePolicy(sizePolicy);
        label_1->setMinimumSize(QSize(0, 0));
        label_1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_1, 0, 0, 1, 1);

        btnConnect = new QPushButton(NetPresenter);
        btnConnect->setObjectName(QStringLiteral("btnConnect"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(btnConnect->sizePolicy().hasHeightForWidth());
        btnConnect->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnConnect, 0, 3, 1, 1);

        editServer = new QLineEdit(NetPresenter);
        editServer->setObjectName(QStringLiteral("editServer"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(2);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(editServer->sizePolicy().hasHeightForWidth());
        editServer->setSizePolicy(sizePolicy2);
        editServer->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(editServer, 1, 0, 1, 1);

        editPort = new QLineEdit(NetPresenter);
        editPort->setObjectName(QStringLiteral("editPort"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(editPort->sizePolicy().hasHeightForWidth());
        editPort->setSizePolicy(sizePolicy3);
        editPort->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(editPort, 1, 1, 1, 1);

        label_2 = new QLabel(NetPresenter);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(1);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy4);
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        editContent = new QLineEdit(NetPresenter);
        editContent->setObjectName(QStringLiteral("editContent"));
        sizePolicy2.setHeightForWidth(editContent->sizePolicy().hasHeightForWidth());
        editContent->setSizePolicy(sizePolicy2);
        editContent->setMinimumSize(QSize(0, 0));
        editContent->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(editContent, 1, 2, 1, 1);

        label_3 = new QLabel(NetPresenter);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(0, 0));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 0, 2, 1, 1);

        btnHide = new QPushButton(NetPresenter);
        btnHide->setObjectName(QStringLiteral("btnHide"));
        sizePolicy1.setHeightForWidth(btnHide->sizePolicy().hasHeightForWidth());
        btnHide->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnHide, 1, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_21 = new QLabel(NetPresenter);
        label_21->setObjectName(QStringLiteral("label_21"));
        sizePolicy4.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
        label_21->setSizePolicy(sizePolicy4);
        label_21->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_21);

        btnSend = new QPushButton(NetPresenter);
        btnSend->setObjectName(QStringLiteral("btnSend"));
        sizePolicy1.setHeightForWidth(btnSend->sizePolicy().hasHeightForWidth());
        btnSend->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(btnSend);

        label_22 = new QLabel(NetPresenter);
        label_22->setObjectName(QStringLiteral("label_22"));
        sizePolicy4.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
        label_22->setSizePolicy(sizePolicy4);
        label_22->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_22);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(NetPresenter);

        QMetaObject::connectSlotsByName(NetPresenter);
    } // setupUi

    void retranslateUi(QDialog *NetPresenter)
    {
        NetPresenter->setWindowTitle(QApplication::translate("NetPresenter", "Dialog", Q_NULLPTR));
        label_1->setText(QApplication::translate("NetPresenter", "ServerName", Q_NULLPTR));
        btnConnect->setText(QApplication::translate("NetPresenter", "Connect", Q_NULLPTR));
        label_2->setText(QApplication::translate("NetPresenter", "Port", Q_NULLPTR));
        editContent->setText(QString());
        label_3->setText(QApplication::translate("NetPresenter", "Content", Q_NULLPTR));
        btnHide->setText(QApplication::translate("NetPresenter", "Hide", Q_NULLPTR));
        label_21->setText(QString());
        btnSend->setText(QApplication::translate("NetPresenter", "Send", Q_NULLPTR));
        label_22->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class NetPresenter: public Ui_NetPresenter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETPRESENTER_H
