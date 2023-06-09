#include "EditTeacherWindow.h"

/*
* Classe permetant d'éditer un intervenant (admin)
**/

/*
* Constructeur de la classe permetant d'éditer un intervenant
**/
EditTeacherWindow::EditTeacherWindow(int idAdmin, QWidget* parent)
	: QWidget(parent)
{
	idTeacherEdit = new QComboBox;
	teacherNameEdit = new QLineEdit;
	loginEdit = new QLineEdit;
	pwdEdit = new QLineEdit;
	pwdEdit->setEchoMode(QLineEdit::Password);
	newPwdEdit = new QLineEdit;
	newPwdEdit->setEchoMode(QLineEdit::Password);

	EditTeacherWindow::idAdmin = idAdmin;

	QPushButton* addButton = new QPushButton(tr("Modifier"), this);
	QPushButton* cancelButton = new QPushButton(tr("Annuler"), this);

	getTeachers();

	for (int i = 0; i < tableaiTeacherEdit.size(); i++) {
		idTeacherEdit->addItem(tableaiTeacherEdit.at(i)["nom"].toString());
		idTeacherEdit->setItemData(i, tableaiTeacherEdit.at(i)["id"].toString());
	}

	QFormLayout* layout = new QFormLayout;
	QLabel* addText = new QLabel(tr("Veulliez indiquer ces informations pour modifier un intervenant."));
	layout->addRow(addText);
	layout->addRow(tr("Identifiant"), idTeacherEdit);
	layout->addRow(tr("Nom"), teacherNameEdit);
	layout->addRow(tr("Login"), loginEdit);
	layout->addRow(tr("Nouveau mot de passe"), pwdEdit);
	layout->addRow(tr("Comfirmer le mot de passe"), newPwdEdit);
	layout->addRow(addButton);
	layout->addRow(cancelButton);
	setLayout(layout);

	QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(quiting()));
	QObject::connect(addButton, SIGNAL(clicked()), this, SLOT(adding()));

	setVisible(true);
	show();
}

EditTeacherWindow::~EditTeacherWindow()
{
}

/*
* Méthode permetant d'obtenir tous les intervenants existants depuis la base de données
**/
void EditTeacherWindow::getTeachers() {
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

		QJsonValue teachers = json.object().value("prof");
		tableaiTeacherEdit = teachers.toArray();
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
* Méthode permetant de modifier l'intervenant dans la base de données
**/
void EditTeacherWindow::adding() {
	if (idTeacherEdit->currentIndex() == NULL && teacherNameEdit->text() != "" && pwdEdit->text() != "" && newPwdEdit->text() != "") {
		if (pwdEdit->text() == newPwdEdit->text()) {
			QNetworkAccessManager networkAccessManager;
			QNetworkAccessManager* manager = new QNetworkAccessManager(this);
			QHttpMultiPart* http = new QHttpMultiPart(QHttpMultiPart::FormDataType);

			QHttpPart receiptPart;
			receiptPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"editprof\""));
			receiptPart.setBody("true");

			QHttpPart receiptPart2;
			receiptPart2.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"id\""));
			receiptPart2.setBody(idTeacherEdit->itemData(idTeacherEdit->currentIndex()).toString().toUtf8());

			QHttpPart receiptPart3;
			receiptPart3.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"nom\""));
			receiptPart3.setBody(teacherNameEdit->text().toUtf8());

			QHttpPart receiptPart4;
			receiptPart4.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"login\""));
			receiptPart4.setBody(loginEdit->text().toUtf8());

			QHttpPart receiptPart5;
			receiptPart5.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"pwd\""));
			receiptPart5.setBody(pwdEdit->text().toUtf8());

			QHttpPart receiptPart6;
			receiptPart6.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"pwd2\""));
			receiptPart6.setBody(newPwdEdit->text().toUtf8());


			http->append(receiptPart);
			http->append(receiptPart2);
			http->append(receiptPart3);
			http->append(receiptPart4);
			http->append(receiptPart5);
			http->append(receiptPart6);

			QNetworkReply* repl = manager->post(QNetworkRequest(QUrl("https://dwarves.iut-fbleau.fr/~barbey/EDT/script1.php")), http);
			connect(manager, SIGNAL(finished(QNetworkReply*)),
				this, SLOT(replyFinished(QNetworkReply*)));
		}
		else {
			QErrorMessage* errorMsg = new QErrorMessage(this);
			errorSoundEdit.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundEdit.setVolume(0.25f);
			errorSoundEdit.play();
			errorMsg->showMessage(tr("Les mots de passe ne sont pas identiques"));
		}
	}
	else {
		QErrorMessage* errorMsg = new QErrorMessage(this);
		if (teacherNameEdit->text() == "") {
			errorSoundEdit.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundEdit.setVolume(0.25f);
			errorSoundEdit.play();
			errorMsg->showMessage(tr("Le nom du professeur doit etre donne"));
		}
		if (pwdEdit->text() == "") {
			errorSoundEdit.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundEdit.setVolume(0.25f);
			errorSoundEdit.play();
			errorMsg->showMessage(tr("Un mot de passe doit etre donne"));
		}
		if (newPwdEdit->text() == "") {
			errorSoundEdit.setSource(QUrl::fromLocalFile("error.wav"));
			errorSoundEdit.setVolume(0.25f);
			errorSoundEdit.play();
			errorMsg->showMessage(tr("Vous devez confirmer votre mot de passe"));
		}
	}
}

/*
* Méthode SLOT permetant de gérer ce qui se passe lorsque la requête de modification de l'interveant est terminée
**/
void EditTeacherWindow::replyFinished(QNetworkReply* resp) {
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
		errorSoundEdit.setSource(QUrl::fromLocalFile("error.wav"));
		errorSoundEdit.setVolume(0.25f);
		errorSoundEdit.play();
		errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
	}
}

/*
* Méthode permetant de quitter le formulaire de modification d'un interveannt
**/
void EditTeacherWindow::quiting() {
	EditTeacherWindow::setVisible(false);
	delete this;
}