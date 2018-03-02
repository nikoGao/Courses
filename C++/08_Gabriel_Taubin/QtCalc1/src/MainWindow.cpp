#include "MainWindow.hpp"
#include "AboutDialog.hpp"

MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags): 
  QMainWindow(parent, flags) {
  // this line has to be the first thing here.  It creates the GUI
  // from the MainWindow.ui file stored the forms directory
  setupUi(this);
}

MainWindow::~MainWindow() {
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

// push-button actions
// Qt takes care of connecting signals to slots

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
  // get current expression
  QString qStr = displayTextEdit->toPlainText();

  // if (string == "") {
  //   set the display text to "-"
  // } else {
  //   if(last character of string == '+')
  //     replace last character by '-'
  //   else if(last character of string == '-')
  //     replace last character by '+'
  //   else
  //     append '-'
  // }

  // clear the display and show the edited expression
}

void MainWindow::on_clearButton_clicked() {
  displayTextEdit->clear();
  QString qStr = "<font color=\"black\"></font>";
  displayTextEdit->insertHtml(qStr);
}

void MainWindow::on_evaluateButton_clicked() {
  // get current expression
  QString qStr = displayTextEdit->toPlainText();

  // convert to C-style string
  // using QString::toLocal8Bit();
  // or
  // QString::toStdString();

  // create AlgebraicTreeExpression

  // if (parser fails to parse the current expression) {
  //
  //   get length of initial parsed substring
  //
  //   display the same expression with the initial
  //   parsed expression painted in black and the rest in red
  //
  //   use html to create a QString with the proper text and colors
  //   QTextEdit::insertHtml() to display the string
  //
  // } else /* if(parser succeeds) */ {
  //
  //   evaluate the expression
  //
  //   convert result to QString
  //   clear the display and display the result
  //  
  //   make sure that the result is displayed painted in black;
  //   neither red or in mixed colors
  // }

}
