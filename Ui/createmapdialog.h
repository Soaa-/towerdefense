#ifndef CREATEMAPDIALOG_H
#define CREATEMAPDIALOG_H

#include <QDialog>

namespace Ui {
class CreateMapDialog;
}

class CreateMapDialog : public QDialog
{
  Q_OBJECT

public:
  explicit CreateMapDialog(QWidget *parent = 0);
  ~CreateMapDialog();

  int getHSize() const;
  int getVSize() const;

private:
  Ui::CreateMapDialog *ui;
};

#endif // CREATEMAPDIALOG_H
