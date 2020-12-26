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

private:
  Ui::Texty *ui;
};
#endif // TEXTY_H
