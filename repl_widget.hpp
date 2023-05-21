#ifndef REPL_WIDGET_HPP
#define REPL_WIDGET_HPP

#include <QWidget>
#include <QLineEdit>
#include <QString>
#include <QVector>

class REPLWidget: public QWidget{
Q_OBJECT

public:

  REPLWidget(QWidget * parent = nullptr);

  QLineEdit* getReplLineEdit();

signals:

  void lineEntered(QString entry);

private slots:

  void changed();

private:
	  QLineEdit* ReplLineEdit = new QLineEdit;
};

#endif
