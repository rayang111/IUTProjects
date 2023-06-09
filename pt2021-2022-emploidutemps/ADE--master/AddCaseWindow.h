#pragma once

#include <QWidget>
#include <QtWidgets>
#include "ADE.h"

class AddCaseWindow : public QWidget
{
	Q_OBJECT

public:
	AddCaseWindow(int hourP, int dayP, int idAdmin, int groupid, ADE* mainWindow,QWidget *parent = Q_NULLPTR);
	~AddCaseWindow();

	void getGroup();

	void getPlace();

public slots:
	void adding();
	void viewCalendar();
	void quiting();
	void getDate();

private:
	QLineEdit* name;
	QComboBox* hour;
	QComboBox* hourFin;
	QComboBox* minDebut;
	QComboBox* minuteFin;
	QComboBox* teacher;
	QLineEdit* type;
	QFormLayout* layout;
	QVBoxLayout* calendarLayout;
	QCalendarWidget* calendar;
	QPushButton* calandarButton;
	QJsonArray tableaiCase;
	QJsonArray tableaiCase2;
	QComboBox* place;
	QString date;
	ADE* mainWindow;
	QSoundEffect errorSoundAdd;
	int idAdmin;
	bool isCalendarOpen;
	int groupid;
};
