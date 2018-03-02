/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *about_action;
    QWidget *centralwidget;
    QTextEdit *displayTextEdit;
    QPushButton *firstExprButton;
    QPushButton *leftParenButton;
    QPushButton *rightParenButton;
    QPushButton *clearButton;
    QPushButton *divideButton;
    QPushButton *prevExprButton;
    QPushButton *number7Button;
    QPushButton *number8Button;
    QPushButton *number9Button;
    QPushButton *multiplyButton;
    QPushButton *nextExprButton;
    QPushButton *number4Button;
    QPushButton *number5Button;
    QPushButton *number6Button;
    QPushButton *subtractButton;
    QPushButton *lastExprButton;
    QPushButton *number1Button;
    QPushButton *number2Button;
    QPushButton *number3Button;
    QPushButton *addButton;
    QPushButton *delExprButton;
    QPushButton *changeSignButton;
    QPushButton *number0Button;
    QPushButton *decimalPointButton;
    QPushButton *evaluateButton;
    QMenuBar *menubar;
    QMenu *menuHelp;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(500, 600);
        about_action = new QAction(MainWindow);
        about_action->setObjectName(QStringLiteral("about_action"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        displayTextEdit = new QTextEdit(centralwidget);
        displayTextEdit->setObjectName(QStringLiteral("displayTextEdit"));
        displayTextEdit->setGeometry(QRect(6, 6, 488, 88));
        QFont font;
        font.setPointSize(36);
        displayTextEdit->setFont(font);
        displayTextEdit->setAlignment(Qt::AlignCenter);
        firstExprButton = new QPushButton(centralwidget);
        firstExprButton->setObjectName(QStringLiteral("firstExprButton"));
        firstExprButton->setGeometry(QRect(0, 100, 100, 100));
        firstExprButton->setFont(font);
        leftParenButton = new QPushButton(centralwidget);
        leftParenButton->setObjectName(QStringLiteral("leftParenButton"));
        leftParenButton->setGeometry(QRect(100, 100, 100, 100));
        leftParenButton->setFont(font);
        rightParenButton = new QPushButton(centralwidget);
        rightParenButton->setObjectName(QStringLiteral("rightParenButton"));
        rightParenButton->setGeometry(QRect(200, 100, 100, 100));
        rightParenButton->setFont(font);
        clearButton = new QPushButton(centralwidget);
        clearButton->setObjectName(QStringLiteral("clearButton"));
        clearButton->setGeometry(QRect(300, 100, 100, 100));
        clearButton->setFont(font);
        divideButton = new QPushButton(centralwidget);
        divideButton->setObjectName(QStringLiteral("divideButton"));
        divideButton->setGeometry(QRect(400, 100, 100, 100));
        divideButton->setFont(font);
        prevExprButton = new QPushButton(centralwidget);
        prevExprButton->setObjectName(QStringLiteral("prevExprButton"));
        prevExprButton->setGeometry(QRect(0, 200, 100, 100));
        prevExprButton->setFont(font);
        number7Button = new QPushButton(centralwidget);
        number7Button->setObjectName(QStringLiteral("number7Button"));
        number7Button->setGeometry(QRect(100, 200, 100, 100));
        number7Button->setFont(font);
        number8Button = new QPushButton(centralwidget);
        number8Button->setObjectName(QStringLiteral("number8Button"));
        number8Button->setGeometry(QRect(200, 200, 100, 100));
        number8Button->setFont(font);
        number9Button = new QPushButton(centralwidget);
        number9Button->setObjectName(QStringLiteral("number9Button"));
        number9Button->setGeometry(QRect(300, 200, 100, 100));
        number9Button->setFont(font);
        multiplyButton = new QPushButton(centralwidget);
        multiplyButton->setObjectName(QStringLiteral("multiplyButton"));
        multiplyButton->setGeometry(QRect(400, 200, 100, 100));
        multiplyButton->setFont(font);
        nextExprButton = new QPushButton(centralwidget);
        nextExprButton->setObjectName(QStringLiteral("nextExprButton"));
        nextExprButton->setGeometry(QRect(0, 300, 100, 100));
        nextExprButton->setFont(font);
        number4Button = new QPushButton(centralwidget);
        number4Button->setObjectName(QStringLiteral("number4Button"));
        number4Button->setGeometry(QRect(100, 300, 100, 100));
        number4Button->setFont(font);
        number5Button = new QPushButton(centralwidget);
        number5Button->setObjectName(QStringLiteral("number5Button"));
        number5Button->setGeometry(QRect(200, 300, 100, 100));
        number5Button->setFont(font);
        number6Button = new QPushButton(centralwidget);
        number6Button->setObjectName(QStringLiteral("number6Button"));
        number6Button->setGeometry(QRect(300, 300, 100, 100));
        number6Button->setFont(font);
        subtractButton = new QPushButton(centralwidget);
        subtractButton->setObjectName(QStringLiteral("subtractButton"));
        subtractButton->setGeometry(QRect(400, 300, 100, 100));
        subtractButton->setFont(font);
        lastExprButton = new QPushButton(centralwidget);
        lastExprButton->setObjectName(QStringLiteral("lastExprButton"));
        lastExprButton->setGeometry(QRect(0, 400, 100, 100));
        lastExprButton->setFont(font);
        number1Button = new QPushButton(centralwidget);
        number1Button->setObjectName(QStringLiteral("number1Button"));
        number1Button->setGeometry(QRect(100, 400, 100, 100));
        number1Button->setFont(font);
        number2Button = new QPushButton(centralwidget);
        number2Button->setObjectName(QStringLiteral("number2Button"));
        number2Button->setGeometry(QRect(200, 400, 100, 100));
        number2Button->setFont(font);
        number3Button = new QPushButton(centralwidget);
        number3Button->setObjectName(QStringLiteral("number3Button"));
        number3Button->setGeometry(QRect(300, 400, 100, 100));
        number3Button->setFont(font);
        addButton = new QPushButton(centralwidget);
        addButton->setObjectName(QStringLiteral("addButton"));
        addButton->setGeometry(QRect(400, 400, 100, 100));
        addButton->setFont(font);
        delExprButton = new QPushButton(centralwidget);
        delExprButton->setObjectName(QStringLiteral("delExprButton"));
        delExprButton->setGeometry(QRect(0, 500, 100, 100));
        delExprButton->setFont(font);
        changeSignButton = new QPushButton(centralwidget);
        changeSignButton->setObjectName(QStringLiteral("changeSignButton"));
        changeSignButton->setGeometry(QRect(100, 500, 100, 100));
        changeSignButton->setFont(font);
        number0Button = new QPushButton(centralwidget);
        number0Button->setObjectName(QStringLiteral("number0Button"));
        number0Button->setGeometry(QRect(200, 500, 100, 100));
        number0Button->setFont(font);
        decimalPointButton = new QPushButton(centralwidget);
        decimalPointButton->setObjectName(QStringLiteral("decimalPointButton"));
        decimalPointButton->setGeometry(QRect(300, 500, 100, 100));
        decimalPointButton->setFont(font);
        evaluateButton = new QPushButton(centralwidget);
        evaluateButton->setObjectName(QStringLiteral("evaluateButton"));
        evaluateButton->setGeometry(QRect(400, 500, 100, 100));
        evaluateButton->setFont(font);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 500, 22));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuHelp->menuAction());
        menuHelp->addAction(about_action);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ENGN2912B 2017 | QtCalc2", nullptr));
        about_action->setText(QApplication::translate("MainWindow", "About...", nullptr));
        displayTextEdit->setText(QString());
        firstExprButton->setText(QApplication::translate("MainWindow", "F", nullptr));
        leftParenButton->setText(QApplication::translate("MainWindow", "(", nullptr));
        rightParenButton->setText(QApplication::translate("MainWindow", ")", nullptr));
        clearButton->setText(QApplication::translate("MainWindow", "C", nullptr));
        divideButton->setText(QApplication::translate("MainWindow", "/", nullptr));
        prevExprButton->setText(QApplication::translate("MainWindow", "P", nullptr));
        number7Button->setText(QApplication::translate("MainWindow", "7", nullptr));
        number8Button->setText(QApplication::translate("MainWindow", "8", nullptr));
        number9Button->setText(QApplication::translate("MainWindow", "9", nullptr));
        multiplyButton->setText(QApplication::translate("MainWindow", "*", nullptr));
        nextExprButton->setText(QApplication::translate("MainWindow", "N", nullptr));
        number4Button->setText(QApplication::translate("MainWindow", "4", nullptr));
        number5Button->setText(QApplication::translate("MainWindow", "5", nullptr));
        number6Button->setText(QApplication::translate("MainWindow", "6", nullptr));
        subtractButton->setText(QApplication::translate("MainWindow", "-", nullptr));
        lastExprButton->setText(QApplication::translate("MainWindow", "L", nullptr));
        number1Button->setText(QApplication::translate("MainWindow", "1", nullptr));
        number2Button->setText(QApplication::translate("MainWindow", "2", nullptr));
        number3Button->setText(QApplication::translate("MainWindow", "3", nullptr));
        addButton->setText(QApplication::translate("MainWindow", "+", nullptr));
        delExprButton->setText(QApplication::translate("MainWindow", "D", nullptr));
        changeSignButton->setText(QApplication::translate("MainWindow", "+/-", nullptr));
        number0Button->setText(QApplication::translate("MainWindow", "0", nullptr));
        decimalPointButton->setText(QApplication::translate("MainWindow", ".", nullptr));
        evaluateButton->setText(QApplication::translate("MainWindow", "=", nullptr));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
