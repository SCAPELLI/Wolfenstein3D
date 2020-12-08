#ifndef EDITOR_TILEMAP_H
#define EDITOR_TILEMAP_H

#include <QWidget>
#include <QtWidgets/QGraphicsView>

class Tilemap : public QGraphicsView {
    private:
        QGraphicsScene *scene;

    public:
        Tilemap(QWidget *parent = 0);
        ~Tilemap();

    private:
        void setGrid();

    protected:
        void mousePressEvent(QMouseEvent *event) override;
};


#endif //EDITOR_TILEMAP_H
