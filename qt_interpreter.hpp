#ifndef QT_INTERPRETER_HPP
#define QT_INTERPRETER_HPP

#include <string>

#include <QObject>
#include <QString>
#include <QGraphicsItem>

#include "interpreter.hpp"

class QtInterpreter: public QObject, private Interpreter{
Q_OBJECT

public:
// Default construct an QtInterpreter with the default environment and an empty AST
  QtInterpreter(QObject * parent = nullptr);

signals:
// a signal emitting a graphic to be drawn as a pointer
  void drawGraphic(QGraphicsItem * item);
 // a signal emitting an informational message
  void info(QString message);
 // a signal emitting an error message
  void error(QString message);

public slots:
// a public slot that accepts and expression string and parses/evaluates it
  void parseAndEvaluate(QString entry);

private:
	Interpreter interpol;
	bool parsecheck;

	void DecideDraw(Interpreter interpol);
	void slispinqt( Expression got);
};

#endif
