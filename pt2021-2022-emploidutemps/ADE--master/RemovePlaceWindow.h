#pragma once

#include <QtWidgets>
#include <QtMultimedia>
#include <ADE.h>


class RemovePlaceWindow : public QWidget
{
	Q_OBJECT

public:
	RemovePlaceWindow(int idAdmin, ADE* mainWindow, QWidget *parent = Q_NULLPTR);
	~RemovePlaceWindow();
	void getGroup();

public slots:
	void adding();
	void replyFinished(QNetworkReply* resp);
	void quiting();

private:
	QComboBox* placelist;
	QFormLayout* layout;
	QSoundEffect errorSoundRemovePlace;
	QJsonArray tableaiRemove;
	ADE* remgroupmainWindow;
	int idAdmin;
};
