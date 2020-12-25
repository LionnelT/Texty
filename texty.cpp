#include "texty.h"
#include "ui_texty.h"

Texty::Texty(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::Texty)
{
  ui->setupUi(this);
}

Texty::~Texty()
{
  delete ui;
}

