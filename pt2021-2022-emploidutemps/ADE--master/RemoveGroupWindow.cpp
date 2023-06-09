#include "RemoveGroupWindow.h"
#include "ADE.h"
#include <QtWidgets>
#include <QtNetwork>

/*
* Classe permetant de supprimer un groupe (admin)
**/

/*
* Contrusteur de la classe permetant de supprimer un groupe
**/
RemoveGroupWindow::RemoveGroupWindow(int idAdmin, ADE* groupmainWindowP, QWidget* parent) : QWidget(parent)
{
	grouplist = new QComboBox;

	RemoveGroupWindow::idAdmin = idAdmin;

	QPushButton* addButton = new QPushButton("Supprimer", this);
	QPushButton* cancelButton = new QPushButton("Annuler", this);

	getGroup();

	for (int nb = 0; nb < tableaiRemove.size(); nb++) {
		grouplist->addItem(tableaiRemove.at(nb)["name"].toString());
		grouplist->setItemData(nb, tableaiRemove.at(nb)["groupid"].toString());
	}

	layout = new QFormLayout;
	QLabel* addText = new QLabel("Choississez le groupe que vous souhaitez supprimer :");
	layout->addRow(addText);
	layout->addRow(grouplist);
	layout->addRow(addButton);
	layout->addRow(cancelButton);
	setLayout(layout);

	remgroupmainWindow = groupmainWindowP;

	QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(quiting()));
	QObject::connect(addButton, SIGNAL(clicked()), this, SLOT(adding()));

	RemoveGroupWindow::setVisible(true);
	show();
}

RemoveGroupWindow::~RemoveGroupWindow()
{}

/*
* Méthode permetant d'obtenir tous les groupes existants depuis la base de données
**/
void RemoveGroupWindow::getGroup() {
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
			errorSoundRemoveGroup.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundRemoveGroup.setVolume(0.25f);
			errorSoundRemoveGroup.play();
			qDebug() << errorSoundRemoveGroup.status();
			errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
		}

		QJsonValue groups = json.object().value("groups");
		tableaiRemove = groups.toArray();
	}
	else {
		QErrorMessage* errorMsg = new QErrorMessage(this);
		errorSoundRemoveGroup.setSource(QUrl::fromLocalFile("error.wav"));
		errorSoundRemoveGroup.setVolume(0.25f);
		errorSoundRemoveGroup.play();
		errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
	}
}

/*
* Méthode permetant de supprimer le groupe dans la base de données
**/
void RemoveGroupWindow::adding() {
	if (grouplist->itemText(grouplist->currentIndex()) != "") {
		QNetworkAccessManager* manager = new QNetworkAccessManager(this);
		QHttpMultiPart* http = new QHttpMultiPart(QHttpMultiPart::FormDataType);

		QHttpPart receiptPart;
		receiptPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"removegroupe\""));
		receiptPart.setBody("true");

		QHttpPart receiptPart2;
		receiptPart2.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"id\""));
		receiptPart2.setBody(grouplist->itemData(grouplist->currentIndex()).toString().toUtf8());

		http->append(receiptPart);
		http->append(receiptPart2);

		QNetworkReply* repl = manager->post(QNetworkRequest(QUrl("https://dwarves.iut-fbleau.fr/~barbey/EDT/script1.php")), http);
		connect(manager, SIGNAL(finished(QNetworkReply*)),
			this, SLOT(replyFinished(QNetworkReply*)));
	}
	else {
		QErrorMessage* errorMsg = new QErrorMessage(this);
		errorSoundRemoveGroup.setSource(QUrl::fromLocalFile("error.wav"));
		errorSoundRemoveGroup.setVolume(0.25f);
		errorSoundRemoveGroup.play();
		qDebug() << errorSoundRemoveGroup.status();
		errorMsg->showMessage(tr("Erreur."));
	}
}

/*
* Méthode SLOT permetant de gérer ce qui se passe lorsque la requête de suppression d'un groupe est terminée
**/
void RemoveGroupWindow::replyFinished(QNetworkReply* resp) {
	QVariant status_code = resp->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	if (status_code.isValid()) {
		QString status = status_code.toString();
		qDebug() << status;
		QByteArray data = resp->readAll();
		qDebug() << data;
		RemoveGroupWindow::setVisible(false);
	}
	else {
		QErrorMessage* errorMsg = new QErrorMessage(this);
		errorSoundRemoveGroup.setSource(QUrl::fromLocalFile("error.wav"));
		errorSoundRemoveGroup.setVolume(0.25f);
		errorSoundRemoveGroup.play();
		errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
	}
}

/*
* Méthode permetant de quitter le formulaire de suppression d'un groupe
**/
void RemoveGroupWindow::quiting() {
	RemoveGroupWindow::setVisible(false);
	delete this;
}
