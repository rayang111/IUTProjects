#include "AddCaseWindow.h"
#include "ADE.h"
#include <QtWidgets>
#include <QtNetwork>

/**
* Classe permetant l'ajout d'un évenement (admin)
*/

/**
* Constructeur de la classe permetant l'ajout d'un évenement
*/
AddCaseWindow::AddCaseWindow(int hourP, int dayP, int idAdmin, int groupid, ADE* mainWindowP,QWidget *parent)
	: QWidget(parent)
{
	name = new QLineEdit;
	hour = new QComboBox;
	hourFin = new QComboBox;
	minDebut = new QComboBox;
	minuteFin = new QComboBox;
	teacher = new QComboBox;
	place = new QComboBox;
	type = new QLineEdit;
	calendar = new QCalendarWidget;
	AddCaseWindow::idAdmin = idAdmin;
	AddCaseWindow::groupid = groupid;
	calandarButton = new QPushButton(tr("Choisir une date"), this);

	QPushButton* addButton = new QPushButton(tr("Ajouter"), this);
	QPushButton* cancelButton = new QPushButton(tr("Annuler"), this);

	getGroup();
	getPlace();

	for (int nb = 0; nb < tableaiCase.size(); nb++) {
		teacher->addItem(tableaiCase.at(nb)["nom"].toString());
		teacher->setItemData(nb, tableaiCase.at(nb)["id"].toString());
	}

	for (int nb = 0; nb < tableaiCase2.size(); nb++) {
		place->addItem(tableaiCase2.at(nb)["nom"].toString());
		place->setItemData(nb, tableaiCase2.at(nb)["id"].toString());
	}

	for (int nb = 0; nb < 23; nb++) {
		hour->addItem(QString::number(nb));
	}

		hour->setCurrentIndex(0);

	for (int nb = 0; nb < 59; nb++) {
		if (nb % 5 == 0) {
			minDebut->addItem(QString::number(nb));
		}
	}

	for (int nb = 0; nb < 23; nb++) {
		hourFin->addItem(QString::number(nb));
	}

	for (int nb = 0; nb < 59; nb++) {
		if (nb % 5 == 0) {
			minuteFin->addItem(QString::number(nb));
		}
	}

	layout = new QFormLayout;
	QWidget* calandarArea = new QWidget;
	calendarLayout = new QVBoxLayout;
	calendarLayout->addWidget(calandarButton);
	AddCaseWindow::isCalendarOpen = false;
	calendar->setMinimumDate(QDate(1900, 1, 1));
	calendar->setMaximumDate(QDate(3000, 1, 1));
	calendar->setGridVisible(false);
	connect(calendar, SIGNAL(clicked(const QDate&)),
		this, SLOT(getDate()));
	calendarLayout->addWidget(calendar);
	calendar->setVisible(false);
	calandarArea->setLayout(calendarLayout);
	QLabel* addText = new QLabel(tr("Veulliez indiquer ces informations pour creer un evenement."));
	layout->addRow(addText);
	layout->addRow(tr("Nom"), name);
	layout->addRow(calandarArea);
	layout->addRow(tr("Heure debut"), hour);
	layout->addRow(tr("Heure fin"), hourFin);
	layout->addRow(tr("Minute debut"), minDebut);
	layout->addRow(tr("Minute fin"), minuteFin);
	layout->addRow(tr("Professeur"), teacher);
	layout->addRow(tr("Lieu"), place);
	layout->addRow(tr("Type"), type);
	layout->addRow(addButton);
	layout->addRow(cancelButton);
	setLayout(layout);

	mainWindow = mainWindowP;

	QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(quiting()));
	QObject::connect(addButton, SIGNAL(clicked()), this, SLOT(adding()));
	QObject::connect(calandarButton, SIGNAL(clicked()), this, SLOT(viewCalendar()));

	AddCaseWindow::setVisible(true);
	show();
}

AddCaseWindow::~AddCaseWindow()
{
}

/*
* Méthode permetant d'obtenir tous les groupes depuis la base de données
**/
void AddCaseWindow::getGroup() {
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
			errorSoundAdd.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundAdd.setVolume(0.25f);
			errorSoundAdd.play();
			qDebug() << errorSoundAdd.status();
			errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
		}

		QJsonValue groups = json.object().value("prof");
		tableaiCase = groups.toArray();
	}
	else {
		QErrorMessage* errorMsg = new QErrorMessage(this);
		errorSoundAdd.setSource(QUrl::fromLocalFile("error.wav"));
		errorSoundAdd.setVolume(0.25f);
		errorSoundAdd.play();
		errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
	}
}

/*
* Méthode permetant d'obtenir tous les lieux depuis la base de données
**/
void AddCaseWindow::getPlace() {
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
			errorSoundAdd.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundAdd.setVolume(0.25f);
			errorSoundAdd.play();
			qDebug() << errorSoundAdd.status();
			errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
		}

		QJsonValue groups = json.object().value("salle");
		tableaiCase2 = groups.toArray();
	}
	else {
		QErrorMessage* errorMsg = new QErrorMessage(this);
		errorSoundAdd.setSource(QUrl::fromLocalFile("error.wav"));
		errorSoundAdd.setVolume(0.25f);
		errorSoundAdd.play();
		errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
	}
}

/*
* Méthode permetant de fermer le formulaire d'ajout d'évènement
**/
void AddCaseWindow::quiting() {
	AddCaseWindow::setVisible(false);
	delete this;
}

/*
* Méthode permetant d'obtenir un petit calendrier pour chosir une date
**/
void AddCaseWindow::viewCalendar() {
	if (isCalendarOpen == true) {
		calendar->setVisible(false);
		AddCaseWindow::isCalendarOpen = false;
	} else {
		AddCaseWindow::isCalendarOpen = true;
		calendar->setVisible(true);
	}
}

/*
* Méthode permetant d'obtenir la date sélectionnée depuis le calendrier
**/
void AddCaseWindow::getDate() {
	 date = calendar->selectedDate().toString("yyyy/MM/dd");
	 calandarButton->setText("Date selectionnee : " + date);
	 AddCaseWindow::isCalendarOpen = false;
	 calendar->setVisible(false);
}

/*
* Méthode permetant d'ajouter l'évènement à la base de données
**/
void AddCaseWindow::adding() {
	if (name->text() != "" && teacher->itemText(teacher->currentIndex()) != "" && place->itemText(place->currentIndex()) != "" && type->text() != "" && date != "" && !(minDebut->itemText(minDebut->currentIndex()) == "0" && minuteFin->itemText(minuteFin->currentIndex()) == "0")) {
		QNetworkAccessManager networkAccessManager;
		QString actualHourValue = hour->itemText(hour->currentIndex());
		QString actualHourFin = hourFin->itemText(hourFin->currentIndex());
		QString actualMinDebut = minDebut->itemText(minDebut->currentIndex());
		QString actualMinuteFin = minuteFin->itemText(minuteFin->currentIndex());
		if (actualHourValue.toInt() <= actualHourFin.toInt()) {
			QNetworkRequest networkRequest(QUrl(QString("https://dwarves.iut-fbleau.fr/~barbey/EDT/script1.php?Add=true&groupid=" + QString::number(groupid) + "&subject=" + name->text() + "&date=" + date + "&hourdebut=" + actualHourValue + "&mindebut=" + actualMinDebut + "&hourfin=" + actualHourFin + "&minutefin=" + actualMinuteFin + "&idprof=" + teacher->itemData(teacher->currentIndex()).toString() + "&idlieu=" + place->itemData(place->currentIndex()).toString() + "&type=" + type->text())));
			QNetworkReply* networkReply = networkAccessManager.get(networkRequest);
			QEventLoop eventLoop;
			QObject::connect(networkReply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
			eventLoop.exec();
			qDebug() << networkReply->readAll();
			QVariant status_code = networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
			if (status_code.isValid()) {
				QDate currentDate = QDateTime::currentDateTime().date();
				int todayDate = QDateTime::currentDateTime().date().dayOfWeek();
				if (todayDate != 1) {
					currentDate.setDate(currentDate.year(), currentDate.month(), ((currentDate.day() + 1) - todayDate));
				}
				mainWindow->loadCalendar(2, groupid, currentDate);
				AddCaseWindow::setVisible(false);
			}
			else {
				QErrorMessage* errorMsg = new QErrorMessage(this);
				errorSoundAdd.setSource(QUrl::fromLocalFile("error.wav"));
				errorSoundAdd.setVolume(0.25f);
				errorSoundAdd.play();
				errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
			}
		}
		else {
			QErrorMessage* errorMsg = new QErrorMessage(this);
			errorSoundAdd.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundAdd.setVolume(0.25f);
			errorSoundAdd.play();
			errorMsg->showMessage(tr("Erreur l heure de debut ne paut etre superieure a l heure de fin"));
		}
	} else {
		QErrorMessage* errorMsg = new QErrorMessage(this);
		if (name->text() == "") {
			errorSoundAdd.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundAdd.setVolume(0.25f);
			errorSoundAdd.play();
			errorMsg->showMessage(tr("Erreur le nom doit etre donne"));
		}
		if (type->text() == "") {
			errorSoundAdd.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundAdd.setVolume(0.25f);
			errorSoundAdd.play();
			errorMsg->showMessage(tr("Erreur un type doit etre donne"));
		}
		if (date == "") {
			errorSoundAdd.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundAdd.setVolume(0.25f);
			errorSoundAdd.play();
			errorMsg->showMessage(tr("Erreur une date doit etre choisie"));
		}
		if (minDebut->itemText(minDebut->currentIndex()) == "0" && minuteFin->itemText(minuteFin->currentIndex()) == "0") {
			errorSoundAdd.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundAdd.setVolume(0.25f);
			errorSoundAdd.play();
			errorMsg->showMessage(tr("Erreur la minute du debut et celle de fin ne peuvent valoir tous deux 0"));
		}
	}
}
