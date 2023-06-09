#pragma once

#include <QtWidgets>
#include <QtMultimedia>
#include <ADE.h>

class RemoveTeacherWindow : public QWidget
{
	Q_OBJECT

public:
	RemoveTeacherWindow(int idAdmin, ADE* groupmainWindowP, QWidget *parent = Q_NULLPTR);
	~RemoveTeacherWindow();
	void getGroup();

public slots:
	void adding();
	void replyFinished(QNetworkReply* resp);
	void quiting();

private:
	QComboBox* teacherlist;
	QFormLayout* layout;
	QSoundEffect errorSoundRemoveTeacher;
	QJsonArray tableaiRemove;
	ADE* remgroupmainWindow;
	int idAdmin;
};
