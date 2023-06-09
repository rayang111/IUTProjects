#pragma once

#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include <QAbstractItemModel>

class FileExplorer : public QWidget
{
	Q_OBJECT

public:
	
	FileExplorer(QWidget *parent = Q_NULLPTR);
	~FileExplorer();

public slots:


private:
	QHBoxLayout* layouttree;
	QHBoxLayout* layout;
	QWidget* buttonlayout;


};
