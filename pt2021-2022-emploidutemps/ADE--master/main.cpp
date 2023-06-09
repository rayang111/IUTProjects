#include "ADE.h"

#include "LoginWindow.h"
#include <QtWidgets/QApplication>
#include <QGuiApplication>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <winsock.h>
#include <windows.h>
#include <iostream>
#include <QtWebEngineWidgets/QtWebEngineWidgets>
#include <QtWebEngineWidgets/qwebengineview.h>
#include <tchar.h>
#include <QSettings>
#include <QFile>
//#include <QTextCodec>





using namespace std;


int main(int argc, char *argv[])
{
    QCoreApplication::addLibraryPath(".");
    QApplication a(argc, argv);
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    //UTF8 dans Qt 6 est pour l'instant très compliqué à mettre en place
    LoginWindow login;
    login.show();
    return a.exec();
}
