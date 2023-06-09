#include "EditPlaceWindow.h"
#include <QtNetwork>

/**
* Classe permetant l'édition d'un lieu (admin)
*/

/*
* Constructeur de la classe permetant l'édition d'un lieu
**/
EditPlaceWindow::EditPlaceWindow(int idAdmin, QWidget *parent)
	: QWidget(parent)
{
	places = new QComboBox;
	placeNameEdit = new QLineEdit;

	EditPlaceWindow::idAdmin = idAdmin;

	QPushButton* addButton = new QPushButton(tr("Modifier"), this);
	QPushButton* cancelButton = new QPushButton(tr("Annuler"), this);

	getPlace();

	for (int i = 0; i < tableai.size(); i++) {
		places->addItem(tableai.at(i)["nom"].toString());
		places->setItemData(i,tableai.at(i)["id"].toString());
	}

	QFormLayout* layout = new QFormLayout;
	QLabel* addText = new QLabel(tr("Veulliez indiquer ces informations pour modifier une salle."));
	layout->addRow(addText);
	layout->addRow(tr("Selectionez une salle"), places);
	layout->addRow(tr("Nouveau nom"), placeNameEdit);
	layout->addRow(addButton);
	layout->addRow(cancelButton);
	setLayout(layout);

	QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(quiting()));
	QObject::connect(addButton, SIGNAL(clicked()), this, SLOT(adding()));

	setVisible(true);
	show();
}

EditPlaceWindow::~EditPlaceWindow()
{
}

/*
* Méthode permetant d'obtenir tous les lieux existant depuis la base de données
**/
void EditPlaceWindow::getPlace() {
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
					errorSoundEditPlace.setSource(QUrl::fromLocalFile("error.wav"));
					errorSoundEditPlace.setVolume(0.25f);
					errorSoundEditPlace.play();
					qDebug() << errorSoundEditPlace.status();
					errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
				}

				QJsonValue salle = json.object().value("salle");
				tableai = salle.toArray();
			}
			else {
				QErrorMessage* errorMsg = new QErrorMessage(this);
				errorSoundEditPlace.setSource(QUrl::fromLocalFile("error.wav"));
				errorSoundEditPlace.setVolume(0.25f);
				errorSoundEditPlace.play();
				errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
			}
}

/*
* Méthode permetant de modifier le lieu dans la base de données
**/
void EditPlaceWindow::adding() {

	if (placeNameEdit->text() != "" && places->currentIndex() == NULL) {

		if (placeNameEdit->text() != places->itemText(places->currentIndex())) {
			QNetworkAccessManager networkAccessManager;
			QNetworkAccessManager* manager = new QNetworkAccessManager(this);
			QHttpMultiPart* http = new QHttpMultiPart(QHttpMultiPart::FormDataType);

			QHttpPart receiptPart;
			receiptPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"editsalle\""));
			receiptPart.setBody("true");

			QHttpPart receiptPart2;
			receiptPart2.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"id\""));
			receiptPart2.setBody(places->itemData(places->currentIndex()).toString().toUtf8());

			QHttpPart receiptPart3;
			receiptPart3.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"nom\""));
			receiptPart3.setBody(placeNameEdit->text().toUtf8());



			http->append(receiptPart);
			http->append(receiptPart2);
			http->append(receiptPart3);

			QNetworkReply* repl = manager->post(QNetworkRequest(QUrl("https://dwarves.iut-fbleau.fr/~barbey/EDT/script1.php")), http);
			connect(manager, SIGNAL(finished(QNetworkReply*)),
				this, SLOT(replyFinished(QNetworkReply*)));
		}
		else {
			QErrorMessage* errorMsg = new QErrorMessage(this);
			errorSoundEditPlace.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundEditPlace.setVolume(0.25f);
			errorSoundEditPlace.play();
			errorMsg->showMessage(tr("Erreur le nom doit etre donne"));
		}
	}
	else {
		QErrorMessage* errorMsg = new QErrorMessage(this);
		if (placeNameEdit->text() == "") {
			errorSoundEditPlace.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundEditPlace.setVolume(0.25f);
			errorSoundEditPlace.play();
			errorMsg->showMessage(tr("Erreur le nom doit etre donne"));
		}
		if (places->itemText(places->currentIndex()) == "") {
			errorSoundEditPlace.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundEditPlace.setVolume(0.25f);
			errorSoundEditPlace.play();
			errorMsg->showMessage(tr("Erreur le nom doit etre donne"));
		}
	}
}

/*
* Méthode SLOT permetant gérer ce qui se passe lorsque la requête de modification du lieu est terminée
**/
void EditPlaceWindow::replyFinished(QNetworkReply* resp) {
	QVariant status_code = resp->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	if (status_code.isValid()) {
		QString status = status_code.toString();
		qDebug() << status;
		QByteArray data = resp->readAll();
		qDebug() << data;
		EditPlaceWindow::setVisible(false);
	}
	else {
		QErrorMessage* errorMsg = new QErrorMessage(this);
		errorSoundEditPlace.setSource(QUrl::fromLocalFile("error.wav"));
		errorSoundEditPlace.setVolume(0.25f);
		errorSoundEditPlace.play();
		errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
	}
}

/*
* Méthode permetant de quitter le formulaire de modification de lieu
**/
void EditPlaceWindow::quiting() {
	EditPlaceWindow::setVisible(false);
	delete this;
}