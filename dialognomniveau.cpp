#include "dialognomniveau.h"
#include "ui_dialognomniveau.h"

DialogNomNiveau::DialogNomNiveau(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNomNiveau)
{
    ui->setupUi(this);
}

DialogNomNiveau::~DialogNomNiveau()
{
    delete ui;
}

void DialogNomNiveau::on_buttonBox_accepted()
{
    emit accepted(ui->lineEdit_nom->text());
}
