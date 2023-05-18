#ifndef GRAPHICS_HH
#define GRAPHICS_HH

#include <QPainter>
#include <QWidget>
#include <QObject>
#include <QTimerEvent>
#include <QPaintEvent>
#include <QShowEvent>
#include <QHideEvent>
#include "common.hh"

struct Vertex {
    f32 x;
    f32 y;
};

class Shape {
protected:
    QList<Vertex> vertices;

public:
    Shape(std::initializer_list<Vertex> il): vertices {il} {}
    virtual void draw(QPainter& painter) = 0;
    virtual ~Shape() = default;
    void rotate(f32 angle);
};

class Line : public Shape {
public:
    Line(Vertex a, Vertex b);
    virtual void draw(QPainter& painter) override;
};

class Rectangle : public Shape {
public:
    Rectangle(Vertex a, Vertex b);
    virtual void draw(QPainter& painter) override;
};

class Scene : public QWidget { Q_OBJECT
    Line line;
    Rectangle rectangle;
    s32 static constexpr width {300};
    s32 static constexpr height {200};
    s32 timerId;
    f32 angle;
    f32 static constexpr angleIncrement = 0.0005f;

protected:
    virtual void paintEvent(QPaintEvent *) override;
    virtual void timerEvent(QTimerEvent *) override;
    virtual void showEvent(QShowEvent *) override;
    virtual void hideEvent(QHideEvent *) override;

public:
    Scene(QWidget * parent);
};


#endif // GRAPHICS_HH
