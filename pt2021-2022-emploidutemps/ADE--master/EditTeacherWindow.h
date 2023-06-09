#pragma once

#include <QtWidgets>
#include <QtMultimedia>

class EditTeacherWindow : public QWidget
{
	Q_OBJECT

public:
	EditTeacherWindow(int idAdmin, QWidget *parent = Q_NULLPTR);
	~EditTeacherWindow();

	void getTeachers();


public slots:
	void adding();
	void replyFinished(QNetworkReply* resp);
	void quiting();


private:
	QLineEdit* teacherNameEdit;
	QComboBox* idTeacherEdit;
	QLineEdit* loginEdit;
	QLineEdit* pwdEdit;
	QJsonArray tableaiTeacherEdit;
	QLineEdit* newPwdEdit;
	QSoundEffect errorSoundEdit;
	int idAdmin;
};
