#include "FileExplorer.h"
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>

/*
* Classe permetant de gérer l'exportation de la grille (Non terminé)
**/

/*
* Constructeur de la classe permetant de gérer l'exportation de la grille
**/
FileExplorer::FileExplorer(QWidget* parent)
    : QWidget(parent)
{
    QString filter = "Text File (*.txt) ;; All File (*.*)";
    QString file_open = QFileDialog::getOpenFileName(this, "Ouvriv un fichier", QDir::homePath(), filter);
    QFile file(file_open);
    //QPushButton button

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Titre", "Impossible d'ouvrir le fichier");
    }
    QTextStream in(&file);
    QString text = in.readAll();
    //ui->plainTextEdit->setPlainText(text);
    file.close();
}



FileExplorer::~FileExplorer()
{

}
