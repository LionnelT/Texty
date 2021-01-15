#include "texty.h"
#include "about.h"
#include "ui_texty.h"
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QStatusBar>
#include <QCloseEvent>
Texty::Texty(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::Texty)
{
  ui->setupUi(this);
  this->setCentralWidget(ui->textEdit);
  QStatusBar *bar = new QStatusBar(this); // created a new status bar object
  ui->statusbar->addWidget(bar);
  bar->showMessage(tr("Ready"));
  }

Texty::~Texty()
{
  delete ui;
}


void Texty::on_actionExit_triggered()
{
    qApp->quit();
}

void Texty::on_actionSave_As_triggered()
{
  saveFile();
}
void Texty::clearScreen()
{
  currentFile.clear();
  ui->textEdit->setText(QString());
}
void Texty::saveFile()
{
  QString fname;
  if(currentFile.isEmpty()){
       fname = QFileDialog::getSaveFileName(this,"Enter the name of the text File",".", "Text Files (*.txt)");
       currentFile = fname;
    } else {
      fname=currentFile;
    }

  QFile f(fname);
  if(!f.open( QIODevice::WriteOnly| QFile :: Text)){
      QMessageBox::warning(this, "Warning", "Cannot save File : " + f.errorString());
      return;
    }

  setWindowTitle(fname);
  QTextStream out(&f);
  QString text = ui->textEdit->toPlainText();
  out<< text;
  f.close();
}



void Texty::on_actionSave_triggered()
{
 saveFile();
}

void Texty::on_newDoc_triggered()
{
  if(ui->textEdit->document()->isEmpty())
    {
      clearScreen();

    }
  else
    {
      QMessageBox msgBox;
      msgBox.setText("Do you want to save the document first ?");
      msgBox.setStandardButtons(QMessageBox::Save| QMessageBox:: Discard | QMessageBox :: Cancel);
      msgBox.setDefaultButton(QMessageBox::Save);
     int ret = msgBox.exec();

     switch(ret){
       case QMessageBox::Save:
       saveFile();
       break;

       case QMessageBox::Discard:
         clearScreen();
         break;

       }

    }


}

void Texty::on_OpenDocument_triggered()
{
  QString fileName = QFileDialog::getOpenFileName(nullptr, "Open the file");
  QFile file(fileName);
  currentFile = fileName;
  if(!file.open(QIODevice::ReadOnly | QFile::Text)){
      QMessageBox::warning(this,"Warning", " Cannot open file: "+ file.errorString());
      return;
    }
  setWindowTitle(fileName);
  QTextStream in(&file);
  QString text = in.readAll();
  ui->textEdit->setText(text);
  file.close();
}

void Texty::on_actionGmail_triggered()
{
    QDesktopServices::openUrl(QUrl("https://mail.google.com/mail/u/0/#inbox?compose=new"));
}

void Texty::on_actionAuthors_triggered()
{

  about *hel = new about();;
  hel->show();
}

void Texty::closeEvent(QCloseEvent *event)
{
  if(ui->textEdit->document()->isEmpty())
    {
      clearScreen();

    }
  else
    {
      QMessageBox msgBox;
      msgBox.move(3400,100);
      msgBox.setIcon(QMessageBox::Warning);

      msgBox.setText("Do you want to save the document first, before you close ?");
      msgBox.setStandardButtons(QMessageBox::Save| QMessageBox:: Discard | QMessageBox :: Cancel);
      msgBox.setDefaultButton(QMessageBox::Save);
     int resBtn = msgBox.exec();

     if(resBtn==QMessageBox::Save){
       saveFile();
       event->accept();
       }
     else if(resBtn==QMessageBox::Discard)
       event->accept();
     else
       event->ignore();

    }

}
int Texty::textChanged()
{
   int  wordCount =  ui->textEdit->toPlainText().split(QRegExp("(\\s|\\n|\\r)+"),QString::SkipEmptyParts).count();


   return wordCount;
}



void Texty::on_textEdit_textChanged()
{
  QStatusBar *bar = new QStatusBar(); // created a new status bar object
  ui->statusbar->addPermanentWidget(bar);
  bar->showMessage("");
  bar->showMessage(QString::number(textChanged()));
}
