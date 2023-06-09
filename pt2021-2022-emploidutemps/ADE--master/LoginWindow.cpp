#include "LoginWindow.h"
#include "ADE.h"

#include <QtNetwork>
#include <QtMultimedia>
#include <QShortcut>

/*
* Classe permettant la connexion vers la base de données
**/

/*
* Constructeur de la classe permettant la connexion vers la base de données
**/
LoginWindow::LoginWindow(QWidget *parent)
	: QWidget(parent)
{
    login = new QLineEdit;
    password = new QLineEdit;
    password->setEchoMode(QLineEdit::Password);
    groupidSelect = new QComboBox();
    //getGroup();
    QLabel* label_img = new QLabel(this);
    QPixmap* p = new QPixmap("ade++.png");
    label_img->setPixmap(p->scaled(250,250, Qt::KeepAspectRatio));
    label_img->resize(10, 100);
    QPushButton* logButton = new QPushButton("Connecter", this);
    QPushButton* createButton = new QPushButton("Creer un compte admin", this);
    QPushButton* quitButton = new QPushButton("Quitter", this);

    QFormLayout* layout = new QFormLayout;
    notifyText = new QLabel;
    notifyText->setAlignment(Qt::AlignCenter);
    textlayout = new QVBoxLayout;
    QLabel *welcomeText = new QLabel(tr("Bienvenue sur ADE++"));
    QWidget* textWidget = new QWidget;
    textlayout->addWidget(label_img);
    textlayout->addWidget(welcomeText);
    textWidget->setLayout(textlayout);
    welcomeText->setAlignment(Qt::AlignCenter);
    layout->addRow(textWidget);
    layout->addRow("Votre login", login);
    layout->addRow("Votre mot de passe", password);
    layout->addRow(logButton);
    layout->addRow(createButton);
    layout->addRow(quitButton);
    setLayout(layout);

    logButton->setAutoDefault(true);

    QObject::connect(logButton, SIGNAL(clicked()), this, SLOT(connection()));
    QObject::connect(createButton, SIGNAL(clicked()), this, SLOT(createAccount()));
    QObject::connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    LoginWindow::setVisible(true);
}

LoginWindow::~LoginWindow()
{
}

/*
* Méthode permetant l'envoi de requête de connexion vers la base de données
**/
void LoginWindow::connection()
{
        textlayout->removeWidget(notifyText);
        effect.setSource(QUrl("https://dwarves.iut-fbleau.fr/~barbey/EDT/clci.wav"));
        effect.setVolume(0.25f);
        effect.play();
        qDebug() << effect.status();

        QNetworkAccessManager* manager = new QNetworkAccessManager(this);
        QHttpMultiPart* http = new QHttpMultiPart(QHttpMultiPart::FormDataType);

        QHttpPart receiptPart;
        receiptPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"login\""));
        receiptPart.setBody(login->text().toUtf8());

        QHttpPart receiptPart2;
        receiptPart2.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"pwd\""));
        receiptPart2.setBody(password->text().toUtf8());

        QHttpPart receiptPart3;
        receiptPart3.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"Connect\""));
        receiptPart3.setBody("true");

        http->append(receiptPart);
        http->append(receiptPart2);
        http->append(receiptPart3);
  
            QNetworkReply* repl = manager->post(QNetworkRequest(QUrl("https://dwarves.iut-fbleau.fr/~barbey/EDT/script1.php")), http);
            connect(manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(replyFinished(QNetworkReply*)));
}

/*
*  Méthode SLOT permetant de ouvrir la fenêtre principale après la connexion
**/
void LoginWindow::replyFinished(QNetworkReply* resp) {
    QVariant status_code = resp->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(status_code.isValid()) {
        QString status = status_code.toString();
        QJsonParseError jsonError;
        QByteArray anwser = resp->readAll();
        QJsonDocument json = QJsonDocument::fromJson(anwser, &jsonError);
        if (jsonError.error != QJsonParseError::NoError) {
            qDebug() << "Error: " << jsonError.errorString(); 
        }
        qDebug() << status;
        
        if (json.object().value("id").toArray().at(0).toString() != "") {
            QString idAdmin = json.object().value("id").toArray().at(0).toString();
            QString id = json.object().value("id").toArray().at(1).toString();
            QString groupid = json.object().value("groupid").toArray().at(0).toString();
            ADE* w = new ADE(login->text(), idAdmin, id, groupid, this); //On pouvait utiliser un singleton aussi

            LoginWindow::setVisible(false);
        }
        else if (json.object().value("id").toArray().at(0).toString() == "") {
            notifyText->setText("Erreur : Login ou mot de passe incorrect.");
            notifyText->setStyleSheet("QLabel { color : red; }");
            textlayout->addWidget(notifyText);
        }
    }
    else {
        QErrorMessage* errorMsg = new QErrorMessage(this);
        effect.setSource(QUrl("error.wav"));
        effect.setVolume(0.25f);
        effect.play();
        qDebug() << effect.status();
        errorMsg->showMessage("Connexion impossible à la base de données. Vérifiez votre connexion internet.");
    }
}

void LoginWindow::getGroup() {
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QHttpMultiPart* http = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart receiptPart;
    receiptPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"GetGroups\""));
    receiptPart.setBody("true");

    http->append(receiptPart);

    QNetworkReply* repl = manager->post(QNetworkRequest(QUrl("https://dwarves.iut-fbleau.fr/~barbey/EDT/script1.php")), http);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(replyFinishedGroups(QNetworkReply*)));
}

/*
* Méthode SLOT permetant de définir quoi faire lorsque la requête de la tentative de création a été faite
**/
void LoginWindow::replyFinishedGroups(QNetworkReply* resp) {
    QVariant status_code = resp->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if (status_code.isValid()) {
        // Print or catch the status code
        QString status = status_code.toString(); // or status_code.toInt();
        qDebug() << status;
        QJsonParseError jsonError;
        QJsonDocument json = QJsonDocument::fromJson(resp->readAll(), &jsonError);
        if (jsonError.error != QJsonParseError::NoError) {
            qDebug() << "Error: " << jsonError.errorString();
        }
        resp->deleteLater();
        QJsonValue groups = json.object().value("groups");
        QJsonArray groupsi = groups.toArray();
        for (int i = 0; i < groupsi.size(); i++) {
            groupids.push_back(groupsi.at(i).toObject()["groupid"].toString().toInt());
            groupidSelect->addItem(groupsi.at(i).toObject()["name"].toString());
        }

    }
}

/*
* Méthode permetant de créer un compte administrateur
**/
void LoginWindow::createAccount() {
    textlayout->removeWidget(notifyText);
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QHttpMultiPart* http = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart receiptPart;
    receiptPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"login\""));
    receiptPart.setBody(login->text().toUtf8());

    QHttpPart receiptPart2;
    receiptPart2.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"pwd\""));
    receiptPart2.setBody(password->text().toUtf8());

    QHttpPart receiptPart3;
    receiptPart3.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"Create\""));
    receiptPart3.setBody("true");


    
    http->append(receiptPart);
    http->append(receiptPart2);
    http->append(receiptPart3);


    QNetworkReply* repl = manager->post(QNetworkRequest(QUrl("https://dwarves.iut-fbleau.fr/~barbey/EDT/script1.php")), http);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(replyFinishedCreate(QNetworkReply*)));

    
}

/*
* Méthode SLOT permetant de définir quoi faire lorsque la requête de la tentative de création a été faite
**/
void LoginWindow::replyFinishedCreate(QNetworkReply* resp) {
    QVariant status_code = resp->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if (status_code.isValid()) {
        QString status = status_code.toString();
        qDebug() << status;
        QByteArray data = resp->readAll();
        if (data == "true") {
            notifyText->setText("Compte cree.");
            notifyText->setStyleSheet("QLabel { color : green; }");
            textlayout->addWidget(notifyText);
        }
        else if (data == "false") {
            notifyText->setText("Compte déjà cree.");
            notifyText->setStyleSheet("QLabel { color : red; }");
            textlayout->addWidget(notifyText);
        }
    }
}