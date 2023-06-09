#include "RemoveTeacherWindow.h"

/*
* Classe permetant de supprimer un intervenant (admin)
**/

/*
* Constructeur de la classe permetant de supprimer un intervenant
**/
RemoveTeacherWindow::RemoveTeacherWindow(int idAdmin, ADE* groupmainWindowP, QWidget *parent)
	: QWidget(parent)
{
	teacherlist = new QComboBox;

	RemoveTeacherWindow::idAdmin = idAdmin;

	QPushButton* addButton = new QPushButton("Supprimer", this);
	QPushButton* cancelButton = new QPushButton("Annuler", this);

	getGroup();

	for (int nb = 0; nb < tableaiRemove.size(); nb++) {
		teacherlist->addItem(tableaiRemove.at(nb)["nom"].toString());
		teacherlist->setItemData(nb, tableaiRemove.at(nb)["id"].toString());
	}

	layout = new QFormLayout;
	QLabel* addText = new QLabel("Choississez le professeur que vous souhaitez supprimer :");
	layout->addRow(addText);
	layout->addRow(teacherlist);
	layout->addRow(addButton);
	layout->addRow(cancelButton);
	setLayout(layout);

	remgroupmainWindow = groupmainWindowP;

	QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(quiting()));
	QObject::connect(addButton, SIGNAL(clicked()), this, SLOT(adding()));

	RemoveTeacherWindow::setVisible(true);
	show();
}

RemoveTeacherWindow::~RemoveTeacherWindow()
{
}

/*
* Méthode permetant d'obtenir tous les groupes existant depuis la base de données
**/
void RemoveTeacherWindow::getGroup() {
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
			errorSoundRemoveTeacher.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundRemoveTeacher.setVolume(0.25f);
			errorSoundRemoveTeacher.play();
			qDebug() << errorSoundRemoveTeacher.status();
			errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
		}

		QJsonValue groups = json.object().value("prof");
		tableaiRemove = groups.toArray();
	}
	else {
		QErrorMessage* errorMsg = new QErrorMessage(this);
		errorSoundRemoveTeacher.setSource(QUrl::fromLocalFile("error.wav"));
		errorSoundRemoveTeacher.setVolume(0.25f);
		errorSoundRemoveTeacher.play();
		errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
	}
}

/*
* Méthode permetant de supprimer l'intervernant dans la base de données
**/
void RemoveTeacherWindow::adding() {
	if (teacherlist->itemText(teacherlist->currentIndex()) != "") {
		QNetworkAccessManager* manager = new QNetworkAccessManager(this);
		QHttpMultiPart* http = new QHttpMultiPart(QHttpMultiPart::FormDataType);

		QHttpPart receiptPart;
		receiptPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"removeprof\""));
		receiptPart.setBody("true");

		QHttpPart receiptPart2;
		receiptPart2.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"id\""));
		receiptPart2.setBody(teacherlist->itemData(teacherlist->currentIndex()).toString().toUtf8());


		http->append(receiptPart);
		http->append(receiptPart2);

		QNetworkReply* repl = manager->post(QNetworkRequest(QUrl("https://dwarves.iut-fbleau.fr/~barbey/EDT/script1.php")), http);
		connect(manager, SIGNAL(finished(QNetworkReply*)),
			this, SLOT(replyFinished(QNetworkReply*)));
	}
	else {
		QErrorMessage* errorMsg = new QErrorMessage(this);
		errorSoundRemoveTeacher.setSource(QUrl::fromLocalFile("error.wav"));
		errorSoundRemoveTeacher.setVolume(0.25f);
		errorSoundRemoveTeacher.play();
		qDebug() << errorSoundRemoveTeacher.status();
		errorMsg->showMessage(tr("Erreur."));
	}
}

/*
* Méthode SLOT permetant de gérer ce sui ce passe lorsque la requête de suppression d'un intervenant est terminée
**/
void RemoveTeacherWindow::replyFinished(QNetworkReply* resp) {
	QVariant status_code = resp->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	if (status_code.isValid()) {
		QString status = status_code.toString();
		qDebug() << status;
		QByteArray data = resp->readAll();
		qDebug() << data;
		RemoveTeacherWindow::setVisible(false);
	}
	else {
		QErrorMessage* errorMsg = new QErrorMessage(this);
		errorSoundRemoveTeacher.setSource(QUrl::fromLocalFile("error.wav"));
		errorSoundRemoveTeacher.setVolume(0.25f);
		errorSoundRemoveTeacher.play();
		errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
	}
}

/*
* Méthode permetant de quitter le formulaire de suppression d'un intervenant
**/
void RemoveTeacherWindow::quiting() {
	RemoveTeacherWindow::setVisible(false);
	delete this;
}