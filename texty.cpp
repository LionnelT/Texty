#include "texty.h"
#include "about.h"
#include "ui_texty.h"
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
Texty::Texty(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::Texty)
{
  ui->setupUi(this);
  this->setCentralWidget(ui->textEdit);
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
  currentFile.clear();
  ui->textEdit->setText(QString());

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
