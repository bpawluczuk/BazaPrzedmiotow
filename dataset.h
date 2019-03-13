#ifndef DATASET_H
#define DATASET_H

#ifndef RECORD_H

#include "record.h"

#endif

#include <list>

/**
 * class DataSet
 */
class DataSet {
public:

    /**
     * Set record list
     * @param records
     */
    void setRecordList(list<Record *> records);

    /**
     * Get row count
     * @return
     */
    int getRowCount();

    /**
     * Get column count
     * @return
     */
    int getColumnCount();

    /**
     * Get column name by index of
     * @param indexColumn
     * @return
     */
    string getColumnName(int indexColumn);

    /**
     * Get cell value by index row and index column
     * @param indexRow
     * @param indexColumn
     * @return
     */
    string getCellValue(int indexRow, int indexColumn);

    string getRecordId(int indexRow);

    vector<string> columnNames;
    vector<vector<string>> rows;

private:

    list<Record *> records;
//    vector<string> columnNames;
//    vector<vector<string>> rows;
    int columnCount;
    int rowsCount;
};

#endif // DATASET_H
