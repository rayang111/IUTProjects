#pragma once

#include <QtWidgets>
#include <QtMultimedia>

class AddTeacherWindow : public QWidget
{
	Q_OBJECT

public:
	AddTeacherWindow(int idAdmin,QWidget *parent = Q_NULLPTR);
	~AddTeacherWindow();


public slots:
	void quiting();
	void adding();
	void replyFinished(QNetworkReply* resp);


private:
	QLineEdit* teacherName;
	QLineEdit* login;
	QLineEdit* pwd;
	QLineEdit* confirmPwd;
	QSoundEffect errorSoundAdd;
	int idAdmin;

};
