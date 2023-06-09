#pragma once

#include <QWidget>
#include <QtWidgets>
#include "ADE.h"

class RemoveGroupWindow : public QWidget
{
	Q_OBJECT

public:
	RemoveGroupWindow(int idAdmin, ADE* mainWindow, QWidget* parent = Q_NULLPTR);
	~RemoveGroupWindow();
	void getGroup();

public slots:
	void adding();
	void replyFinished(QNetworkReply* resp);
	void quiting();

private:
	QComboBox* grouplist;
	QFormLayout* layout;
	QSoundEffect errorSoundRemoveGroup;
	QJsonArray tableaiRemove;
	ADE* remgroupmainWindow;
	int idAdmin;
};

