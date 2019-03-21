#ifndef XMLMODEL_H
#define XMLMODEL_H

#endif // XMLMODEL_H

#include <QAbstractTableModel>
#include "xmlDatabase/dataset.h"

class XmlModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    XmlModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    void setDataset(DataSet *dataSet);
    DataSet *getDataset();
private:
    DataSet *dataSet;
};
