#pragma once

#include <QtWidgets>
#include <QtMultimedia>

class AddGroupWindow : public QWidget
{
	Q_OBJECT

public:
	AddGroupWindow(int idAdmin, QWidget *parent = Q_NULLPTR);
	~AddGroupWindow();

public slots:
	void quiting();
	void replyFinished(QNetworkReply* resp);
	void adding();


private:
	QLineEdit* groupName;
	QLineEdit* groupLogin;
	QLineEdit* pwd;
	QLineEdit* confirmPwd;
	QSoundEffect errorSoundAdd;
	int idAdmin;
};
