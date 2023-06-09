#pragma once

#include <QWidget>
#include <QtWidgets>
#include "ADE.h"

class EditCaseWindow : public QWidget
{
	Q_OBJECT

public:
	EditCaseWindow(int idAdmin, int id, int groupid, QString prof, QString salle, QString tableas, int hour, int hourFin, int minDebut, int minuteFin, QString date, QString tableat, ADE* mainWindowEditP, QWidget *parent = Q_NULLPTR);
	~EditCaseWindow();
	void getGroup();
	void getPlace();

public slots:
	void adding();
	void viewCalendar();
	void quitting();
	void getDate();
	void replyFinishedEdit(QNetworkReply* resp);

private:
	QLineEdit* editname;
	QComboBox* editgroupid;
	QComboBox* edithour;
	QComboBox* editHourFin;
	QComboBox* editMinDebut;
	QComboBox* editMinuteFin;
	QComboBox* editTeacher;
	QComboBox* editPlace;
	QLineEdit* edittype;
	QFormLayout* editlayout;
	QVBoxLayout* editcalendarLayout;
	QCalendarWidget* editcalendar;
	QPushButton* editcalandarButton;
	QString editdate;
	ADE* mainWindowEdit;
	QSoundEffect errorSoundEdit;
	QJsonArray tableaiCaseEdit;
	bool isCalendarOpenEdit;
	int groupid;
	int id;
	int idAdmin;
};
