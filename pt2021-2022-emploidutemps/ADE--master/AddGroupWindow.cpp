#include "AddGroupWindow.h"

/*
* Classe permetant de créer un groupe (admin)
**/

/*
* Constructeur de la classe permetant de créer un groupe
**/
AddGroupWindow::AddGroupWindow(int idAdmin, QWidget *parent)
	: QWidget(parent)
{
	groupName = new QLineEdit;
	groupLogin = new QLineEdit;
	pwd = new QLineEdit;
	pwd->setEchoMode(QLineEdit::Password);
	confirmPwd = new QLineEdit;
	confirmPwd->setEchoMode(QLineEdit::Password);

	AddGroupWindow::idAdmin = idAdmin;

	QPushButton* addButton = new QPushButton(tr("Ajouter"), this);
	QPushButton* cancelButton = new QPushButton(tr("Annuler"), this);

	QFormLayout* layout = new QFormLayout;
	QLabel* addText = new QLabel(tr("Veulliez indiquer ces informations pour creer un intervenant."));
	QLabel* adminidText = new QLabel(tr("Vous etes l admin numero ") + QString::number(idAdmin));
	layout->addRow(addText);
	layout->addRow(adminidText);
	layout->addRow(tr("Nom"), groupName);
	layout->addRow(tr("Login"), groupLogin);
	layout->addRow(tr("Mot de passe"), pwd);
	layout->addRow(tr("Confirmer le mot de passe"), confirmPwd);
	layout->addRow(addButton);
	layout->addRow(cancelButton);
	setLayout(layout);

	QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(quiting()));
	QObject::connect(addButton, SIGNAL(clicked()), this, SLOT(adding()));

	setVisible(true);
	show();
}

AddGroupWindow::~AddGroupWindow()
{
}

/*
* Méthode permetant d'ajouter le groupe à la base de données
**/
void AddGroupWindow::adding() {
	if (groupName->text() != "" && pwd->text() != "" && confirmPwd->text() != "") {

		if (pwd->text() == confirmPwd->text()) {
			QNetworkAccessManager networkAccessManager;
			QNetworkAccessManager* manager = new QNetworkAccessManager(this);
			QHttpMultiPart* http = new QHttpMultiPart(QHttpMultiPart::FormDataType);

			QHttpPart receiptPart;
			receiptPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"addgroupe\""));
			receiptPart.setBody("true");

			qDebug() << "ABC " + QString::number(idAdmin);
			QHttpPart receiptPart2;
			receiptPart2.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"idadmin\""));
			receiptPart2.setBody(QString::number(idAdmin).toUtf8());

			QHttpPart receiptPart3;
			receiptPart3.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"name\""));
			receiptPart3.setBody(groupName->text().toUtf8());

			QHttpPart receiptPart4;
			receiptPart4.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"login\""));
			receiptPart4.setBody(groupLogin->text().toUtf8());

			QHttpPart receiptPart5;
			receiptPart5.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"pwd\""));
			receiptPart5.setBody(pwd->text().toUtf8());


			http->append(receiptPart);
			http->append(receiptPart2);
			http->append(receiptPart3);
			http->append(receiptPart4);
			http->append(receiptPart5);

			QNetworkReply* repl = manager->post(QNetworkRequest(QUrl("https://dwarves.iut-fbleau.fr/~barbey/EDT/script1.php")), http);
			connect(manager, SIGNAL(finished(QNetworkReply*)),
				this, SLOT(replyFinished(QNetworkReply*)));
		}
		else {
			QErrorMessage* errorMsg = new QErrorMessage(this);
			errorSoundAdd.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundAdd.setVolume(0.25f);
			errorSoundAdd.play();
			errorMsg->showMessage(tr("Erreur le nom doit etre donne"));
		}
	}
	else {
		QErrorMessage* errorMsg = new QErrorMessage(this);
		if (groupName->text() == "") {
			errorSoundAdd.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundAdd.setVolume(0.25f);
			errorSoundAdd.play();
			errorMsg->showMessage(tr("Erreur le nom doit etre donne"));
		}
		if (pwd->text() == "") {
			errorSoundAdd.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundAdd.setVolume(0.25f);
			errorSoundAdd.play();
			errorMsg->showMessage(tr("Erreur le nom doit etre donne"));
		}
		if (confirmPwd->text() != "") {
			errorSoundAdd.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundAdd.setVolume(0.25f);
			errorSoundAdd.play();
			errorMsg->showMessage(tr("Erreur le nom doit etre donne"));
		}
	}
}

/*
* Méthode SLOT permetant de gérer ce qu'il se passe lorsque la requête d'ajout est terminée
**/
void AddGroupWindow::replyFinished(QNetworkReply* resp) {
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
		errorSoundAdd.setSource(QUrl::fromLocalFile("error.wav"));
		errorSoundAdd.setVolume(0.25f);
		errorSoundAdd.play();
		errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
	}
}

/*
* Méthode permetant de quitter le formulaire d'ajout de groupe
**/
void AddGroupWindow::quiting() {
	AddGroupWindow::setVisible(false);
	delete this;
}