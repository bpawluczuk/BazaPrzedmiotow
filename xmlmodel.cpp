#include "xmlmodel.h"

XmlModel::XmlModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

void XmlModel::setDataset(DataSet *dataSet){
    XmlModel::dataSet = dataSet;
}

DataSet *XmlModel::getDataset(){
    return XmlModel::dataSet;
}

int XmlModel::rowCount(const QModelIndex & /*parent*/) const
{
    return XmlModel::dataSet->getRowCount();
}

int XmlModel::columnCount(const QModelIndex & /*parent*/) const
{
    return XmlModel::dataSet->getColumnCount();
}

QVariant XmlModel::data(const QModelIndex &index, int role) const
{        
    string value;
    if (role == Qt::DisplayRole){
        value = XmlModel::dataSet->getCellValue(index.row(), index.column());
        return QString::fromStdString(value);
    }

    return QVariant();
}

QVariant XmlModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            string name = XmlModel::dataSet->getColumnName(section);
            return QString::fromStdString(name);
        }
        if (orientation == Qt::Vertical) {
            return QString("");
        }
    }
    return QVariant();
}
