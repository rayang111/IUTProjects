#include "EditCaseWindow.h"
#include "ADE.h"
#include <QtWidgets>
#include <QtNetwork>

/**
* Classe permetant l'édition d'un évènement (admin)
*/

/*
* Constructeur de la classe permetant de modifier un évènement
**/
EditCaseWindow::EditCaseWindow(int idAdmin, int id, int groupid, QString prof, QString salle, QString tableas, int hour, int hourFin, int minDebut, int minuteFin, QString date, QString tableat, ADE* mainWindowEditP, QWidget *parent)
	: QWidget(parent)
{
	editname = new QLineEdit;
	edithour = new QComboBox;
	editHourFin = new QComboBox;
	editMinDebut = new QComboBox;
	editMinuteFin = new QComboBox;
	editTeacher = new QComboBox;
	editPlace = new QComboBox;
	edittype = new QLineEdit;
	editcalendar = new QCalendarWidget;
	editcalandarButton = new QPushButton("Choisir une date", this);

	QPushButton* addButton = new QPushButton("Modifier", this);
	QPushButton* cancelButton = new QPushButton("Annuler", this);

	EditCaseWindow::idAdmin = idAdmin;
	EditCaseWindow::groupid = groupid;
	EditCaseWindow::id = id;


	for (int nb = 0; nb < 24; nb++) {
		edithour->addItem(QString::number(nb));
	}

	for (int nb = 0; nb < 59; nb++) {
		editMinDebut->addItem(QString::number(nb));
	}

	for (int nb = 0; nb < 23; nb++) {
		editHourFin->addItem(QString::number(nb));
	}

	for (int nb = 0; nb < 59; nb++) {
		editMinuteFin->addItem(QString::number(nb));
	}

	getGroup();

	for (int nb = 0; nb < tableaiCaseEdit.size(); nb++) {
		editTeacher->addItem(tableaiCaseEdit.at(nb)["nom"].toString());
		editTeacher->setItemData(nb, tableaiCaseEdit.at(nb)["id"].toString());
	}

	getPlace();

	for (int nb = 0; nb < tableaiCaseEdit.size(); nb++) {
		editPlace->addItem(tableaiCaseEdit.at(nb)["nom"].toString());
		editPlace->setItemData(nb, tableaiCaseEdit.at(nb)["id"].toString());
	}

	edithour->setCurrentIndex(hour);
	editname->setText(tableas);
	edittype->setText(tableat);
	editHourFin->setCurrentIndex(hourFin);
	editMinDebut->setCurrentIndex(minDebut);
	editMinuteFin->setCurrentIndex(minuteFin);
	editdate = date;
	if (date != "") {
		editcalandarButton->setText("Date selectionnee : " + editdate);
		editcalendar->setSelectedDate(QDate::fromString(editdate));
	}

	editlayout = new QFormLayout;
	QWidget* calandarArea = new QWidget;
	editcalendarLayout = new QVBoxLayout;
	editcalendarLayout->addWidget(editcalandarButton);
	editcalendar->setMinimumDate(QDate(1900, 1, 1));
	editcalendar->setMaximumDate(QDate(3000, 1, 1));
	editcalendar->setGridVisible(true);
	connect(editcalendar, SIGNAL(clicked(const QDate&)),
		this, SLOT(getDate()));
	editcalendarLayout->addWidget(editcalendar);
	editcalendar->setVisible(false);
	EditCaseWindow::isCalendarOpenEdit = false;
	calandarArea->setLayout(editcalendarLayout);
	QLabel* addText = new QLabel("Veuliez indiquer les informations a modifier pour cette evenement.");
	editlayout->addRow(addText);
	editlayout->addRow(tr("Nom"), editname);
	editlayout->addRow(calandarArea);
	editlayout->addRow(tr("Heure debut"), edithour);
	editlayout->addRow(tr("Heure fin"), editHourFin);
	editlayout->addRow(tr("Minute debut"), editMinDebut);
	editlayout->addRow(tr("Minute fin"), editMinuteFin);
	editlayout->addRow(tr("Professeur"), editTeacher);
	editlayout->addRow(tr("Salle"), editPlace);
	editlayout->addRow(tr("Type"), edittype);
	editlayout->addRow(addButton);
	editlayout->addRow(cancelButton);
	setLayout(editlayout);

	mainWindowEdit = mainWindowEditP;

	QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(quitting()));
	QObject::connect(addButton, SIGNAL(clicked()), this, SLOT(adding()));
	QObject::connect(editcalandarButton, SIGNAL(clicked()), this, SLOT(viewCalendar()));

	EditCaseWindow::setVisible(true);
	show();
}

EditCaseWindow::~EditCaseWindow()
{
}

/*
* Méthode permetant de fermer le formulaire d'édition d'évènement
**/
void EditCaseWindow::quitting() {
	EditCaseWindow::setVisible(false);
	delete this;
}

/*
* Méthode permetant d'obtenir un petit calendrier pour chosir une date
**/
void EditCaseWindow::viewCalendar() {
	if (EditCaseWindow::isCalendarOpenEdit == true) {
		EditCaseWindow::isCalendarOpenEdit = false;
		editcalendar->setVisible(false);
	} else{
		EditCaseWindow::isCalendarOpenEdit = true;
		editcalendar->setVisible(true);
	}
}

/*
* Méthode permetant d'obtenir tous les groupes depuis la base de données
**/
void EditCaseWindow::getGroup() {
	QNetworkAccessManager networkAccessManager;
	QNetworkRequest networkRequest(QUrl(QString("https://dwarves.iut-fbleau.fr/~barbey/EDT/script1.php?getprof=true&idadmin=" + QString::number(idAdmin))));
	QNetworkReply* networkReply = networkAccessManager.get(networkRequest);
	QEventLoop eventLoop;
	QObject::connect(networkReply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
	eventLoop.exec();
	QVariant status_code = networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	if (status_code.isValid()) {
		QJsonParseError jsonError;
		QByteArray rep = networkReply->readAll();
		QJsonDocument json = QJsonDocument::fromJson(rep, &jsonError);
		if (jsonError.error != QJsonParseError::NoError) {
			qDebug() << "Error: " << jsonError.errorString();
			QErrorMessage* errorMsg = new QErrorMessage(this);
			errorSoundEdit.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundEdit.setVolume(0.25f);
			errorSoundEdit.play();
			qDebug() << errorSoundEdit.status();
			errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
		}

		QJsonValue groups = json.object().value("prof");
		tableaiCaseEdit = groups.toArray();
	}
	else {
		QErrorMessage* errorMsg = new QErrorMessage(this);
		errorSoundEdit.setSource(QUrl::fromLocalFile("error.wav"));
		errorSoundEdit.setVolume(0.25f);
		errorSoundEdit.play();
		errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
	}
}

/*
* Méthode permetant d'obtenir tous les lieux depuis la base de données
**/
void EditCaseWindow::getPlace() {
	QNetworkAccessManager networkAccessManager;
	QNetworkRequest networkRequest(QUrl(QString("https://dwarves.iut-fbleau.fr/~barbey/EDT/script1.php?getsalle=true&idadmin=" + QString::number(idAdmin))));
	QNetworkReply* networkReply = networkAccessManager.get(networkRequest);
	QEventLoop eventLoop;
	QObject::connect(networkReply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
	eventLoop.exec();
	QVariant status_code = networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	if (status_code.isValid()) {
		QJsonParseError jsonError;
		QByteArray rep = networkReply->readAll();
		QJsonDocument json = QJsonDocument::fromJson(rep, &jsonError);
		if (jsonError.error != QJsonParseError::NoError) {
			qDebug() << "Error: " << jsonError.errorString();
			QErrorMessage* errorMsg = new QErrorMessage(this);
			errorSoundEdit.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundEdit.setVolume(0.25f);
			errorSoundEdit.play();
			qDebug() << errorSoundEdit.status();
			errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
		}

		QJsonValue groups = json.object().value("salle");
		tableaiCaseEdit = groups.toArray();
	}
	else {
		QErrorMessage* errorMsg = new QErrorMessage(this);
		errorSoundEdit.setSource(QUrl::fromLocalFile("error.wav"));
		errorSoundEdit.setVolume(0.25f);
		errorSoundEdit.play();
		errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
	}
}

/*
* Méthode permetant d'obtenir la date sélectionnée depuis le calendrier
**/
void EditCaseWindow::getDate() {
	editdate = editcalendar->selectedDate().toString("yyyy/MM/dd");
	editcalandarButton->setText("Date selectionnee : " + editdate);
	EditCaseWindow::isCalendarOpenEdit = false;
	editcalendar->setVisible(false);
}


/*
* Méthode permetant de modifier l'évènement dans la base de données
**/
void EditCaseWindow::adding() {
	if (editname->text() != "" && edittype->text() != "" && editdate != "" && !(editMinDebut->itemText(editMinDebut->currentIndex()) == "0" && editMinuteFin->itemText(editMinuteFin->currentIndex()) == "0")) {
		QNetworkAccessManager networkAccessManager;
		QString actualHourValue = edithour->itemText(edithour->currentIndex());
		QString actualHourFin = editHourFin->itemText(editHourFin->currentIndex());
		QString actualMinDebut = editMinDebut->itemText(editMinDebut->currentIndex());
		QString actualMinuteFin = editMinuteFin->itemText(editMinuteFin->currentIndex());
		QNetworkAccessManager* manager = new QNetworkAccessManager(this);
		QHttpMultiPart* http = new QHttpMultiPart(QHttpMultiPart::FormDataType);

		QHttpPart receiptPart;
		receiptPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"editcase\""));
		receiptPart.setBody("true");

		QHttpPart receiptPart1;
		receiptPart1.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"id\""));
		receiptPart1.setBody(QString::number(id).toUtf8());

		QHttpPart receiptPart2;
		receiptPart2.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"groupid\""));
		receiptPart2.setBody(QString::number(groupid).toUtf8());

		QHttpPart receiptPart3;
		receiptPart3.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"subject\""));
		receiptPart3.setBody(editname->text().toUtf8());

		QHttpPart receiptPart4;
		receiptPart4.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"date\""));
		receiptPart4.setBody(editcalendar->selectedDate().toString("yyyy-MM-dd").toUtf8());

		QHttpPart receiptPart5;
		receiptPart5.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"hourdebut\""));
		receiptPart5.setBody(actualHourValue.toUtf8());

		QHttpPart receiptPart6;
		receiptPart6.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"hourfin\""));
		receiptPart6.setBody(actualHourFin.toUtf8());

		QHttpPart receiptPart7;
		receiptPart7.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"mindebut\""));
		receiptPart7.setBody(actualMinDebut.toUtf8());

		QHttpPart receiptPart8;
		receiptPart8.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"minutefin\""));
		receiptPart8.setBody(actualMinuteFin.toUtf8());

		QHttpPart receiptPart9;
		receiptPart9.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"type\""));
		receiptPart9.setBody(edittype->text().toUtf8());

		QHttpPart receiptPart10;
		receiptPart10.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"idprof\""));
		receiptPart10.setBody(editTeacher->itemData(editTeacher->currentIndex()).toString().toUtf8());

		QHttpPart receiptPart11;
		receiptPart11.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"idlieu\""));
		receiptPart11.setBody(editPlace->itemData(editPlace->currentIndex()).toString().toUtf8());

		http->append(receiptPart);
		http->append(receiptPart2);
		http->append(receiptPart3);
		http->append(receiptPart4);
		http->append(receiptPart5);
		http->append(receiptPart6);
		http->append(receiptPart7);
		http->append(receiptPart8);
		http->append(receiptPart9);
		http->append(receiptPart10);
		http->append(receiptPart11);


		QNetworkReply* repl = manager->post(QNetworkRequest(QUrl("https://dwarves.iut-fbleau.fr/~barbey/EDT/script1.php")), http);
		connect(manager, SIGNAL(finished(QNetworkReply*)),
			this, SLOT(replyFinishedEdit(QNetworkReply*)));
	} else {
		QErrorMessage* errorMsg = new QErrorMessage(this);
		if (editname->text() == "") {
			errorSoundEdit.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundEdit.setVolume(0.25f);
			errorSoundEdit.play();
			errorMsg->showMessage(tr("Erreur le nom doit etre donne"));
		}
		if (edittype->text() == "") {
			errorSoundEdit.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundEdit.setVolume(0.25f);
			errorSoundEdit.play();
			errorMsg->showMessage(tr("Erreur un type doit etre donne"));
		}
		if (editdate == "") {
			errorSoundEdit.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundEdit.setVolume(0.25f);
			errorSoundEdit.play();
			errorMsg->showMessage(tr("Erreur une date doit etre choisie"));
		}
		if ((editMinDebut->itemText(editMinDebut->currentIndex()) == "0" && editMinuteFin->itemText(editMinuteFin->currentIndex()) == "0")) {
			errorSoundEdit.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundEdit.setVolume(0.25f);
			errorSoundEdit.play();
			errorMsg->showMessage(tr("Erreur la minute du debut et celle de fin ne peuvent valoir tous deux 0"));
		}
	}

}

/*
* Méthode SLOT permetant de réactualiser la grille et de quitter l'éditon de l'évènement si la requête vers la base de données a aboutie
**/
void EditCaseWindow::replyFinishedEdit(QNetworkReply* resp) {
	QVariant status_code = resp->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	if (status_code.isValid()) {
		QString status = status_code.toString();
		qDebug() << status;
		QByteArray data = resp->readAll();
		qDebug() << data;
		QDate currentDate = QDateTime::currentDateTime().date();
		int todayDate = QDateTime::currentDateTime().date().dayOfWeek();
		if (todayDate != 1) {
			currentDate.setDate(currentDate.year(), currentDate.month(), ((currentDate.day() + 1) - todayDate));
		}
		mainWindowEdit->loadCalendar(1, groupid,currentDate);
		EditCaseWindow::setVisible(false);
	}
	else {
		QErrorMessage* errorMsg = new QErrorMessage(this);
		errorSoundEdit.setSource(QUrl::fromLocalFile("error.wav"));
		errorSoundEdit.setVolume(0.25f);
		errorSoundEdit.play();
		errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
	}
}