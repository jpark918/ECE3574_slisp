#include "message_widget.hpp"

#include <QLabel>
#include <QLayout>
#include <QLineEdit>

//Jihoon added
#include "repl_widget.hpp"
#include <QDebug>

MessageWidget::MessageWidget(QWidget *parent) : QWidget(parent) {
  // TODO: your code here...
    messageLineEdit = new QLineEdit;
	QLabel* realLabel = new QLabel("Message: ");
	messageLineEdit->setFocus();
	messageLineEdit->setReadOnly(true);
	   
	//connect(REPLWidget::messageLineEdit, SIGNAL(editingFinished()), this, );

	auto layout = new QHBoxLayout;
	layout->addWidget(realLabel, 0, 0); // (Message: )
	layout->addWidget(messageLineEdit);
	setLayout(layout);
}

void MessageWidget::info(QString message) {
  // TODO: your code here...
	//qDebug() << "Sent from parse to message"; //called in main window
	QPalette palette;
	this->messageLineEdit->setPalette(palette);
	palette.setColor(QPalette::Base, Qt::white);
	this->messageLineEdit->setText(message);
}

void MessageWidget::error(QString message) {
  // TODO: your code here...
	//qDebug() << "error slot in message_widget.";
	this->messageLineEdit->setText(message);
	QPalette palette;
	palette.setColor(QPalette::Highlight, Qt::red);
	//palette->setColor(QPalette::HighlightedText, Qt::white);
	palette.highlight();
	this->messageLineEdit->setPalette(palette);
	this->messageLineEdit->selectAll();
}

//don't need to make this.
void MessageWidget::clear() {
  // TODO: your code here...
	/*
	QPalette palette;
	this->messageLineEdit->setPalette(palette);
	palette.setColor(QPalette::Base, Qt::white);
	*/
}

QLineEdit* MessageWidget::getmessageLineEdit() {
	return this->messageLineEdit;
}