#ifndef TEXTY_H
#define TEXTY_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Texty; }
QT_END_NAMESPACE

class Texty : public QMainWindow
{
  Q_OBJECT

public:
  Texty(QWidget *parent = nullptr);
  ~Texty();

private slots:
  void on_actionExit_triggered();

  void on_actionSave_As_triggered();
  void saveFile();
  void clearScreen();
  void on_actionSave_triggered();

  void on_newDoc_triggered();

  void on_OpenDocument_triggered();

  void on_actionGmail_triggered();

  void on_actionAuthors_triggered();
  int textChanged();

  void closeEvent(QCloseEvent *event);

  void on_textEdit_textChanged();

private:
  Ui::Texty *ui;
  QString currentFile;
};
#endif // TEXTY_H
