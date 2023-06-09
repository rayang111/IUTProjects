#include "RemovePlaceWindow.h"

/*
* Classe permetant de supprimer un lieu (admin)
**/

/*
* Constructeur de la classe permetant de supprimer un lieu
**/
RemovePlaceWindow::RemovePlaceWindow(int idAdmin, ADE* groupmainWindowP, QWidget *parent)
	: QWidget(parent)
{
	placelist = new QComboBox;

	RemovePlaceWindow::idAdmin = idAdmin;

	QPushButton* addButton = new QPushButton("Supprimer", this);
	QPushButton* cancelButton = new QPushButton("Annuler", this);

	getGroup();

	for (int nb = 0; nb < tableaiRemove.size(); nb++) {
		placelist->addItem(tableaiRemove.at(nb)["nom"].toString());
		placelist->setItemData(nb, tableaiRemove.at(nb)["id"].toString());
	}

	layout = new QFormLayout;
	QLabel* addText = new QLabel("Choississez la salle que vous souhaitez supprimer :");
	layout->addRow(addText);
	layout->addRow(placelist);
	layout->addRow(addButton);
	layout->addRow(cancelButton);
	setLayout(layout);

	remgroupmainWindow = groupmainWindowP;

	QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(quiting()));
	QObject::connect(addButton, SIGNAL(clicked()), this, SLOT(adding()));

	RemovePlaceWindow::setVisible(true);
	show();
}

RemovePlaceWindow::~RemovePlaceWindow()
{
}

/*
* Méthode permetant d'obtenir tous les groupes depuis la base de données
**/
void RemovePlaceWindow::getGroup() {
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
			errorSoundRemovePlace.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundRemovePlace.setVolume(0.25f);
			errorSoundRemovePlace.play();
			qDebug() << errorSoundRemovePlace.status();
			errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
		}

		QJsonValue groups = json.object().value("salle");
		tableaiRemove = groups.toArray();
	}
	else {
		QErrorMessage* errorMsg = new QErrorMessage(this);
		errorSoundRemovePlace.setSource(QUrl::fromLocalFile("error.wav"));
		errorSoundRemovePlace.setVolume(0.25f);
		errorSoundRemovePlace.play();
		errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
	}
}

/*
* Méthode permetant de supprimer le lieu dans la base de données
**/
void RemovePlaceWindow::adding() {
	if (placelist->itemText(placelist->currentIndex()) != "") {
		QNetworkAccessManager* manager = new QNetworkAccessManager(this);
		QHttpMultiPart* http = new QHttpMultiPart(QHttpMultiPart::FormDataType);

		QHttpPart receiptPart;
		receiptPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"removesalle\""));
		receiptPart.setBody("true");

		QHttpPart receiptPart2;
		receiptPart2.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"id\""));
		receiptPart2.setBody(placelist->itemData(placelist->currentIndex()).toString().toUtf8());

		QHttpPart receiptPart3;
		receiptPart3.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"idadmin\""));
		receiptPart3.setBody(QString::number(idAdmin).toUtf8());

		http->append(receiptPart);
		http->append(receiptPart2);
		http->append(receiptPart3);

		QNetworkReply* repl = manager->post(QNetworkRequest(QUrl("https://dwarves.iut-fbleau.fr/~barbey/EDT/script1.php")), http);
		connect(manager, SIGNAL(finished(QNetworkReply*)),
			this, SLOT(replyFinished(QNetworkReply*)));
	}
	else {
		QErrorMessage* errorMsg = new QErrorMessage(this);
		errorSoundRemovePlace.setSource(QUrl::fromLocalFile("error.wav"));
		errorSoundRemovePlace.setVolume(0.25f);
		errorSoundRemovePlace.play();
		qDebug() << errorSoundRemovePlace.status();
		errorMsg->showMessage(tr("Erreur."));
	}
}

/*
* Méthode SLOT permetant gérer ce qui ce passe lorsque la requête de suppression de lieu est terminée
**/
void RemovePlaceWindow::replyFinished(QNetworkReply* resp) {
	QVariant status_code = resp->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	if (status_code.isValid()) {
		QString status = status_code.toString();
		qDebug() << status;
		QByteArray data = resp->readAll();
		qDebug() << data;
		RemovePlaceWindow::setVisible(false);
	}
	else {
		QErrorMessage* errorMsg = new QErrorMessage(this);
		errorSoundRemovePlace.setSource(QUrl::fromLocalFile("error.wav"));
		errorSoundRemovePlace.setVolume(0.25f);
		errorSoundRemovePlace.play();
		errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
	}
}

/*
* Méthode permetant de quitter le formulaire de suppression d'un lieu
**/
void RemovePlaceWindow::quiting() {
	RemovePlaceWindow::setVisible(false);
	delete this;
}
