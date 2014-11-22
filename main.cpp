#include "Ui/tdmap.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  TdMap w;
  w.show();

  return a.exec();
}
