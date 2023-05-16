#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QObject>
#include <QtGui>
#include <QTextCodec>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPainter>
#include <MKB/aliases.h>

struct Vertex {
    f32 x;
    f32 y;
};

class Shape {
protected:
    QList<Vertex> vertices;

public:
    virtual void draw(QPainter& painter) = 0;
    virtual ~Shape() = default;
    void rotate(f32 angle);
};

class Line : public Shape {
public:
    Line(Vertex const points[2]);
    virtual void draw(QPainter &painter) override;
};

class Rectangle : public Shape {
public:
    Rectangle(Vertex const points[4]);
    virtual void draw(QPainter &painter) override;
};

class Scene : public QWidget { Q_OBJECT
    Line line;
    Rectangle rectangle;
    s32 timerId;
    f32 angle;

protected:
    void paintEvent(QPaintEvent * event) override;
    void timerEvent(QTimerEvent * event) override;
    void showEvent(QShowEvent * event) override;
    void hideEvent(QHideEvent * event) override;

public:
    Scene(QWidget * parent);
};

class MainWindow : public QWidget { Q_OBJECT
    Scene scene;
    QTextCodec codec;
    QPushButton * exitButton;

public:
    MainWindow();
};

#endif // MAINWINDOW_HH
