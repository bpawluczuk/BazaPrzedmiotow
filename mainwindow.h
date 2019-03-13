#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <vector>
#include "tinyxml2.h"
#include "xmldatabase.h"
#include "dataset.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_connectButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButtonClear_clicked();

    void on_pushButtonAddColumn_clicked();

    void on_pushButtonAdd_clicked();

    void on_pushButtonDelete_clicked();

    void on_pushButtonUpdate_clicked();

    void on_pushButtonSetCurrentFolder_clicked();

    void on_pushButtonDeleteColumn_clicked();

    void on_pushButtonCreateDb_clicked();

    void on_pushButtonFind_clicked();

private:
    const char *QStringToConstChar(QString qString);
    QString ConstCharToQString(const char * string);
    void refresh();
    void connectDb(QString dbName);
    Record* createRecord();
    Record* where = nullptr;

    Ui::MainWindow *ui;
    XmlDatabase *db;
    QString dbDir;
    QString dbPath;
    QString dbCurrentName;
    bool connect = false;
    int currentRow;
    int currentColumn;
    DataSet *dataSet;
    vector<pair<string, QLineEdit *>> editRecord;
};

#endif // MAINWINDOW_H

