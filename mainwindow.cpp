#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include <QStringListModel>
#include <QSettings>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dialog = new OpenDatabaseDialog(this);
    db = QSqlDatabase::addDatabase("QPSQL", "mydb");
    ui->tablesListView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered(){
    QString ip          ;
    int     port        ;
    QString databaseName;
    QString login       ;
    QString password    ;
    dialog->setParameters();
    if (dialog->exec() == QDialog::Accepted){
        dialog->getParameters(ip, port, databaseName, login, password);
        db.setHostName    (ip          );
        db.setPort        (port        );
        db.setDatabaseName(databaseName);
        db.setUserName    (login       );
        db.setPassword    (password    );
    }
    if(!db.open())
        ui->errorLabel->setText(db.lastError().text());
    else
        ui->errorLabel->setText("OK!");
    dialog->close();
    QStringListModel *list = new QStringListModel(ui->tablesListView);
    list->setStringList(db.tables());
    ui->tablesListView->setModel(list);
}

void MainWindow::keyPressedEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Escape) close();
    else QMainWindow::keyPressEvent(event);
}

void MainWindow::on_pushButton_clicked()
{
    QString command = ui->commandTextEdit->toPlainText();
    QSqlQuery query(db);
    if(!query.exec(command)) ui->errorLabel->setText(query.lastError().text());
    else{
        ui->errorLabel->setText("OK!");
        ui->historyPlainTextEdit->insertPlainText(command + "\n");
        QSqlQueryModel *model = new QSqlQueryModel(ui->contentTableView);
        model->setQuery(query);
        ui->contentTableView->setModel(model);
        QStringListModel *listik = new QStringListModel(ui->tablesListView);
        listik->setStringList(db.tables());
        ui->tablesListView->setModel(listik);
    }
}

void MainWindow::on_tablesListView_doubleClicked(const QModelIndex &index)
{
    QSqlQuery query(db);
    if(!query.exec("select * from " + index.data().toString())){
        ui->errorLabel->setText(query.lastError().text());
    }
    else {
        ui->errorLabel->setText("OK!");
        QSqlQueryModel * model = new QSqlQueryModel(ui->contentTableView);
        model->setQuery(query);
        ui->contentTableView->setModel(model);
    }
}

