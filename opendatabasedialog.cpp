#include "opendatabasedialog.h"
#include "ui_opendatabasedialog.h"

OpenDatabaseDialog::OpenDatabaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenDatabaseDialog)
{
    ui->setupUi(this);
}

OpenDatabaseDialog::~OpenDatabaseDialog()
{
    delete ui;
}

void OpenDatabaseDialog::getParameters(QString &ip, int &port, QString &databaseName, QString &login, QString &password)
{
    ip           = ui->ipLineEdit      ->text()        ;
    port         = ui->portLineEdit    ->text().toInt();
    databaseName = ui->dbNameLineEdit  ->text()        ;
    login        = ui->userLineEdit    ->text()        ;
    password     = ui->passwordLineEdit->text()        ;
    emit sign();
}

void OpenDatabaseDialog::setParameters(QString ip          ,
                                       int     port        ,
                                       QString databaseName,
                                       QString login       ,
                                       QString password    )
{
    ui->ipLineEdit      ->setText(ip          );
    ui->portLineEdit    ->setText(QString::number(port)        );
    ui->dbNameLineEdit  ->setText(databaseName);
    ui->userLineEdit    ->setText(login       );
    ui->passwordLineEdit->setText(password    );
}
