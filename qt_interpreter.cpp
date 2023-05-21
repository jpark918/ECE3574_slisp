#include "qt_interpreter.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <fstream>

#include <QBrush>
#include <QDebug>

#include "qgraphics_arc_item.hpp"

#include "interpreter_semantic_error.hpp"
#include <string.h>
#include <iomanip>

QtInterpreter::QtInterpreter(QObject* parent) : QObject(parent) {
	// TODO: your code here...
	interpol = Interpreter();
}

void QtInterpreter::parseAndEvaluate(QString entry) {
std::string hold = entry.toStdString();
	if (hold.size() >= 3) {
		if (hold.substr(hold.size() - 3, 3) == "slp") { //if it is a file
			std::ifstream ifs(hold);
			parsecheck = interpol.parse(ifs);
		}
		else {								//if it is normal proceudre line
			std::istringstream iss(hold);
			parsecheck = interpol.parse(iss);
		}
	}
	//parsecheck = interpol.parse(iss);
	if (!parsecheck) {
		//qDebug() << "failed parse";
		QString fail = "Error: Failure to Parse";
		error(fail); //this is the error signal in interpreter, there is another error slot in message_widget
	}
	else {
		//qDebug() << "passed parse";
		bool caught = false;
		Expression got;
		try {
			 got = interpol.eval();
		}
		catch (const InterpreterSemanticError& e) {
			//qDebug() << "InterpreterSemnaticError";
			QString fail = "Error: Failure to evaluate";
			error(fail); //this is the error signal in interpreter, there is another error slot in message_widget
			caught = true;
		}
		if (!interpol.getDraw().empty() && !caught) {		//this means that the vector graphics has been modified (aka draw)
			DecideDraw(interpol);
		}
		else if (got.head.type != NoneType && !caught) { //pulled from <<
			slispinqt( got);
		}
		else { //if it is a nonetype  //HELP why does it go here for QLineEdit (foo) and (fail) when it gives me semantic error in my unit tests?
			//qDebug() << "nonetype failure";
			QString fail = "Error: Failure to evaluate";
			error(fail); //this is the error signal in interpreter, there is another error slot in message_widget
		}	//std::string final = got.head.value.sym_value; //Note: I don't think the sym value is always available
	}
}

/// takes the interpreter object that called eval and the result of the eval, the Expression got
/// and draws onto the canvas.
void QtInterpreter:: DecideDraw(Interpreter interpol) { //is within 60 lines :D
	for (unsigned int i = 0; i < interpol.getDraw().size(); i++) {
		//if (got.head.type == NoneType) {
			if (interpol.getDraw()[i].head.type == PointType) {
				//qDebug() << "This is a point type";
				QGraphicsEllipseItem* s = new QGraphicsEllipseItem(interpol.getDraw()[i].head.value.point_value.x, interpol.getDraw()[i].head.value.point_value.y, 2, 2);
				drawGraphic(s);
				//info(""); //clear the messagewidget
			}
			else if (interpol.getDraw()[i].head.type == LineType) {
					//qDebug() << "This is a line type";
				QGraphicsLineItem* l = new QGraphicsLineItem(interpol.getDraw()[i].head.value.line_value.first.x, interpol.getDraw()[i].head.value.line_value.first.y,
					interpol.getDraw()[i].head.value.line_value.second.x, interpol.getDraw()[i].head.value.line_value.second.y);
				drawGraphic(l);
				//info(""); //clear the messagewidget
			}
			else if (interpol.getDraw()[i].head.type == ArcType) {
					//qDebug() << "This is an arc type";
				double changex = (interpol.getDraw()[i].head.value.arc_value.center.x - interpol.getDraw()[i].head.value.arc_value.start.x);
				double changey = (interpol.getDraw()[i].head.value.arc_value.center.y - interpol.getDraw()[i].head.value.arc_value.start.y);
				double widthhold = sqrt((changex*changex) + (changey*changey)) * 2;
				double heighthold = widthhold;
				double xhold = interpol.getDraw()[i].head.value.arc_value.center.x - (widthhold / 2);
				double yhold = interpol.getDraw()[i].head.value.arc_value.center.y - (heighthold / 2);
				//convertion to degrees from span
				double holdspan = interpol.getDraw()[i].head.value.arc_value.span;
				double degree = ((holdspan * 180) / atan2(0, -1)) * 16;
				//qreal startangle = ((atan2(yhold, xhold) * 180) / atan2(0, -1)) * 16;
				//double startangle = (((atan2((/*abs(*/interpol.getDraw()[i].head.value.arc_value.center.y - interpol.getDraw()[i].head.value.arc_value.start.y)) * 180) / atan2(0, -1)) * 16) /
				//	(/*abs(*/interpol.getDraw()[i].head.value.arc_value.center.x - interpol.getDraw()[i].head.value.arc_value.start.x);
				double startangle2 = ((atan2(changey, -changex)) / (atan2(0, -1))) *180 * 16;
				QGraphicsArcItem* a = new QGraphicsArcItem(xhold, yhold, heighthold, widthhold);
				a->setSpanAngle(degree);
				a->setStartAngle(startangle2);
				drawGraphic(a);
				//info("");
			}
		//}
	}
}

/*
* if the eval is not drawing, by checking if the interpol's graphic vector is empty
* then we are displaying a value into 
*/
void QtInterpreter::slispinqt( Expression got) {
	std::string store = "(";
	Atom a;
	a.value = got.head.value;
	if (got.head.type == SymbolType) {
		store = got.head.value.sym_value;
	}
	else if (got.head.type == NumberType) {
		//store = std::to_string(got.head.value.num_value); //HELP how to get rid of trailing 0's
		std::ostringstream oss;
		oss << std::setprecision(8) << std::noshowpoint << got.head.value.num_value;
		store.append(oss.str());
		store.append(")");
	}
	else { //Boolean() is default false
		if (got.head.value.bool_value) {
			store = "True";
		}
		else {
			store = "False";
		}
	}
	QString qstore = QString::fromStdString(store);
	info(qstore);
}