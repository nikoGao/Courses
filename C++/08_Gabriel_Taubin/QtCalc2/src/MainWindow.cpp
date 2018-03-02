#include "MainWindow.hpp"
#include "AboutDialog.hpp"
#include "iostream"
#include "vector"
using namespace std;
// remember that if you add new variables to the class, you need to
// modify your constructors to initialize them

MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags):
QMainWindow(parent, flags) {
    // this line has to be the first thing here.  It creates the GUI
    // from the MainWindow.ui file stored in the forms directory
    setupUi(this);
    firstExprButton->setDisabled(true);
    prevExprButton->setDisabled(true);
    nextExprButton->setDisabled(true);
    lastExprButton->setDisabled(true);
    delExprButton->setDisabled(true);
}

MainWindow::~MainWindow() {
    //    for(int i = 0; i < expression_container.size(); i++)
    //    {
    //        delete expression_container.first();
    //    }
}

// menu bar actions

void MainWindow::on_quit_action_triggered() {
    close();
    QApplication::quit();
}

void MainWindow::on_about_action_triggered() {
    AboutDialog dialog(this);
    dialog.exec();
}

// buttons
void MainWindow::on_number0Button_clicked() {
    displayTextEdit->insertPlainText(QString("0"));
}

void MainWindow::on_number1Button_clicked() {
    displayTextEdit->insertPlainText(QString("1"));
}

void MainWindow::on_number2Button_clicked() {
    displayTextEdit->insertPlainText(QString("2"));
}

void MainWindow::on_number3Button_clicked() {
    displayTextEdit->insertPlainText(QString("3"));
}

void MainWindow::on_number4Button_clicked() {
    displayTextEdit->insertPlainText(QString("4"));
}

void MainWindow::on_number5Button_clicked() {
    displayTextEdit->insertPlainText(QString("5"));
}

void MainWindow::on_number6Button_clicked() {
    displayTextEdit->insertPlainText(QString("6"));
}

void MainWindow::on_number7Button_clicked() {
    displayTextEdit->insertPlainText(QString("7"));
}

void MainWindow::on_number8Button_clicked() {
    displayTextEdit->insertPlainText(QString("8"));
}

void MainWindow::on_number9Button_clicked() {
    displayTextEdit->insertPlainText(QString("9"));
}

void MainWindow::on_addButton_clicked() {
    displayTextEdit->insertPlainText(QString("+"));
}

void MainWindow::on_subtractButton_clicked() {
    displayTextEdit->insertPlainText(QString("-"));
}

void MainWindow::on_multiplyButton_clicked() {
    displayTextEdit->insertPlainText(QString("*"));
}

void MainWindow::on_divideButton_clicked() {
    displayTextEdit->insertPlainText(QString("/"));
}

void MainWindow::on_leftParenButton_clicked() {
    displayTextEdit->insertPlainText(QString("("));
}

void MainWindow::on_rightParenButton_clicked() {
    displayTextEdit->insertPlainText(QString(")"));
}

void MainWindow::on_decimalPointButton_clicked() {
    displayTextEdit->insertPlainText(QString("."));
}

void MainWindow::on_changeSignButton_clicked() {
    
    // get from you QtCalc1 implementation
    QString qStr = displayTextEdit->toPlainText();
    QString qStr1 = qStr.left(qStr.length() - 1);
    if (qStr == "") {
        displayTextEdit->insertPlainText(QString("-"));
    }else{
        if(qStr.at(qStr.size()-1) == QChar('+')){
            displayTextEdit->clear();
            displayTextEdit->insertPlainText(qStr1);//or use qStr.replace
            displayTextEdit->insertPlainText(QString('-'));
        }
        else if(qStr.at(qStr.size()-1) == QChar('-')){
            displayTextEdit->clear();
            displayTextEdit->insertPlainText(qStr1);
            displayTextEdit->insertPlainText(QString('+'));
        }
        else{
            /*qStr.at(0);
             this -> */displayTextEdit->insertPlainText(QString("-"));
        }
    }
}

void MainWindow::on_clearButton_clicked() {
    displayTextEdit->clear();
    std::string cStr = "2";
    QString toclear = QString::fromStdString(cStr);
    QString qStr = "<font color=\"black\">" +toclear+ "</font>";
    displayTextEdit->QTextEdit::insertHtml(qStr);
    displayTextEdit->clear();
}

unsigned expression_location = 0;

void MainWindow::on_evaluateButton_clicked() {
    
    // get from your QtCalc1 implementation, and modify so that:
    QString qStr = displayTextEdit->toPlainText();
    std::string cStr = qStr.toStdString();
    const char* exprStr = cStr.c_str();
    AlgebraicTreeExpression* expr = new AlgebraicTreeExpression(exprStr);
    unsigned parsed_length = 0;
    int i = 0, m = 0, n = 0;
    bool wrong = 0;
    for( i ; i< qStr.size() ; i++)
    {
        if(qStr.at(0) != QChar('(')){//not start with '('
            wrong = 1;
            displayTextEdit->clear();
            displayTextEdit->QTextEdit::insertHtml("<font color=\"red\">"+qStr+"</font>");
            break;
        }
        //two operation
        if(qStr.at(i) == QChar('+') || qStr.at(i) == QChar('-') ||qStr.at(i) == QChar('*') ||qStr.at(i) == QChar('/') ){
            if(qStr.at(i-1) == QChar('+') || qStr.at(i-1) == QChar('-') ||qStr.at(i-1) == QChar('*') ||qStr.at(i-1) == QChar('/')  ){
                parsed_length = i;
                std::string parse = cStr.substr(0, parsed_length);
                std::string notparse = cStr.substr(parsed_length, strlen(exprStr)-parsed_length);
                QString qparse = QString::fromStdString(parse);
                QString qnotparse = QString::fromStdString(notparse);
                QString qStr = "<font color=\"black\">"+qparse+"</font>"+"<font color=\"red\">"+qnotparse+"</font>";
                displayTextEdit->clear();
                displayTextEdit->QTextEdit::insertHtml(qStr);
                wrong = 1;
                break;
            }
        }
        if(qStr.at(i) == QChar('+') || qStr.at(i) == QChar('-') ||qStr.at(i) == QChar('*') ||qStr.at(i) == QChar('/') ||
           qStr.at(i) == QChar('1') || qStr.at(i) == QChar('2') ||qStr.at(i) == QChar('3') ||qStr.at(i) == QChar('4') ||
           qStr.at(i) == QChar('5') || qStr.at(i) == QChar('6') ||qStr.at(i) == QChar('7') ||qStr.at(i) == QChar('8') ||
           qStr.at(i) == QChar('9') || qStr.at(i) == QChar('(') ||qStr.at(i) == QChar(')')) {}
        else  //illegal character
        {   parsed_length = i + 1;
            std::string parse = cStr.substr(0, parsed_length);
            std::string notparse = cStr.substr(parsed_length, strlen(exprStr)-parsed_length);
            QString qparse = QString::fromStdString(parse);
            QString qnotparse = QString::fromStdString(notparse);
            QString qStr = "<font color=\"black\">"+qparse+"</font>"+"<font color=\"red\">"+qnotparse+"</font>";
            displayTextEdit->clear();
            displayTextEdit->QTextEdit::insertHtml(qStr);
            wrong = 1;
            break;
        }
        if(qStr.at(i) == QChar('(')){
            m++;
        }
        if(qStr.at(i) == QChar(')')){
            n++;
        }
        if(i == qStr.size() - 1 && m > n){//more '(' than ')'
            int k = 0;
            for(int j = 0;j < qStr.size(); j++)
            {
                if(qStr.at(j) == QChar('(')){
                    k++;
                }
                if(k == m - n + 1){
                    parsed_length = j;
                    std::string parse = cStr.substr(0, parsed_length);
                    std::string notparse = cStr.substr(parsed_length, strlen(exprStr)-parsed_length);
                    QString qparse = QString::fromStdString(parse);
                    QString qnotparse = QString::fromStdString(notparse);
                    QString qStr = "<font color=\"black\">"+qparse+"</font>"+"<font color=\"red\">"+qnotparse+"</font>";
                    displayTextEdit->clear();
                    displayTextEdit->QTextEdit::insertHtml(qStr);
                    wrong = 1;
                    break;
                }
            }
        }
        if(i == qStr.size() - 1 && m < n){//more ')' than '('
            int k = 0;
            for(int j = 0 ; j < qStr.size() ; j++)
            {
                if(qStr.at(j) == QChar(')')){
                    k++;
                }
                if(k == m){
                    parsed_length = j + 1;
                    std::string parse = cStr.substr(0, parsed_length);
                    std::string notparse = cStr.substr(parsed_length, strlen(exprStr)-parsed_length);
                    QString qparse = QString::fromStdString(parse);
                    QString qnotparse = QString::fromStdString(notparse);
                    QString qStr = "<font color=\"black\">"+qparse+"</font>"+"<font color=\"red\">"+qnotparse+"</font>";
                    displayTextEdit->clear();
                    displayTextEdit->QTextEdit::insertHtml(qStr);
                    wrong = 1;
                    break;
                }
            }
        }
        if(i == qStr.size() - 1 && wrong == 0 && m == n){//parsed successfully, calculate result
            char*  outStr = expr->toString();
            double result = expr->evaluate();
            displayTextEdit->clear();
            displayTextEdit->QTextEdit::insertHtml("<font color=\"black\">"+QString::number(result)+"</font>");
            bool bTemp = true;
            for(int i = 0;i < Expression_container.size();i++){
                if(!strcmp( Expression_container.at(i)->toString(),expr->toString())){
                    bTemp = false;
                    cout <<"duplicate expression"<<endl;
                }
            }
            if(bTemp){
                Expression_container.push_back(expr);
                ++expression_location;
                firstExprButton->setDisabled(false);
                prevExprButton->setDisabled(false);
                nextExprButton->setDisabled(false);
                lastExprButton->setDisabled(false);
            }
            delete [] outStr;
            delete expr;
            break;
        }
    }
    // - allocate the root node in the heap
    //   and save it in an appropriate container (vector, list, or set)
    //
    // - add buttons to retrieve first, previous, next, and last expression
    //
    // - add a button to remove the expressions shown in the display
    //   from the container
    //
    // - make sure that you don't save duplicate expressions in the container
    //
    // - buttons that operate on the stored expressions must be disabled
    //   the container is empty, and enabled when the container contains
    //   at least one expression
}

void MainWindow::on_firstExprButton_clicked() {
    AlgebraicTreeExpression* first_expr = Expression_container.first();
    expression_location = 0;
    char * outStr = first_expr->toString();
    QString myString = QString::fromUtf8(outStr);
    displayTextEdit->setPlainText(myString);
    delExprButton->setDisabled(false);
}

void MainWindow::on_prevExprButton_clicked() {
    if(expression_location == 0){
        expression_location = Expression_container.size() - 1;}
    else{
        expression_location--;}
    //    cout<<"expression_location at = "<<expression_location<<endl;
    AlgebraicTreeExpression* pre_expr = Expression_container.at(expression_location);
    char * outStr = pre_expr->toString();
    QString myString = QString::fromUtf8(outStr);
    displayTextEdit->setPlainText(myString);
    delExprButton->setDisabled(false);
}

void MainWindow::on_nextExprButton_clicked() {
    if(expression_location == Expression_container.size()-1)
        expression_location = 0;
    else
        ++expression_location;
    cout<<"expression_location at = "<<expression_location<<endl;
    
    AlgebraicTreeExpression* next_expr = Expression_container.at(expression_location);
    char * outStr = next_expr->toString();
    QString myString = QString::fromUtf8(outStr);
    displayTextEdit->setPlainText(myString);
    delExprButton->setDisabled(false);
}

void MainWindow::on_lastExprButton_clicked() {
    AlgebraicTreeExpression* last_expr = Expression_container.last();
    expression_location = Expression_container.size() - 1;
    char * outStr = last_expr->toString();
    QString myString = QString::fromUtf8(outStr);
    displayTextEdit->setPlainText(myString);
    delExprButton->setDisabled(false);
}

void MainWindow::on_delExprButton_clicked() {
    Expression_container.removeAt(expression_location);
    //    cout<<"expression_location at = "<<expression_location<<endl;
    displayTextEdit->clear();
    if(Expression_container.size()==0)
    {
        firstExprButton->setDisabled(true);
        prevExprButton->setDisabled(true);
        nextExprButton->setDisabled(true);
        lastExprButton->setDisabled(true);
        delExprButton->setDisabled(true);
    }
}

