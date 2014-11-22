#ifndef CRITTERITEM_H
#define CRITTERITEM_H

#include <QGraphicsObject>
#include <QPainter>

class CritterItem : public QGraphicsObject {
  Q_OBJECT
private:
  QPen pen;
  QBrush brush;

public:
  CritterItem(QGraphicsItem *parent = 0);

  virtual QRectF boundingRect() const;
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*,
             QWidget*);
signals:

public slots:
  void death();
};

#endif // CRITTERITEM_H
