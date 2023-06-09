#pragma once

#include <QtWidgets>
#include <QtMultimedia>

class EditPlaceWindow : public QWidget
{
	Q_OBJECT

public:
	EditPlaceWindow(int idAdmin, QWidget *parent = Q_NULLPTR);
	~EditPlaceWindow();

	void getPlace();

public slots:
	void adding();
	void replyFinished(QNetworkReply* resp);
	void quiting();


private:
	QLineEdit* placeNameEdit;
	QComboBox* places;
	QString oldName;
	QSoundEffect errorSoundEditPlace;
	QJsonArray tableai;
	int idAdmin;
};
