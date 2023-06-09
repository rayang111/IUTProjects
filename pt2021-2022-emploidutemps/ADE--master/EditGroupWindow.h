#pragma once

#include <QtWidgets>
#include <QtMultimedia>

class EditGroupWindow : public QWidget
{
	Q_OBJECT

public:
	EditGroupWindow(int idAdmin, QWidget *parent = Q_NULLPTR);
	~EditGroupWindow();

	void getGroup();

public slots:
	void adding();
	void replyFinished(QNetworkReply* resp);
	void quiting();


private:
	QLineEdit* groupNameEdit;
	QLineEdit* groupLogin;
	QLineEdit* groupPwdEdit;
	QLineEdit* groupConfirmPwdEdit;
	QComboBox* group;
	QSoundEffect errorSoundEditGroup;
	QJsonArray tableaiEdit;
	int idAdmin;
};
