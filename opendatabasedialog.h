#ifndef OPENDATABASEDIALOG_H
#define OPENDATABASEDIALOG_H

#include <QDialog>

namespace Ui {
class OpenDatabaseDialog;
}

class OpenDatabaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenDatabaseDialog(QWidget *parent = nullptr);
    ~OpenDatabaseDialog();
    void getParameters(QString &ip          ,
                       int     &port        ,
                       QString &databaseName,
                       QString &login       ,
                       QString &password    );

    void setParameters(QString ip = "195.19.32.74",
                       int port = 5432,
                       QString databaseName = "fn1131_2022",
                       QString login = "student",
                       QString password = "bmstu");

private:
    Ui::OpenDatabaseDialog *ui;

signals:
    void sign();
};

#endif // OPENDATABASEDIALOG_H
