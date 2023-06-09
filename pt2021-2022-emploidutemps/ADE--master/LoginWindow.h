#pragma once

#include <QWidget>
#include <QtWidgets>
#include <QtNetwork>
#include <QtMultimedia>

class LoginWindow : public QWidget
{
	Q_OBJECT

public:
	LoginWindow(QWidget *parent = Q_NULLPTR);
	void getGroup();
	~LoginWindow();


public slots:
	void connection();
	void replyFinished(QNetworkReply* resp);
	void createAccount();
	void replyFinishedCreate(QNetworkReply* resp);
	void replyFinishedGroups(QNetworkReply* resp);

private:
	QLineEdit* login;
	QLineEdit* password;
	QComboBox* groupidSelect;
	QVBoxLayout* textlayout;
	QLabel* notifyText;
	std::vector<int> groupids;
	QSoundEffect effect;
};
