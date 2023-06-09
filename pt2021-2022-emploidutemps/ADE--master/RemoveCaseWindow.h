#pragma once

#include <QWidget>
#include <QtWidgets>
#include <QtNetwork>
#include "ADE.h"

class RemoveCaseWindow : public QWidget
{
	Q_OBJECT

public:
	RemoveCaseWindow(std::vector<QString> caseId, int groupid, ADE* mainWindowRemoveP,QWidget *parent = Q_NULLPTR);
	~RemoveCaseWindow();

public slots:
	void removing();
	void replyFinishedRemove(QNetworkReply* resp);
	void quitting();
	

private:
	std::vector<QString> caseId;
	ADE* mainWindowRemove;
	QSoundEffect errorSoundRemove;
	int groupid;
};
