#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;
using namespace tinyxml2;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh(){

    ui->comboBoxDbList->clear();
    QDirIterator it(MainWindow::dbDir, QStringList() << "*.xml");
    while (it.hasNext()) {
        QFile f(it.next());
        QString ddd = it.fileName();
        ui->comboBoxDbList->addItem(it.fileName());
    }

    if(MainWindow::dbDir.length()){
        ui->comboBoxDbList->setEnabled(true);
        ui->connectButton->setEnabled(true);
        ui->lineEditCreateDb->setEnabled(true);
        ui->pushButtonCreateDb->setEnabled(true);
    }

    ui->comboBoxDbList->setCurrentText(MainWindow::dbCurrentName);

    if(!MainWindow::connect){
        return;
    }else{
        ui->pushButtonAdd->setEnabled(true);
        ui->pushButtonFind->setEnabled(true);
        ui->pushButtonClear->setEnabled(true);
        ui->pushButtonDelete->setEnabled(true);
        ui->pushButtonUpdate->setEnabled(true);
        ui->pushButtonAddColumn->setEnabled(true);
        ui->pushButtonDeleteColumn->setEnabled(true);
        ui->lineEditInsertColumn->setEnabled(true);
        ui->comboBoxColumnList->setEnabled(true);
    }

    ui->comboBoxColumnList->clear();
    for( auto item: MainWindow::db->getSchema()){
        ui->comboBoxColumnList->addItem(MainWindow::ConstCharToQString(item));
    }

    XmlModel* xmlModel = new XmlModel();

    MainWindow::dataSet = new DataSet();
    if(MainWindow::where){
        dataSet->setRecordList(MainWindow::db->select(MainWindow::where));
    }else{
        dataSet->setRecordList(MainWindow::db->select());
    }

    xmlModel->setDataset(MainWindow::dataSet);

    ui->tableView->setModel(xmlModel);
    ui->tableView->setColumnHidden(0, true);

    for(auto item: MainWindow::editRecord){
        delete item.second;
    }

    MainWindow::editRecord.clear();

    for( int index=0; index < MainWindow::db->columnCount(); index++){
        QLineEdit *field = new QLineEdit;
        string name = MainWindow::db->getSchema()[index];
        field->setPlaceholderText(QString::fromStdString(name));
        if(MainWindow::where){
            field->setText(MainWindow::ConstCharToQString(where->getColumnValue(name.c_str())));
        }
        MainWindow::editRecord.push_back(std::make_pair(name, field));
    }

    for(auto item: MainWindow::editRecord){
        if(item.first != "ID"){
            ui->horizontalLayout->addWidget(item.second);
        }
    }

    MainWindow::where = nullptr;
}

Record* MainWindow::createRecord(){

    Record *record = new Record();

    string *name;

    int index=0;
    for(auto column: MainWindow::editRecord){
        name = new string(column.first);
        record->addColumn(new Column(name->c_str(), MainWindow::QStringToConstChar(column.second->text()), index++));
    }
    return record;
}

void MainWindow::on_connectButton_clicked()
{
    MainWindow::connectDb(ui->comboBoxDbList->currentText());
}

void MainWindow::connectDb(QString dbName){

    MainWindow::dbCurrentName=dbName;
    MainWindow::db = new XmlDatabase();
    MainWindow::dbPath = MainWindow::dbDir + dbName;
    const char *dbPath = MainWindow::QStringToConstChar(MainWindow::dbPath);
    if (MainWindow::db->connect(dbPath)) {
        ui->statusBar->showMessage("Połączono z bazą danych: " + MainWindow::dbPath);
        MainWindow::connect = true;
    }else{
        ui->statusBar->showMessage("Nie można połaczyć się z bazą danych ...");
        MainWindow::connect = false;
    }

    MainWindow::refresh();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    if(!MainWindow::connect){
        return;
    }

    MainWindow::currentRow = index.row();
    MainWindow::currentColumn = index.column();

    ui->tableView->selectRow(MainWindow::currentRow);

    int inc = 0;
    for(auto item: MainWindow::editRecord){
        QString val = QString::fromStdString(MainWindow::dataSet->getCellValue(MainWindow::currentRow, inc++));
        item.second->setText(val);
    }
}

void MainWindow::on_pushButtonClear_clicked()
{
    if(!MainWindow::connect){
        return;
    }

    for(auto item: MainWindow::editRecord){
        item.second->setText("");
    }

    MainWindow::where = nullptr;
    MainWindow::refresh();
}

void MainWindow::on_pushButtonAddColumn_clicked()
{
    if(!MainWindow::connect){
        return;
    }

    if(ui->lineEditInsertColumn->text().toStdString()!=""){
        const char *name = MainWindow::QStringToConstChar(ui->lineEditInsertColumn->text());
        MainWindow::db->insertColumn(name);
        MainWindow::where = nullptr;
        ui->lineEditInsertColumn->setText("");
        MainWindow::refresh();
    }
}

void MainWindow::on_pushButtonAdd_clicked()
{
    if(!MainWindow::connect){
        return;
    }

    MainWindow::db->insert(MainWindow::createRecord());
    MainWindow::refresh();
}

void MainWindow::on_pushButtonUpdate_clicked()
{
    MainWindow::db->update(MainWindow::createRecord());
    MainWindow::refresh();
}

void MainWindow::on_pushButtonDelete_clicked()
{
    const char* id = MainWindow::dataSet->getRecordId(MainWindow::currentRow).c_str();

    MainWindow::db->remove(id);
    MainWindow::refresh();
}

const char *MainWindow::QStringToConstChar(QString qString){
    string *str = new string(qString.toStdString());
    return str->c_str();
}

QString MainWindow::ConstCharToQString(const char * str){
    QString qString = QString::fromStdString(string(str));
    return qString;
}

void MainWindow::on_pushButtonSetCurrentFolder_clicked()
{
    MainWindow::dbDir = QFileDialog::getExistingDirectory(this, "Plik bazy danych", "/" ) + "/";
    MainWindow::refresh();
}

void MainWindow::on_pushButtonDeleteColumn_clicked()
{
    MainWindow::db->removeColumn(MainWindow::QStringToConstChar(ui->comboBoxColumnList->currentText()));
    MainWindow::where = nullptr;
    MainWindow::refresh();
}

void MainWindow::on_pushButtonCreateDb_clicked()
{
    XmlDatabase *newDb = new XmlDatabase();

    QString dbName = ui->lineEditCreateDb->text();

    if(!dbName.contains(".xml")){
        dbName.append(".xml");
    }

    newDb->create(MainWindow::QStringToConstChar(MainWindow::dbDir+dbName));

    MainWindow::connectDb(dbName);

    MainWindow::db->insertColumn("ID");
    MainWindow::db->insertColumn("Type");
    MainWindow::db->insertColumn("Name");
    MainWindow::db->insertColumn("Desc");
    MainWindow::db->insertColumn("Status");

    ui->lineEditCreateDb->setText("");
    MainWindow::refresh();
}

void MainWindow::on_pushButtonFind_clicked()
{
    MainWindow::where = MainWindow::createRecord();
    MainWindow::refresh();
}
