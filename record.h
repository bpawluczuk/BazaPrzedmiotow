#ifndef RECORD_H
#define RECORD_H


#include <map>
#include <vector>
#include "column.h"


class Record {
public:

    /**
     * Constructor
     * @param index
     */
    Record(int index = 0);

    /**
     * Add new column to database schema
     * @param column
     */
    void addColumn(Column *column);

    /**
     * @brief addColumns
     * @param column
     */
    void addColumns(vector<Column *> columns);

    /**
     * Get column names from database schema
     * @return
     */
    vector<Column *> getColumns();

    /**
     * Get identyfier of database record
     * @return
     */
    const char *getId();

    /**
     * Get column value by column name
     * @param name
     * @return
     */
    const char *getColumnValue(const char *name);

    /**
     * Update column name by column name
     * @param key
     * @param value
     */
    void updateColumnValue(const char *key, const char *value);

    /**
     * Update column name by column object
     * @param updateColumn
     */
    void updateColumnValue(Column *updateColumn);

    /**
     * Update column name by list of columns object
     * @param updateColumns
     */
    void updateColumnValue(vector<Column *> updateColumns);

    /**
     * Set index of record
     * @param index
     */
    void setIndex(int index);

    /**
     * Get index of record
     * @return
     */
    int getIndex() const;

private:

    vector<Column *> columns;
    int index;
};


#endif // RECORD_H
