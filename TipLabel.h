#ifndef TIPLABEL_H
#define TIPLABEL_H

#include "qlabel.h"
#include <QObject>
#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>
#include <QWidget>

class TipLabel : public QFrame
{
    Q_OBJECT
public:
    explicit TipLabel(const QRect& geometry, QWidget* parent = nullptr);

    void setupAnimation();

signals:
};

#endif // TIPLABEL_H
