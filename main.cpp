#include "mainwindow.h"
#include <QApplication>
#include <QTableView>
#include <QLineEdit>
#include <QFileDialog>
#include "xmlmodel.h"
#include "tinyxml2.h"
#include "xmldatabase.h"

using namespace std;
using namespace tinyxml2;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //    QTableView tableView;
    //    MyModel myModel;
    //    tableView.setModel(&myModel);
    //    tableView.show();

//    XmlDatabase db;
//    const char *dbName = "baza.xml";
//    if (!db.connect(dbName)) {
//        db.create(dbName);
//        return 0;
//    }

//    db.insertColumn("Type");
//    db.insertColumn("Name");
//    db.insertColumn("Desc");

//        Record *record = new Record();
//        record->addColumn(new Column("Type", "GITARA"));
//        record->addColumn(new Column("Name", "Kult"));
//        record->addColumn(new Column("Desc", "bla bla"));
//        db.insert(record);

//    list<Record*> r = db.select();

//    return 0;

    MainWindow w;

    w.show();

    return a.exec();
}
