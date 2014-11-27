#ifndef SLEEP_H
#define SLEEP_H

#include <QThread>

class Sleep : public QThread {
public:
  static void msleep(unsigned long ms) {
    QThread::msleep(ms);
  }
};

#endif // SLEEP_H
