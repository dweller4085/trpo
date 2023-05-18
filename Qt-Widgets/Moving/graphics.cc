#include <QVector>
#include <QLine>
#include <math.h>
#include "graphics.hh"

void Shape::rotate(f32 angle) {
    f32 const rotation_matrix [9] = {
        cos(angle),  sin(angle), 0.f,
        -sin(angle), cos(angle), 0.f,
        0.f,         0.f,        1.f
    };

    struct {
        f32 x {0.f};
        f32 y {0.f};
    } center;

    for (int i = 0; i < vertices.size(); i += 1) {
        center.x += vertices[i].x;
        center.y += vertices[i].y;
    }

    center.x /= vertices.size();
    center.y /= vertices.size();

    for (auto& vertex : vertices) {
        vertex = {
            vertex.x - center.x,
            vertex.y - center.y,
        };

        vertex = {
            vertex.x * rotation_matrix [0] + vertex.y * rotation_matrix [3] + 1.f * rotation_matrix [6],
            vertex.x * rotation_matrix [1] + vertex.y * rotation_matrix [4] + 1.f * rotation_matrix [7]
        };

        vertex = {
            vertex.x + center.x,
            vertex.y + center.y,
        };
    }
}

Line::Line(Vertex a, Vertex b): Shape {{a, b}} {}

Rectangle::Rectangle(Vertex a, Vertex b): Shape {{a, {a.x, b.y}, b, {b.x, a.y}}} {}

void Line::draw(QPainter& painter) {
    painter.drawLine(vertices[0].x, vertices[0].y, vertices[1].x, vertices[1].y);
}

void Rectangle::draw(QPainter& painter) {
    painter.drawLine(vertices[0].x, vertices[0].y, vertices[1].x, vertices[1].y);
    painter.drawLine(vertices[1].x, vertices[1].y, vertices[2].x, vertices[2].y);
    painter.drawLine(vertices[2].x, vertices[2].y, vertices[3].x, vertices[3].y);
    painter.drawLine(vertices[3].x, vertices[3].y, vertices[0].x, vertices[0].y);
}

Scene::Scene(QWidget * parent):
    QWidget {parent},
    line {{width/2.f - 80, height/2.f - 20}, {width/2.f - 20, height/2.f + 40}},
    rectangle {{width/2.f + 20, height/2.f - 40}, {width/2.f + 80, height/2.f + 40}},
    timerId {0},
    angle {0.f}
{
    QWidget::setFixedSize(QSize{width, height});
}

void Scene::showEvent(QShowEvent *) {
    timerId = QObject::startTimer(1);
}

void Scene::hideEvent(QHideEvent *) {
    QObject::killTimer(timerId);
    timerId = 0;
}

void Scene::timerEvent(QTimerEvent * event) {
    if (event->timerId() == timerId) {
        angle += Scene::angleIncrement;
        QWidget::update();
    } else {
        QWidget::timerEvent(event);
    }
}

void Scene::paintEvent(QPaintEvent *) {
    QPainter painter {this};
    painter.setPen(Qt::red);
    line.rotate(Scene::angleIncrement);
    rectangle.rotate(-Scene::angleIncrement);
    line.draw(painter);
    rectangle.draw(painter);
}
