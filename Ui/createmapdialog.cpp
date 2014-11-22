#include "createmapdialog.h"
#include "ui_createmapdialog.h"

CreateMapDialog::CreateMapDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::CreateMapDialog) {
  ui->setupUi(this);
}

CreateMapDialog::~CreateMapDialog() { delete ui; }

int CreateMapDialog::getHSize() const { return ui->hSize->value(); }

int CreateMapDialog::getVSize() const { return ui->vSize->value(); }
