#include "repl_widget.hpp"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QLayout>
#include <QKeyEvent>

//Jihoon Added
#include "message_widget.hpp"

// Default construct a REPLWidget
REPLWidget::REPLWidget(QWidget * parent): QWidget(parent){
  // TODO: your code here

	// messageLineEdit = new QLineEdit;
	QLabel* realLabel = new QLabel("slisp> ");
	ReplLineEdit = new QLineEdit; //lets stuff to write on 
	ReplLineEdit->setFocus();
	//messageLineEdit->setReadOnly(true);

	connect(ReplLineEdit, SIGNAL(editingFinished()), this, SLOT(changed())); 
	//connect() 

	auto layout = new QHBoxLayout;
	layout->addWidget(realLabel, 0, 0); // (slisp> )
	layout->addWidget(ReplLineEdit);
	setLayout(layout);
}

void REPLWidget::changed() {
  // TODO: your code here
	//QString str = messageLineEdit->text();
	//realLabel->setText(str);

	//clear the repl 
	lineEntered(ReplLineEdit->text());
	ReplLineEdit->setText(""); //make it blank
}

QLineEdit* REPLWidget::getReplLineEdit() {

	return ReplLineEdit;
}

