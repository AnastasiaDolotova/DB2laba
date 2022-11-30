#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "opendatabasedialog.h"
#include <QSqlDatabase>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressedEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    OpenDatabaseDialog *dialog;

signals:
    void run();

private slots:
    void on_pushButton_clicked();
    void on_action_triggered();
    void on_tablesListView_doubleClicked(const QModelIndex &index);
};
#endif // MAINWINDOW_H
