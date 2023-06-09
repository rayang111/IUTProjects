#include "AddPlaceWindow.h"

/*
* Classe permetant de créer un lieu (admin)
**/

/*
* Constructeur de la classe permetant d'ajouter un lieu
**/
AddPlaceWindow::AddPlaceWindow(int idAdmin, QWidget *parent)
	: QWidget(parent)
{
	placeName = new QLineEdit;

	AddPlaceWindow::idAdmin = idAdmin;

	QPushButton* addButton = new QPushButton(tr("Ajouter"), this);
	QPushButton* cancelButton = new QPushButton(tr("Annuler"), this);

	QFormLayout* layout = new QFormLayout;
	QLabel* addText = new QLabel(tr("Veulliez indiquer ces informations pour creer une salle."));
	layout->addRow(addText);
	layout->addRow(tr("Nom"), placeName);
	layout->addRow(addButton);
	layout->addRow(cancelButton);
	setLayout(layout);

	QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(quiting()));
	QObject::connect(addButton, SIGNAL(clicked()), this, SLOT(adding()));

	setVisible(true);
	show();
}

AddPlaceWindow::~AddPlaceWindow()
{
}

/*
* Méthode permetant d'ajouter le lieu à la base de données
**/
void AddPlaceWindow::adding() {
	if (placeName->text() != "") {
			QNetworkAccessManager networkAccessManager;
			QNetworkAccessManager* manager = new QNetworkAccessManager(this);
			QHttpMultiPart* http = new QHttpMultiPart(QHttpMultiPart::FormDataType);

			QHttpPart receiptPart;
			receiptPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"addsalle\""));
			receiptPart.setBody("true");

			QHttpPart receiptPart2;
			receiptPart2.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"idadmin\""));
			receiptPart2.setBody(QString::number(idAdmin).toUtf8());

			QHttpPart receiptPart3;
			receiptPart3.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"nom\""));
			receiptPart3.setBody(placeName->text().toUtf8());

			http->append(receiptPart);
			http->append(receiptPart2);
			http->append(receiptPart3);

			QNetworkReply* repl = manager->post(QNetworkRequest(QUrl("https://dwarves.iut-fbleau.fr/~barbey/EDT/script1.php")), http);
			connect(manager, SIGNAL(finished(QNetworkReply*)),
				this, SLOT(replyFinished(QNetworkReply*)));
	}
	else {
		QErrorMessage* errorMsg = new QErrorMessage(this);
		errorSoundAddPlace.setSource(QUrl::fromLocalFile("error.wav"));
		errorSoundAddPlace.setVolume(0.25f);
		errorSoundAddPlace.play();
		errorMsg->showMessage(tr("Erreur le nom doit etre donne"));

	}
}

/*
* Méthode SLOT permetant gérer ce qui passe lorsque la requête est finie
**/
void AddPlaceWindow::replyFinished(QNetworkReply* resp) {
	QVariant status_code = resp->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	if (status_code.isValid()) {
		QString status = status_code.toString();
		qDebug() << status;
		QByteArray data = resp->readAll();
		qDebug() << data;
		setVisible(false);
	}
	else {
		QErrorMessage* errorMsg = new QErrorMessage(this);
		errorSoundAddPlace.setSource(QUrl::fromLocalFile("error.wav"));
		errorSoundAddPlace.setVolume(0.25f);
		errorSoundAddPlace.play();
		errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
	}
}

/*
* Méthode permetant de quitter le formulaire d'ajout de lieu
**/
void AddPlaceWindow::quiting() {
	AddPlaceWindow::setVisible(false);
	delete this;
}