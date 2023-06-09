#include "ADE.h"

#include <QCloseEvent>
#include <QtNetwork>
#include <QtWidgets>
#include <vector>
#include <QDIR>
#include "FileExplorer.h"
#include "AddCaseWindow.h"
#include "EditCaseWindow.h"
#include "RemoveCaseWindow.h"
#include <QCloseEvent>
#include <AddTeacherWindow.h>
#include <EditTeacherWindow.h>
#include <AddPlaceWindow.h>
#include <EditPlaceWindow.h>
#include <AddGroupWindow.h>
#include <EditGroupWindow.h>
#include <RemoveGroupWindow.h>
#include <RemovePlaceWindow.h>
#include <RemoveTeacherWindow.h>

/**
* Classe qui gère la fenêtre principale où est affichée la grille
*/


/*
* Constructeur de la classe ADE
**/
ADE::ADE(QString login, QString idAdmin, QString id, QString groupid, LoginWindow* loginWindowP, QWidget *parent)
    : QMainWindow(parent)
{
    resize(1500, 1500);
    ADE::idAdmin = idAdmin;
    ADE::groupid = groupid;
    ADE::id = id;
    ADE::login = login;
    if (idAdmin == "admin") {
        ADE::welcomeText = new QLabel(tr("Choisir un groupe ci dessous.\nSi vous n'avez pas de groupe, contactez un administrateur avec les droits."));
    }
    else {
        ADE::welcomeText = new QLabel(tr("Bienvenue sur ADE++, ") + login + " \t(Votre identifiant est : " + id + " et vous etes : " + idAdmin + ")");
    }
    welcomeText->setFont(QFont("Arial", 12, QFont::Bold));
    welcomeText->setAlignment(Qt::AlignCenter);
    table = new QTableWidget(288, 7, this);
    table->setStyleSheet("selection-background-color: qlineargradient(x1: 0, y1: 0, x2: 0.5, y2: 0.5, stop: 0 #0cadeb, stop: 1 blue); ");
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    verticalHeader = table->verticalHeader();
    QString stylesheet = "::section{Background-color:qlineargradient(x1: 0, y1: 0, x2: 0.5, y2: 0.5, stop: 0 #799fe8, stop: 1 #4d78ca); color: white; border-radius:14px;}";
    table->horizontalHeader()->setStyleSheet(stylesheet);
    verticalHeader->setDefaultSectionSize(1);
    verticalHeader->sectionResizeMode(QHeaderView::Fixed);
    horizontalHeader = table->horizontalHeader();
    horizontalHeader->setDefaultSectionSize(1);
    horizontalHeader->sectionResizeMode(QHeaderView::Fixed);
    horizontalHeader->setStretchLastSection(true);

    QTableWidgetItem* headerV[288]{};
    int compt = 0;
    for (int i = 0; i < 288;i++) {
        headerV[i] = new QTableWidgetItem;
        if (i % 12 == 0) {
            headerV[i]->setText(QString::number(compt)+"h");
            headerV[i]->setFont(QFont("arial", 9, QFont::Bold));
            compt = compt + 1;
            table->setVerticalHeaderItem(i, headerV[i]);
        }
        else {
            headerV[i]->setText("");
            table->setVerticalHeaderItem(i, headerV[i]);
        }
    }
    
    currentDate = QDateTime::currentDateTime().date();
    int todayDate = currentDate.dayOfWeek();
    if (todayDate != 1) {
        currentDate.setDate(currentDate.year(), currentDate.month(), ((currentDate.day() + 1) - todayDate));
    }

    loginWindow = loginWindowP;

    header = new QTableWidgetItem();
    header->setText(locale.toString(currentDate));
    table->setHorizontalHeaderItem(0, header);
    header2 = new QTableWidgetItem();
    header2->setText(locale.toString(currentDate.addDays(1)));
    table->setHorizontalHeaderItem(1, header2);
    header3 = new QTableWidgetItem();
    header3->setText(locale.toString(currentDate.addDays(2)));
    table->setHorizontalHeaderItem(2, header3);
    header4 = new QTableWidgetItem();
    header4->setText(locale.toString(currentDate.addDays(3)));
    table->setHorizontalHeaderItem(3, header4);
    header5 = new QTableWidgetItem();
    header5->setText(locale.toString(currentDate.addDays(4)));
    table->setHorizontalHeaderItem(4, header5);
    header6 = new QTableWidgetItem();
    header6->setText(locale.toString(currentDate.addDays(5)));
    table->setHorizontalHeaderItem(5, header6);
    header7 = new QTableWidgetItem();
    header7->setText(locale.toString(currentDate.addDays(6)));
    table->setHorizontalHeaderItem(6, header7);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int i = 0; i < 7; i++) {
        if ((table->horizontalHeaderItem(i)->text() == locale.toString(QDateTime::currentDateTime().date()))) {
            table->horizontalHeaderItem(i)->setFont(QFont("arial", 9, QFont::Bold));
        }
    }

    QWidget* northButtons = new QWidget;
    QHBoxLayout* northButtonLayout = new QHBoxLayout;
    QPushButton* previousButton = new QPushButton("&<<");
    selectedTime = new QPushButton(tr("Semaine du ") + locale.toString(QDateTime::currentDateTime()));
    QPushButton* nextButton = new QPushButton("&>>");
    northButtonLayout->addWidget(previousButton);
    northButtonLayout->addWidget(selectedTime);
    northButtonLayout->addWidget(nextButton);
    northButtons->setLayout(northButtonLayout);

    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(3);
    effect->setXOffset(0);
    effect->setYOffset(0);
    QGraphicsOpacityEffect opacity = new QGraphicsOpacityEffect(effect);
    opacity.setOpacity(0.5);
    effect->setColor(Qt::black);
    QGraphicsDropShadowEffect* effect2 = new QGraphicsDropShadowEffect;
    effect2->setBlurRadius(3);
    effect2->setXOffset(0);
    effect2->setYOffset(0);
    QGraphicsOpacityEffect opacity2 = new QGraphicsOpacityEffect(effect2);
    opacity2.setOpacity(0.5);
    effect2->setColor(Qt::black);
    QGraphicsDropShadowEffect* effect3 = new QGraphicsDropShadowEffect;
    effect3->setBlurRadius(3);
    effect3->setXOffset(0);
    effect3->setYOffset(0);
    QGraphicsOpacityEffect opacity3 = new QGraphicsOpacityEffect(effect3);
    opacity3.setOpacity(0.5);
    effect3->setColor(Qt::black);
    previousButton->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #1f4183, stop: .4 #2642c1, stop: .5 #132b9a, stop: 1 #1f4183); color: white; border-radius: 5px; padding: 10px;");
    selectedTime->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #1f4183, stop: .4 #266bc1, stop: .5 #132b9a, stop: 1 #1f4183); color: white; border-radius: 5px; padding: 10px; ");
    nextButton->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #1f4183, stop: .4 #2642c1, stop: .5 #132b9a, stop: 1 #1f4183); color: white; border-radius: 5px; padding: 10px; ");
    previousButton->setGraphicsEffect(effect);
    selectedTime->setGraphicsEffect(effect2);
    nextButton->setGraphicsEffect(effect3);

    QWidget* southButtons = new QWidget;
    QHBoxLayout* southButtonLayout = new QHBoxLayout;
    QPushButton* addButton = new QPushButton(tr("&Ajouter"));
    QPushButton* editButton = new QPushButton(tr("&Modifier"));
    QPushButton* removeButton = new QPushButton(tr("&Supprimer"));

    if (idAdmin == "admin") {
        QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect;
        effect->setBlurRadius(3);
        effect->setXOffset(0);
        effect->setYOffset(0);
        QGraphicsOpacityEffect opacity = new QGraphicsOpacityEffect(effect);
        opacity.setOpacity(0.5);
        effect->setColor(Qt::black);
        QGraphicsDropShadowEffect* effect2 = new QGraphicsDropShadowEffect;
        effect2->setBlurRadius(3);
        effect2->setXOffset(0);
        effect2->setYOffset(0);
        QGraphicsOpacityEffect opacity2 = new QGraphicsOpacityEffect(effect2);
        opacity.setOpacity(0.5);
        effect2->setColor(Qt::black);
        QGraphicsDropShadowEffect* effect3 = new QGraphicsDropShadowEffect;
        effect3->setBlurRadius(3);
        effect3->setXOffset(0);
        effect3->setYOffset(0);
        QGraphicsOpacityEffect opacity3 = new QGraphicsOpacityEffect(effect3);
        opacity.setOpacity(0.5);
        effect3->setColor(Qt::black);

        addButton->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #1f8340, stop: .4 #09ac3f, stop: .5 #07802f, stop: 1 #1f8340); color: white; border-radius: 5px; padding: 10px;");
        editButton->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #1f4183, stop: .4 #2642c1, stop: .5 #132b9a, stop: 1 #1f4183); color: white; border-radius: 5px; padding: 10px;");
        removeButton->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #ac0909, stop: .4 #d03030, stop: .5 #b90e0e, stop: 1 #ac0909); color: white; border-radius: 5px; padding: 10px;");
        addButton->setGraphicsEffect(effect);
        removeButton->setGraphicsEffect(effect2);
        editButton->setGraphicsEffect(effect3);
        southButtonLayout->addWidget(addButton);
        southButtonLayout->addWidget(editButton);
        southButtonLayout->addWidget(removeButton);
        southButtons->setLayout(southButtonLayout);
    }
    QPushButton* selectedGroupButton;
    mainCalendar = new QCalendarWidget;
    mainCalendar->setVisible(false);
    ADE::isCalendarOpen = false;
    centralLayout = new QVBoxLayout;
    if(idAdmin == "admin"){
        groupChoice = new QWidget;
        groupChoiceLayout = new QHBoxLayout;
        groupList = new QComboBox;
        selectedGroupButton = new QPushButton(tr("Selectionner"));
        selectedGroupButton->setStyleSheet("background-color: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #696969, stop: .4 #808080, stop: .5 #A9A9A9, stop: 1 #696969); color: white; border-radius: 5px; padding: 10px; ");
        getGroup();
        for (int nb = 0; nb < tableaiGroupe.size(); nb++) {
            groupList->addItem(tableaiGroupe.at(nb)["name"].toString());
            groupList->setItemData(nb, tableaiGroupe.at(nb)["groupid"].toString());
        }
        groupChoiceLayout->addWidget(groupList);
        groupChoiceLayout->addWidget(selectedGroupButton);
        groupChoice->setLayout(groupChoiceLayout);
        connect(selectedGroupButton, SIGNAL(clicked()), this, SLOT(loadCalendarLaunch()));
    }
    
    centralLayout->addWidget(welcomeText);
    centralLayout->addWidget(northButtons);
    if (idAdmin == "admin") {
        centralLayout->addWidget(groupChoice);
    }
    centralLayout->addWidget(mainCalendar);
    centralLayout->addWidget(table);
    centralLayout->addWidget(southButtons);
    QWidget *centralElements = new QWidget;
    centralElements->setLayout(centralLayout);

    ADE::southButtons = southButtons;
    ADE::northButtons = northButtons;

    QMenu *fileMenu = menuBar()->addMenu(tr("&Fichier"));
    QMenu* manage;

    connect(selectedTime, SIGNAL(clicked()), this, SLOT(viewCalendar()));
    
    QMenu* managePlace;
    QMenu* manageGroup;
    QMenu* manageTeacher;
    QAction* managePlaceAdd;
    QAction* manageGroupAdd;
    QAction* manageTeacherAdd;
    QAction* managePlaceModify;
    QAction* manageGroupModify;
    QAction* manageTeacherModify;
    QAction* managePlaceRemove;
    QAction* manageGroupRemove;
    QAction* manageTeacherRemove;

    if (idAdmin == "admin") {

        connect(addButton, SIGNAL(clicked()), this, SLOT(addCase()));
        connect(editButton, SIGNAL(clicked()), this, SLOT(editCase()));
        connect(removeButton, SIGNAL(clicked()), this, SLOT(removeCase()));
        manage = menuBar()->addMenu(tr("Gestion"));
        managePlace = manage->addMenu(tr("Lieu"));
        manageGroup = manage->addMenu(tr("Groupe"));
        manageTeacher = manage->addMenu(tr("Intervenant"));

        managePlaceAdd = new QAction(tr("Ajouter..."), this);
        manageGroupAdd = new QAction(tr("Ajouter..."), this);
        manageTeacherAdd = new QAction(tr("Ajouter..."), this);
        managePlaceModify = new QAction(tr("Modifier..."), this);
        manageGroupModify = new QAction(tr("Modifier..."), this);
        manageTeacherModify = new QAction(tr("Modifier..."), this);
        managePlaceRemove = new QAction(tr("Supprimer..."), this);
        manageGroupRemove = new QAction(tr("Supprimer..."), this);
        manageTeacherRemove = new QAction(tr("Suprimer..."), this);

        managePlace->addAction(managePlaceAdd);
        managePlace->addAction(managePlaceModify);
        managePlace->addAction(managePlaceRemove);
        manageGroup->addAction(manageGroupAdd);
        manageGroup->addAction(manageGroupModify);
        manageGroup->addAction(manageGroupRemove);
        manageTeacher->addAction(manageTeacherAdd);
        manageTeacher->addAction(manageTeacherModify);
        manageTeacher->addAction(manageTeacherRemove);

        connect(managePlaceAdd, SIGNAL(triggered()), this, SLOT(placeAdd()));
        connect(managePlaceModify, SIGNAL(triggered()), this, SLOT(placeModify()));
        connect(managePlaceRemove, SIGNAL(triggered()), this, SLOT(placeRemove()));
        connect(manageGroupAdd, SIGNAL(triggered()), this, SLOT(groupAdd()));
        connect(manageGroupModify, SIGNAL(triggered()), this, SLOT(groupModify()));
        connect(manageGroupRemove, SIGNAL(triggered()), this, SLOT(groupRemove()));
        connect(manageTeacherAdd, SIGNAL(triggered()), this, SLOT(teacherAdd()));
        connect(manageTeacherModify, SIGNAL(triggered()), this, SLOT(teacherModify()));
        connect(manageTeacherRemove, SIGNAL(triggered()), this, SLOT(teacherRemove()));
    }

    QMenu* helpMenu = menuBar()->addMenu(tr("&Aide"));

    QAction* openAction = new QAction(tr("&Ouvrir un fichier"), this);
    fileMenu->addAction(openAction);
    connect(openAction, SIGNAL(triggered()), this, SLOT(openfile()));
    openAction->setShortcut(QKeySequence("Ctrl+N"));

    fileMenu->addSeparator();

    QAction* reconnectAction = new QAction(tr("&Changer de compte"), this);
    fileMenu->addAction(reconnectAction);
    connect(reconnectAction, SIGNAL(triggered()), this, SLOT(reconnect()));
    reconnectAction->setShortcut(QKeySequence("Ctrl+R"));

    QAction* quitAction = new QAction(tr("&Quitter"), this);
    fileMenu->addAction(quitAction);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    quitAction->setShortcut(QKeySequence("Ctrl+Q"));

    QAction* aboutQtAction = new QAction(tr("&A propos de Qt"), this);
    helpMenu->addAction(aboutQtAction);
    connect(aboutQtAction, SIGNAL(triggered()), this, SLOT(aboutQt()));

    QAction* aboutAction = new QAction(tr("&A propos de ce logiciel"), this);
    helpMenu->addAction(aboutAction);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    setCentralWidget(centralElements);

    connect(nextButton, SIGNAL(clicked()), this, SLOT(changeWeekAdd()));
    connect(previousButton, SIGNAL(clicked()), this, SLOT(changeWeekLess()));
    if (idAdmin != "admin") {
        ADE::loadCalendar(1, groupid.toInt(), currentDate);
    }
    else {
        table->setVisible(false);
        southButtons->setVisible(false);
        northButtons->setVisible(false);
        resize(800, 200);

    }
    table->verticalScrollBar()->setValue(80);
    show();
}
/*
* Méthode SLOT permetant d'ouvrir un fichier pour l'exportation d'un calendrier
**/
void ADE::openfile() {
    FileExplorer explorer = new FileExplorer();
    /*QString fileName = QFileDialog::getOpenFileName(this, (tr("Ouvrir un fichier")),
        "*.ics",
        ("*.ics"));*/
}

/*
* Méthode SLOT permetant de charger la grille après choix du groupe lorsque l'on est connecté en admin
**/
void ADE::loadCalendarLaunch() {
    groupid = groupList->itemData(groupList->currentIndex()).toString();
    if (ADE::idAdmin == "admin") {
        ADE::welcomeText->setText((tr("Bienvenue sur ADE++, ") + ADE::login + " \t(Votre identifiant est : " + ADE::id + " et vous etes un : " + ADE::idAdmin + ")"));
        table->setVisible(true);
        southButtons->setVisible(true);
        northButtons->setVisible(true);
        resize(1500, 1500);

    }
    loadCalendar(1, groupid.toInt(), currentDate);
}

/*
* Méthode SLOT permetant d'actualiser les dates lors de la sélection d'une sur le petit calendrier
**/
void ADE::whenDateSelected()
{
    for (int i = 0; i < 7; i++) {
        if ((table->horizontalHeaderItem(i)->text() == locale.toString(QDateTime::currentDateTime().date()))) {
            table->horizontalHeaderItem(i)->setFont(QFont("arial"));
        }
    }
    currentDate = mainCalendar->selectedDate();
    int todayDate = currentDate.dayOfWeek();
    if (todayDate != 1) {
        currentDate.setDate(currentDate.year(), currentDate.month(), ((currentDate.day() + 1) - todayDate));
    }
    selectedTime->setText(tr("Semaine du ") + locale.toString(currentDate));
    changeHeaderDates();
    loadCalendar(2, groupid.toInt(), currentDate);
    ADE::isCalendarOpen = false;
    mainCalendar->setVisible(false);
}

/*
* Méthode SLOT permetant d'afficher un petit calendrier pour choisir une date plus rapidement
**/
void ADE::viewCalendar() {
    if (ADE::isCalendarOpen == true) {
        mainCalendar->setVisible(false);
        ADE::isCalendarOpen = false;
    }
    else {
        mainCalendar->setVisible(true);
        ADE::isCalendarOpen = true;
        mainCalendar->setMinimumDate(QDate(1900, 1, 1));
        mainCalendar->setMaximumDate(QDate(3000, 1, 1));
        mainCalendar->setGridVisible(true);
        connect(mainCalendar, SIGNAL(clicked(const QDate&)),
            this, SLOT(whenDateSelected()));
    }
}

/*
* Méthode SLOT permetant de charger la grille sur l'interface graphique
**/
void ADE::loadCalendar(int loadCode, int groupid, QDate idDay)
{
        selectedTime->setText(tr("Semaine du ") + locale.toString(idDay));
        //tab.clear();
        QNetworkAccessManager networkAccessManager;
        if (idAdmin != "admin") {
            groupid = id.toInt();
        }
        QNetworkRequest networkRequest(QUrl(QString("https://dwarves.iut-fbleau.fr/~barbey/EDT/script1.php?VarGrpId=true&groupid=" + QString::number(groupid) + "&date=" + idDay.toString(Qt::ISODate) + "&type=" + idAdmin)));
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
                errorSound.setSource(QUrl::fromLocalFile("error.wav"));
                errorSound.setVolume(0.25f);
                errorSound.play();
                qDebug() << errorSound.status();
                errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
            }

            QJsonValue edt = json.object().value("edt");
            QJsonArray tableai = edt.toArray();
            if (loadCode == 1 || loadCode == 2 || loadCode == 3) {
                tab.clear();
                for (int i = 0; i < 288; i++) {
                    for (int y = 0; y < 7; y++) {
                        table->setSpan(i, y, 1, 1);
                        delete table->item(i, y);
                    }
                }
                for (int i = 0; i < tableai.size(); i++) {
                    for (int y = 0; y < 7; y++) {
                        if (tableai.at(i).toObject()["date"].toString() == currentDate.addDays(y).toString("yyyy-MM-dd")) {
                            QString str = tableai.at(i).toObject()["subject"].toString();
                            tab.push_back(tableai.at(i).toObject());
                            QString dateStr = tableai.at(i).toObject()["date"].toString();
                            QDate date;
                            QStringList dateList = dateStr.split("-", Qt::SkipEmptyParts);
                            date.setDate(dateList.at(0).toInt(), dateList.at(1).toInt(), dateList.at(2).toInt());
                            int day = date.dayOfWeek();
                            QString hourDebutStr = tableai.at(i).toObject()["hour"].toString();
                            QString hourFinStr = tableai.at(i).toObject()["hourfin"].toString();
                            QString minDebutStr = tableai.at(i).toObject()["mindebut"].toString();
                            QString minuteFinStr = tableai.at(i).toObject()["minutefin"].toString();
                            QString teacher = tableai.at(i).toObject()["9"].toString();
                            QString place = tableai.at(i).toObject()["nom"].toString();
                            int hD = hourDebutStr.toInt()*12;
                            int hF = hourFinStr.toInt()*12;
                            int mD = minDebutStr.toInt()/5;
                            int mF = minuteFinStr.toInt()/5;
                            QTableWidgetItem* item = new QTableWidgetItem();
                            getPlace();
                            getTeacher();
                            QString reelPlace = place;
                            for (int i = 0; i < places.size(); i++) {
                                if (places.at(i).toObject()["id"].toString() == place) {
                                    reelPlace = places.at(i).toObject()["nom"].toString();
                                }
                            }
                            QString reelTeacher = teacher;
                            for (int i = 0; i < teachers.size(); i++) {
                                if (teachers.at(i).toObject()["id"].toString() == teacher) {
                                    reelPlace = teachers.at(i).toObject()["nom"].toString();
                                }
                            }
                            item->setText(str+'\n'+reelPlace+'\n'+reelTeacher);
                            QLinearGradient colorGradient = QLinearGradient(0, 0, 100, 100);
                            colorGradient.setSpread(QGradient::ReflectSpread);
                            int r = rand() % 255;
                            int g = rand() % 255;
                            int b = rand() % 255;
                            colorGradient.setColorAt(0, QColor(r, g, b, 255));
                            colorGradient.setColorAt(1, QColor(r+20, g+20, b+20, 255));
                            item->setBackground(colorGradient);
                            item->setForeground(Qt::white);
                            item->setTextAlignment(Qt::AlignCenter);
                            item->setFont(QFont("arial", 10));
                            table->setItem(hD+mD, day - 1, item);
                            for (auto& v : tab) {
                               table->item(hD+mD, day - 1)->setData(Qt::UserRole, v);
                            }
                            table->setSpan(hD+mD, day-1, (hF+mF)-(hD + mD), 1);
                        }
                    }
                }
                spanGrid();
                networkReply->deleteLater();
            }
        }
        else {
            QErrorMessage* errorMsg = new QErrorMessage(this);
            errorSound.setSource(QUrl::fromLocalFile("error.wav"));
            errorSound.setVolume(0.25f);
            errorSound.play();
            qDebug() << errorSound.status();
            errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
        }
}

/*
* Méthode permetant de charger la grille lorsque l'on supprime un évènement
**/
void ADE::loadCalendar(int loadCode, int groupid, int id, QDate idDay)
{
   if (loadCode == 4) {
        ADE::loadCalendar(loadCode, groupid, idDay);
        for (int i = 0; i < tab.size(); i++) {
            int itemCheckId = tab.at(i)["id"].toString().toInt();
            if (itemCheckId == id) {
                QString dateStr = tab.at(i)["date"].toString();
                QDate date;
                QStringList dateList = dateStr.split("-", Qt::SkipEmptyParts);
                date.setDate(dateList.at(0).toInt(), dateList.at(1).toInt(), dateList.at(2).toInt());
                int day = date.dayOfWeek();
                QString hourDebutStr = tab.at(i)["hour"].toString();
                QString hourFinStr = tab.at(i)["hourfin"].toString();
                QString minDebutStr = tab.at(i)["mindebut"].toString();
                QString minuteFinStr = tab.at(i)["minutefin"].toString();
                int hD = hourDebutStr.toInt() * 12;
                int hF = hourFinStr.toInt() * 12;
                int mD = minDebutStr.toInt() / 5;
                int mF = minuteFinStr.toInt() / 5;
                tab.clear();
                delete table->item(hD + mD, day - 1);
                table->setSpan(hD + mD, day - 1, 1, 1);
            }
        }
    }
}

/*
* Méthode SLOT permetant d'actualiser les dates de la semaine de la grille
**/
void ADE::changeHeaderDates() {
    header->setText(locale.toString(currentDate));
    header2->setText(locale.toString(currentDate.addDays(1)));
    header3->setText(locale.toString(currentDate.addDays(2)));
    header4->setText(locale.toString(currentDate.addDays(3)));
    header5->setText(locale.toString(currentDate.addDays(4)));
    header6->setText(locale.toString(currentDate.addDays(5)));
    header7->setText(locale.toString(currentDate.addDays(6)));
    for (int i = 0; i < 7; i++) {
        if ((table->horizontalHeaderItem(i)->text() == locale.toString(QDateTime::currentDateTime().date()))) {
            table->horizontalHeaderItem(i)->setFont(QFont("arial", 9, QFont::Bold));
        }
    }
}

/*
* Méthode SLOT permetant d'avancer d'une semaine
**/
void ADE::changeWeekAdd() {
    for (int i = 0; i < 7; i++) {
        if ((table->horizontalHeaderItem(i)->text() == locale.toString(QDateTime::currentDateTime().date()))) {
            table->horizontalHeaderItem(i)->setFont(QFont("arial"));
        }
    }
    currentDate = currentDate.addDays(7);
    ADE::loadCalendar(2, groupid.toInt(), currentDate);
    table->verticalScrollBar()->setValue(80);
    changeHeaderDates();
    
}

/*
* Méthode SLOT permetant de reculer d'une semaine
**/
void ADE::changeWeekLess() {
    for (int i = 0; i < 7; i++) {
        if ((table->horizontalHeaderItem(i)->text() == locale.toString(QDateTime::currentDateTime().date()))) {
            table->horizontalHeaderItem(i)->setFont(QFont("arial"));
        }
    }
    currentDate = currentDate.addDays(-7);
    ADE::loadCalendar(2, groupid.toInt(), currentDate);
    table->verticalScrollBar()->setValue(80);
    changeHeaderDates();
}

/*
* Méthode SLOT permetant d'ajouter un évènement
**/
void ADE::addCase() {
    int r = table->selectionModel()->currentIndex().row();
    int h = table->selectionModel()->currentIndex().column();
    AddCaseWindow* addCaseWindow = new AddCaseWindow(r, h, id.toInt(), groupid.toInt(), this);
}

/*
* Méthode SLOT permetant d'éditer un évènement
**/
void ADE::editCase() {
    int r = table->selectionModel()->currentIndex().row();
    int h = table->selectionModel()->currentIndex().column();
    QModelIndex item = table->selectionModel()->currentIndex();
    std::vector<QString> caseId;
    QString tableai = item.data(Qt::UserRole).toJsonObject()["id"].toString();
    QString hour = item.data(Qt::UserRole).toJsonObject()["hourdebut"].toString();
    QString hourFin = item.data(Qt::UserRole).toJsonObject()["hourfin"].toString();
    QString minDebut = item.data(Qt::UserRole).toJsonObject()["mindebut"].toString();
    QString minuteFin = item.data(Qt::UserRole).toJsonObject()["minutefin"].toString();
    QString date = item.data(Qt::UserRole).toJsonObject()["date"].toString();
    QString tableas = item.data(Qt::UserRole).toJsonObject()["subject"].toString();
    QString tableat = item.data(Qt::UserRole).toJsonObject()["type"].toString();
    QString prof = item.data(Qt::UserRole).toJsonObject()["idprof"].toString();
    QString salle = item.data(Qt::UserRole).toJsonObject()["idlieu"].toString();
    QString tableag = item.data(Qt::UserRole).toJsonObject()["groupid"].toString();
    EditCaseWindow* editCaseWindow = new EditCaseWindow(id.toInt(), tableai.toInt(), tableag.toInt(), prof, salle, tableas, hour.toInt(), hourFin.toInt(), minDebut.toInt(), minuteFin.toInt(), date, tableat, this);
}

/*
* Méthode SLOT permetant de supprimer un évènement
**/
void ADE::removeCase() {
    QModelIndex item = table->selectionModel()->currentIndex();
    std::vector<QString> caseId;
    QString tableai = item.data(Qt::UserRole).toJsonObject()["id"].toString();
    caseId.push_back(tableai);
    RemoveCaseWindow* removeCaseWindow = new RemoveCaseWindow(caseId, groupid.toInt(), this);
}

/*
* Méthode permetant d'obtenir tous les groupes depuis la base de données
**/
void ADE::getGroup() {
    QNetworkAccessManager networkAccessManager;
    QNetworkRequest networkRequest(QUrl(QString("https://dwarves.iut-fbleau.fr/~barbey/EDT/script1.php?getgroupe=true&idadmin=" + id)));
    QNetworkReply* networkReply = networkAccessManager.get(networkRequest);
    QEventLoop eventLoop;
    QObject::connect(networkReply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    QVariant status_code = networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if (status_code.isValid()) {
        QString status = status_code.toString();
        qDebug() << status;
        QJsonParseError jsonError;
        QJsonDocument json = QJsonDocument::fromJson(networkReply->readAll(), &jsonError);
        if (jsonError.error != QJsonParseError::NoError) {
            qDebug() << "Error: " << jsonError.errorString();
        }
        networkReply->deleteLater();
        QJsonValue groups = json.object().value("groups");
        tableaiGroupe = groups.toArray();
    }
    else {
        QErrorMessage* errorMsg = new QErrorMessage(this);
        errorSound.setSource(QUrl::fromLocalFile("error.wav"));
        errorSound.setVolume(0.25f);
        errorSound.play();
        qDebug() << errorSound.status();
        errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
    }
}

/*
* Méthode permetant d'obtenir tous les profs depuis la base de données
**/
void ADE::getTeacher() {
    QNetworkAccessManager networkAccessManager;
    QNetworkRequest networkRequest(QUrl(QString("https://dwarves.iut-fbleau.fr/~barbey/EDT/script1.php?getprof=true&idadmin=" + id)));
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
            errorSound.setSource(QUrl::fromLocalFile("error.wav"));
            errorSound.setVolume(0.25f);
            errorSound.play();
            qDebug() << errorSound.status();
            errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
        }

        QJsonValue groups = json.object().value("prof");
        teachers = groups.toArray();
    }
    else {
        QErrorMessage* errorMsg = new QErrorMessage(this);
        errorSound.setSource(QUrl::fromLocalFile("error.wav"));
        errorSound.setVolume(0.25f);
        errorSound.play();
        errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
    }
}

/*
* Méthode permetant de gérer l'affichage des cellules de la grille pour s'adapter à un évenement et aussi pour les créneaux horaires
**/
void ADE::spanGrid() {
    int compt;
    int flag;
    for (int z = 0; z < 7; z++) {
        for (int i = 0; i < 288; i++) {
            if (i % 12 == 0) {
                flag = 0;
                compt = 0;
                for (int y = 0; y < 12; y++) {
                    QTableWidgetItem* item = table->itemAt(i, y);
                    if (item != NULL) {
                        flag = 1;
                    }
                    compt = compt + 1;
                }
                if (flag == 0) {
                    //table->setSpan(i, z, compt, 1);
                }
            }

        }
    }
}

/*
* Méthode permetant d'obtenir toutes les salles depuis la base de données
**/
void ADE::getPlace() {
    QNetworkAccessManager networkAccessManager;
    QNetworkRequest networkRequest(QUrl(QString("https://dwarves.iut-fbleau.fr/~barbey/EDT/script1.php?getsalle=true&idadmin=" + id)));
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
            errorSound.setSource(QUrl::fromLocalFile("error.wav"));
            errorSound.setVolume(0.25f);
            errorSound.play();
            qDebug() << errorSound.status();
            errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
        }

        QJsonValue salle = json.object().value("salle");
        places = salle.toArray();
    }
    else {
        QErrorMessage* errorMsg = new QErrorMessage(this);
        errorSound.setSource(QUrl::fromLocalFile("error.wav"));
        errorSound.setVolume(0.25f);
        errorSound.play();
        errorMsg->showMessage(tr("Connexion impossible à la base de données. Vérifiez votre connexion internet."));
    }
}

/*
* Méthode SLOT permetant d'ajouter un intervenant
**/
void ADE::teacherAdd() {
    AddTeacherWindow* addTeacherWindow = new AddTeacherWindow(id.toInt());
}

/*
* Méthode SLOT permetant de modifier des informations d'un intervenant
**/
void ADE::teacherModify() {
    EditTeacherWindow* editTeacherWindow = new EditTeacherWindow(id.toInt());
}

/*
* Méthode SLOT permetant d'ajouter un lieu
**/
void ADE::placeAdd() {
    AddPlaceWindow* addPlaceWindow = new AddPlaceWindow(id.toInt());
}

/*
* Méthode SLOT permetant de modifier les informations d'un lieu
**/
void ADE::placeModify() {
    EditPlaceWindow* editPlaceWindow = new EditPlaceWindow(id.toInt());
}

/*
* Méthode SLOT permetant d'ajouter un groupe
**/
void ADE::groupAdd() {
    AddGroupWindow* addGroupWindow = new AddGroupWindow(id.toInt());
}

/*
* Méthode SLOT permetant de modifier les informations d'un groupe
**/
void ADE::groupModify() {
    EditGroupWindow* editGroupWindow = new EditGroupWindow(id.toInt());
}

/*
* Méthode SLOT permetant de supprimer un groupe
**/
void ADE::groupRemove() {
    RemoveGroupWindow* removeGroupWindow = new RemoveGroupWindow(id.toInt(), this);
}

/*
* Méthode SLOT permetant de supprimer un lieu
**/
void ADE::placeRemove() {
    RemovePlaceWindow* removePlaceWindow = new RemovePlaceWindow(id.toInt(), this);
}

/*
* Méthode SLOT permetant de supprimer un intervenant
**/
void ADE::teacherRemove() {
    RemoveTeacherWindow* removeTeacherWindow = new RemoveTeacherWindow(id.toInt(), this);
}

/*
* Méthode SLOT permetant d'afficher des informations à propos du programme
**/
void ADE::about() {
    QPixmap* p = new QPixmap("ade++.png");
    QMessageBox* aboutMessage = new QMessageBox(this);
    QPushButton* aboutMessageOKButton = new QPushButton("OK");
    aboutMessage->setDefaultButton(aboutMessageOKButton);
    aboutMessage->setIconPixmap(p->scaled(250, 250, Qt::KeepAspectRatio));
    aboutMessage->setText(tr("ADE++ : Un logiciel crée dans le cadre du projet tutoré de la seconde année du DUT Informatique."));
    aboutMessage->setInformativeText(tr("Crée par Rayan GRIB, Pierre BARBEY, Brice PANIZZI et Paul LE CORRE"));
    aboutMessage->setWindowTitle(tr("A propos"));
    aboutMessage->show();
    easterEggSound.setSource(QUrl::fromLocalFile("2000.wav"));
    easterEggSound.setVolume(0.25f);
    easterEggSound.play();
    qDebug() << easterEggSound.status();
}

/*
* Méthode SLOT permetant d'afficher des informations sur Qt
**/
void ADE::aboutQt() {
    QMessageBox* aboutQt = new QMessageBox(this);
    aboutQt->aboutQt(this);
}

/*
* Méthode SLOT permetant de se déconnecter et de retourner sur le menu de connexion
**/
void ADE::reconnect() {
    loginWindow->setVisible(true);
    delete this;
}

/*
* Méthode SLOT permetant de gérer lorsque l'on veut quitter le logiciel depuis la croix rouge
**/
void ADE::closeEvent(QCloseEvent* event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question(this, "ADE++",
        tr("Etes vous sur(e) de vouloir quitter ?\n"),
        QMessageBox::No | QMessageBox::Yes,
        QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    }
    else {
        event->accept();
        close();
        delete this;
        QCoreApplication::quit();
    }
}