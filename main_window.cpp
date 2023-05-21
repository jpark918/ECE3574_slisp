#include "main_window.hpp"

#include <iostream>

#include <QLayout>

MainWindow::MainWindow(QWidget * parent): MainWindow("", parent){
  // TODO: your code here...

}

MainWindow::MainWindow(std::string filename, QWidget * parent): QWidget(parent){
  // TODO: your code here...

	messageView = new MessageWidget;
	canvasView = new CanvasWidget;
	replView = new REPLWidget;
	//interpView = new QtInterpreter;
	QGridLayout* layout = new QGridLayout;
	layout->addWidget(messageView, 0, 0);
	layout->addWidget(canvasView, 1, 0);
	layout->addWidget(replView, 2, 0);
	//send the line to parse
	//QObject::connect(replView, &REPLWidget::lineEntered, this, SLOT(slot())); //no need for params (based off of qt signals slots page)
	connect(replView, &REPLWidget::lineEntered, &interpView, &QtInterpreter::parseAndEvaluate);
	//QObject::connect(replView->getReplLineEdit(), SIGNAL(editingFinished()), this, SLOT(slot()));
	//QObject::connect(replView, SIGNAL(editingFinished()), this, SLOT(messageView->info())); //I want to test if I can send repl's QLineedit to message's QLineedit
	//QObject::connect(interpView, SIGNAL(interpView->error), this, SLOT()
	//messageView->getmessageLineEdit()->setText( replView->getReplLineEdit()->text()); //change messageline edit with the replLineEdit (This only works once, put it in Slot)
	//layout->addWidget(canavasView, 1, 0);
	//connect(replView, &REPLWidget::lineEntered, messageView, &MessageWidget::info); example connect

	connect(&interpView, &QtInterpreter::info, messageView, &MessageWidget::info); //from parse and evaluate to message info
	connect(&interpView, &QtInterpreter::error, messageView, &MessageWidget::error); //from parse and evaluate to message error

	connect(&interpView, &QtInterpreter::drawGraphic, canvasView, &CanvasWidget::addGraphic); //from parse and evaluate to canvas addGraphic

	connect(this, &MainWindow::readfile, &interpView, &QtInterpreter::parseAndEvaluate);

	QString fname = QString::fromStdString(filename);
	readfile(fname);

		//lineentered("asdf")
		//info("derp");
	setLayout(layout);
	setWindowTitle("Project 3");
}

//send it to parse and evaluate
void MainWindow::slot() {
	/*
	QLineEdit* temp = replView->getReplLineEdit();
	interpView->parseAndEvaluate(temp->text());
	*/
}