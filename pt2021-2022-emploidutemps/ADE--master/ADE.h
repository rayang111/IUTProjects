#pragma once
#ifndef ADE_H
#define ADE_H

#include <QtWidgets>
#include <QtNetwork>
#include <QVBoxLayout>
#include <vector>
#include "LoginWindow.h"


class ADE : public QMainWindow
{
    Q_OBJECT

public:
    ADE(QString login, QString idAdmin, QString id, QString groupid, LoginWindow* loginWindowP, QWidget *parent = Q_NULLPTR);
    void getGroup();
    void changeHeaderDates();
    void spanGrid();
    void getPlace();
    void getTeacher();


public slots:
    void openfile();
    void viewCalendar();
    void whenDateSelected();
    void loadCalendar(int loadCode, int groupid, QDate idDay);
    void loadCalendar(int loadCode, int groupid, int id, QDate idDay);
    void changeWeekAdd();
    void changeWeekLess();
    void addCase();
    void editCase();
    void removeCase();
    void teacherAdd();
    void teacherModify();
    void placeAdd();
    void placeModify();
    void groupAdd();
    void groupModify();
    void groupRemove();
    void placeRemove();
    void teacherRemove();
    void about();
    void aboutQt();
    void reconnect();
    void closeEvent(QCloseEvent* event);
    void loadCalendarLaunch();

private:
    QWidget *centralElements;
    QVBoxLayout *centralLayout;
    QTableWidget* table;
    QHeaderView* verticalHeader;
    QHeaderView* horizontalHeader;
    QCalendarWidget* mainCalendar;
    std::vector<QJsonObject> tab;
    std::vector<int> groupidsADE;
    QWidget* groupChoice;
    QHBoxLayout* groupChoiceLayout;
    QComboBox* groupList;
    QJsonArray tableaiGroupe;
    QDate currentDate;
    QPushButton* selectedTime;
    QLocale locale = QLocale(QLocale::French, QLocale::France);
    QTableWidgetItem* header;
    QTableWidgetItem* header2;
    QTableWidgetItem* header3;
    QTableWidgetItem* header4;
    QTableWidgetItem* header5;
    QTableWidgetItem* header6;
    QTableWidgetItem* header7;
    LoginWindow* loginWindow;
    QSoundEffect errorSound;
    QSoundEffect easterEggSound;
    QString idAdmin;
    QString groupid;
    QJsonArray places;
    QJsonArray teachers;
    QLabel* welcomeText;
    QString login;
    bool isCalendarOpen;
    QWidget* southButtons;
    QWidget* northButtons;
    QString id;

};
#endif //ADE_H