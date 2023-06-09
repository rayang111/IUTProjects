#pragma once

#include <QtWidgets>
#include <QtMultimedia>

class AddPlaceWindow : public QWidget
{
	Q_OBJECT

public:
	AddPlaceWindow(int idAdmin, QWidget *parent = Q_NULLPTR);
	~AddPlaceWindow();


public slots:
	void replyFinished(QNetworkReply* resp);
	void adding();
	void quiting();

private:
	QLineEdit* placeName;
	QSoundEffect errorSoundAddPlace;
	int idAdmin;
};
