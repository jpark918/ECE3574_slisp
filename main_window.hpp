#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <string>

#include <QWidget>
#include "message_widget.hpp"
#include "canvas_widget.hpp"
#include "repl_widget.hpp"
#include "interpreter_semantic_error.hpp"
#include "qt_interpreter.hpp"

//Jihoon Added
#include <QtWidgets>

class MainWindow: public QWidget{
  Q_OBJECT

public:

  MainWindow(QWidget * parent = nullptr);
  MainWindow(std::string filename, QWidget * parent = nullptr);

signals:
	void readfile(QString message);


public slots:
	void slot();

private:
	REPLWidget * replView;
	QtInterpreter  interpView;
	CanvasWidget* canvasView;
	MessageWidget* messageView;
};


#endif
