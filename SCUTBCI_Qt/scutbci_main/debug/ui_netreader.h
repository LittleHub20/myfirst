/********************************************************************************
** Form generated from reading UI file 'netreader.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETREADER_H
#define UI_NETREADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NetReader
{
public:
    QVBoxLayout *verticalLayout_1;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label_1;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_3;
    QLineEdit *editServer;
    QSpinBox *spinDuration;
    QPushButton *btnConnect;
    QLineEdit *editStatus;
    QPushButton *btnHide;
    QLineEdit *editPort;
    QSpinBox *spinScale;
    QTextEdit *editInstruction;

    void setupUi(QDialog *NetReader)
    {
        if (NetReader->objectName().isEmpty())
            NetReader->setObjectName(QStringLiteral("NetReader"));
        NetReader->resize(1024, 768);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NetReader->sizePolicy().hasHeightForWidth());
        NetReader->setSizePolicy(sizePolicy);
        NetReader->setMinimumSize(QSize(0, 0));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/resources/netreader.png"), QSize(), QIcon::Normal, QIcon::Off);
        NetReader->setWindowIcon(icon);
        verticalLayout_1 = new QVBoxLayout(NetReader);
        verticalLayout_1->setObjectName(QStringLiteral("verticalLayout_1"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new QLabel(NetReader);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        label_1 = new QLabel(NetReader);
        label_1->setObjectName(QStringLiteral("label_1"));
        sizePolicy.setHeightForWidth(label_1->sizePolicy().hasHeightForWidth());
        label_1->setSizePolicy(sizePolicy);
        label_1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_1, 0, 0, 1, 1);

        label_4 = new QLabel(NetReader);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_4, 0, 3, 1, 1);

        label_5 = new QLabel(NetReader);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setMinimumSize(QSize(0, 0));
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_5, 0, 4, 1, 1);

        label_3 = new QLabel(NetReader);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 0, 2, 1, 1);

        editServer = new QLineEdit(NetReader);
        editServer->setObjectName(QStringLiteral("editServer"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(3);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(editServer->sizePolicy().hasHeightForWidth());
        editServer->setSizePolicy(sizePolicy1);
        editServer->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(editServer, 1, 0, 1, 1);

        spinDuration = new QSpinBox(NetReader);
        spinDuration->setObjectName(QStringLiteral("spinDuration"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(2);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(spinDuration->sizePolicy().hasHeightForWidth());
        spinDuration->setSizePolicy(sizePolicy2);
        spinDuration->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(spinDuration, 1, 2, 1, 1);

        btnConnect = new QPushButton(NetReader);
        btnConnect->setObjectName(QStringLiteral("btnConnect"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(1);
        sizePolicy3.setHeightForWidth(btnConnect->sizePolicy().hasHeightForWidth());
        btnConnect->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(btnConnect, 0, 5, 1, 1);

        editStatus = new QLineEdit(NetReader);
        editStatus->setObjectName(QStringLiteral("editStatus"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(4);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(editStatus->sizePolicy().hasHeightForWidth());
        editStatus->setSizePolicy(sizePolicy4);
        editStatus->setMinimumSize(QSize(0, 0));
        editStatus->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(editStatus, 1, 4, 1, 1);

        btnHide = new QPushButton(NetReader);
        btnHide->setObjectName(QStringLiteral("btnHide"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy5.setHorizontalStretch(2);
        sizePolicy5.setVerticalStretch(1);
        sizePolicy5.setHeightForWidth(btnHide->sizePolicy().hasHeightForWidth());
        btnHide->setSizePolicy(sizePolicy5);

        gridLayout->addWidget(btnHide, 1, 5, 1, 1);

        editPort = new QLineEdit(NetReader);
        editPort->setObjectName(QStringLiteral("editPort"));
        sizePolicy2.setHeightForWidth(editPort->sizePolicy().hasHeightForWidth());
        editPort->setSizePolicy(sizePolicy2);
        editPort->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(editPort, 1, 1, 1, 1);

        spinScale = new QSpinBox(NetReader);
        spinScale->setObjectName(QStringLiteral("spinScale"));
        sizePolicy2.setHeightForWidth(spinScale->sizePolicy().hasHeightForWidth());
        spinScale->setSizePolicy(sizePolicy2);
        spinScale->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(spinScale, 1, 3, 1, 1);


        verticalLayout_1->addLayout(gridLayout);

        editInstruction = new QTextEdit(NetReader);
        editInstruction->setObjectName(QStringLiteral("editInstruction"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(8);
        sizePolicy6.setHeightForWidth(editInstruction->sizePolicy().hasHeightForWidth());
        editInstruction->setSizePolicy(sizePolicy6);

        verticalLayout_1->addWidget(editInstruction);


        retranslateUi(NetReader);

        QMetaObject::connectSlotsByName(NetReader);
    } // setupUi

    void retranslateUi(QDialog *NetReader)
    {
        NetReader->setWindowTitle(QApplication::translate("NetReader", "NetReader", Q_NULLPTR));
        label_2->setText(QApplication::translate("NetReader", "Port", Q_NULLPTR));
        label_1->setText(QApplication::translate("NetReader", "ServerName", Q_NULLPTR));
        label_4->setText(QApplication::translate("NetReader", "Scale(uV/chan)", Q_NULLPTR));
        label_5->setText(QApplication::translate("NetReader", "Status", Q_NULLPTR));
        label_3->setText(QApplication::translate("NetReader", "Duration(sec)", Q_NULLPTR));
        btnConnect->setText(QApplication::translate("NetReader", "Connect", Q_NULLPTR));
        btnHide->setText(QApplication::translate("NetReader", "Hide", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NetReader: public Ui_NetReader {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETREADER_H
