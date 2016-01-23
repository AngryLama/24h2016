#ifndef DIALOGNOMNIVEAU_H
#define DIALOGNOMNIVEAU_H

#include <QDialog>

namespace Ui {
class DialogNomNiveau;
}

class DialogNomNiveau : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNomNiveau(QWidget *parent = 0);
    ~DialogNomNiveau();

signals:
    void accepted(QString);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogNomNiveau *ui;
};

#endif // DIALOGNOMNIVEAU_H
