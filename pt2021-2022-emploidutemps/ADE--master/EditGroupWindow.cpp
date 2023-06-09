#include "EditGroupWindow.h"

/*
* Classe permetant d'éditer un groupe (admin)
**/

/*
* Constructeur de la classe permetant d'éditer un groupe
**/
EditGroupWindow::EditGroupWindow(int idAdmin, QWidget *parent)
	: QWidget(parent)
{
	group = new QComboBox;
	groupNameEdit = new QLineEdit;
	groupLogin = new QLineEdit;
	groupPwdEdit = new QLineEdit;
	groupPwdEdit->setEchoMode(QLineEdit::Password);
	groupConfirmPwdEdit = new QLineEdit;
	groupConfirmPwdEdit->setEchoMode(QLineEdit::Password);

	EditGroupWindow::idAdmin = idAdmin;

	QPushButton* addButton = new QPushButton(tr("Modifier"), this);
	QPushButton* cancelButton = new QPushButton(tr("Annuler"), this);

	getGroup();

	for (int i = 0; i < tableaiEdit.size(); i++) {
		group->addItem(tableaiEdit.at(i)["name"].toString());
		group->setItemData(i, tableaiEdit.at(i)["groupid"].toString());
	}

	QFormLayout* layout = new QFormLayout;
	QLabel* addText = new QLabel(tr("Veulliez indiquer ces informations pour modifier un groupe."));
	layout->addRow(addText);
	layout->addRow(tr("Selectionez un groupe"), group);
	layout->addRow(tr("login"), groupLogin);
	layout->addRow(tr("Nouveau nom"), groupNameEdit);
	layout->addRow(tr("Mot de passe"), groupPwdEdit);
	layout->addRow(tr("Mot de passe 2"), groupConfirmPwdEdit);
	layout->addRow(addButton);
	layout->addRow(cancelButton);
	setLayout(layout);

	QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(quiting()));
	QObject::connect(addButton, SIGNAL(clicked()), this, SLOT(adding()));

	setVisible(true);
	show();
}

EditGroupWindow::~EditGroupWindow()
{
}

/*
* Méthode permetant d'obtenir tous les groupes existant dans la base de données
**/
void EditGroupWindow::getGroup() {
	QNetworkAccessManager networkAccessManager;
	QNetworkRequest networkRequest(QUrl(QString("https://dwarves.iut-fbleau.fr/~barbey/EDT/script1.php?getgroupe=true&idadmin=" + QString::number(idAdmin))));
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
			errorSoundEditGroup.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundEditGroup.setVolume(0.25f);
			errorSoundEditGroup.play();
			qDebug() << errorSoundEditGroup.status();
			errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
		}

		QJsonValue groups = json.object().value("groups");
		tableaiEdit = groups.toArray();
	}
	else {
		QErrorMessage* errorMsg = new QErrorMessage(this);
		errorSoundEditGroup.setSource(QUrl::fromLocalFile("error.wav"));
		errorSoundEditGroup.setVolume(0.25f);
		errorSoundEditGroup.play();
		errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
	}
}

/*
* Méthode permetant de modifier le groupe dans la base de données
**/
void EditGroupWindow::adding() {

	if (groupNameEdit->text() != "" && group->currentIndex() != NULL) {
		if (groupNameEdit->text() != group->itemText(group->currentIndex())) {
			QNetworkAccessManager networkAccessManager;
			QNetworkAccessManager* manager = new QNetworkAccessManager(this);
			QHttpMultiPart* http = new QHttpMultiPart(QHttpMultiPart::FormDataType);

			QHttpPart receiptPart;
			receiptPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"editgroupe\""));
			receiptPart.setBody("true");

			QHttpPart receiptPart2;
			receiptPart2.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"id\""));
			receiptPart2.setBody(group->itemData(group->currentIndex()).toString().toUtf8());

			QHttpPart receiptPart3;
			receiptPart3.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"name\""));
			receiptPart3.setBody(groupNameEdit->text().toUtf8());

			QHttpPart receiptPart4;
			receiptPart4.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"login\""));
			receiptPart4.setBody(groupNameEdit->text().toUtf8());

			QHttpPart receiptPart5;
			receiptPart5.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"pwd\""));
			receiptPart5.setBody(groupNameEdit->text().toUtf8());

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
			errorSoundEditGroup.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundEditGroup.setVolume(0.25f);
			errorSoundEditGroup.play();
			errorMsg->showMessage(tr("Erreur le nom doit etre donne"));
		}
	}
	else {
		QErrorMessage* errorMsg = new QErrorMessage(this);
		if (groupNameEdit->text() == "") {
			errorSoundEditGroup.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundEditGroup.setVolume(0.25f);
			errorSoundEditGroup.play();
			errorMsg->showMessage(tr("Erreur le nom doit etre donne"));
		}
		if (group->itemText(group->currentIndex()) == "") {
			errorSoundEditGroup.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundEditGroup.setVolume(0.25f);
			errorSoundEditGroup.play();
			errorMsg->showMessage(tr("Erreur le nom doit etre donne"));
		}
	}
}

/*
* Méthode SLOT permetant de gérer ce qu'il se passe lors de la modification du groupe dans la base de données
**/
void EditGroupWindow::replyFinished(QNetworkReply* resp) {
	QVariant status_code = resp->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	if (status_code.isValid()) {
		QString status = status_code.toString(); 
		qDebug() << status;
		QByteArray data = resp->readAll();
		qDebug() << data;
		EditGroupWindow::setVisible(false);
	}
	else {
		QErrorMessage* errorMsg = new QErrorMessage(this);
		errorSoundEditGroup.setSource(QUrl::fromLocalFile("error.wav"));
		errorSoundEditGroup.setVolume(0.25f);
		errorSoundEditGroup.play();
		errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
	}
}

/*
* Méthode permetant de quitter le formulaire de modification de groupe
**/
void EditGroupWindow::quiting() {
	EditGroupWindow::setVisible(false);
	delete this;
}