#ifndef MENU_PRINCIPAL_H
#define MENU_PRINCIPAL_H

#include <QWidget>
#include <QPixmap>
#include <QSharedPointer>
#include <QPainter>
#include <QDir>
#include <QTimer>
#include <QElapsedTimer>
#include <QResizeEvent>
#include <QPropertyAnimation>
#include <iostream>
#include <algorithm>

using namespace std;

class Reticule : public QWidget
{
	Q_OBJECT
public:

	Reticule(QWidget* parent = nullptr);
	~Reticule();

private:

	QPixmap image;



};




#endif
