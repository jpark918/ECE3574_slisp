#include "canvas_widget.hpp"

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLayout>

// Default construct a CanvasWidget
CanvasWidget::CanvasWidget(QWidget * parent): QWidget(parent){
  // TODO: your code here...
	
	//scene = new QGraphicsScene(this);

	//QWidget* window = new QWidget;
	//window->resize(300, 200);
	 
	auto layout = new QVBoxLayout;
	scene = new QGraphicsScene(this); //we need (this) for init test case to work
	QGraphicsView *view = new QGraphicsView(scene);
	//QGraphicsTextItem* text = scene->addText("Hello World");
	layout->addWidget(view);
	setLayout(layout);

	
	//QGraphicsRectItem* rectangle;
}
// A public slot that accepts a signal in the form of a QGraphicsItem pointer containing an
// object derived from QGraphicsItem to draw
void CanvasWidget::addGraphic(QGraphicsItem * item){
  // TODO: your code here...

	//QGraphicsView* view = new QGraphicsView(&scene);
	scene->addItem(item);
	//QGraphicsItem* text = scene->addText("Hello World");
	//item = scene->addText("Hello World");
}
//b