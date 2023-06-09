#include "RemoveCaseWindow.h"
#include "ADE.h"
#include <QtWidgets>
#include <QtNetwork>

/*
* Classe permetant de supprimer un évènement (admin)
**/

/*
* Constructeur de la classe permetant de supprimer un évènement
**/
RemoveCaseWindow::RemoveCaseWindow(std::vector<QString> caseIdP, int groupid,ADE* mainWindowRemoveP, QWidget *parent)
	: QWidget(parent)
{
	QVBoxLayout* layout = new QVBoxLayout;
	QWidget* panel = new QWidget();

	caseId = caseIdP;
    RemoveCaseWindow::groupid = groupid;

	QLabel* selectionText = new QLabel(tr("Identifiant de la ou les cases selectionnees : ") + caseId.at(0));

	QPushButton* removeButton = new QPushButton(tr("Valider la suppression"));
	QPushButton* cancelButton = new QPushButton(tr("Annuler la suppression"));
	layout->addWidget(selectionText);
	layout->addWidget(removeButton);
	layout->addWidget(cancelButton);
	panel->setLayout(layout);
	setLayout(layout);

	mainWindowRemove = mainWindowRemoveP;

	QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(quitting()));
	QObject::connect(removeButton, SIGNAL(clicked()), this, SLOT(removing()));

    RemoveCaseWindow::setVisible(true);
	show();
}

RemoveCaseWindow::~RemoveCaseWindow()
{
}

/*
* Méthode permetant d'annuler la supprimer un évènement
**/
void RemoveCaseWindow::quitting() {
    RemoveCaseWindow::setVisible(false);
    delete this;
}

/*
* Méthode permetant de supprimer un évènement de la base de données
**/
void RemoveCaseWindow::removing() {
    if (caseId.at(0) != "") {
        QNetworkAccessManager* manager = new QNetworkAccessManager(this);
        QHttpMultiPart* http = new QHttpMultiPart(QHttpMultiPart::FormDataType);

        QHttpPart receiptPart;
        receiptPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"Remouve\""));
        receiptPart.setBody("true");

        QHttpPart receiptPart2;
        receiptPart2.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"id\""));
        receiptPart2.setBody(caseId.at(0).toUtf8());

        http->append(receiptPart);
        http->append(receiptPart2);

        QNetworkReply* repl = manager->post(QNetworkRequest(QUrl("https://dwarves.iut-fbleau.fr/~barbey/EDT/script1.php")), http);
        connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinishedRemove(QNetworkReply*)));
    }
    else {
        QErrorMessage* errorMsg = new QErrorMessage(this);
        errorSoundRemove.setSource(QUrl::fromLocalFile("error.wav"));
        errorSoundRemove.setVolume(0.25f);
        errorSoundRemove.play();
        qDebug() << errorSoundRemove.status();
        errorMsg->showMessage(tr("Erreur."));
    }
}
/*
* Méthode SLOT permetant de réactualiser la grille et de quitter le formulaire de suppression de l'évènement si la requête vers la base de données a aboutie
**/
void RemoveCaseWindow::replyFinishedRemove(QNetworkReply* resp) {
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
        mainWindowRemove->loadCalendar(4, groupid, caseId.at(0).toInt(), currentDate);
        RemoveCaseWindow::setVisible(false);
    } else {
         QErrorMessage* errorMsg = new QErrorMessage(this);
         errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
     }
}