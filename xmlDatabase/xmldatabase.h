#ifndef XMLDATABASE_H
#define XMLDATABASE_H


#include <iostream>
#include <map>
#include <list>
#include "tinyxml2.h"
#include "record.h"
#include "dataset.h"

using namespace std;
using namespace tinyxml2;

/**
 * class XmlDatabase
 * This class represents database,
 * This class defines methods who are needed for manage of database, creates and fill simple ORM objects
 */
class XmlDatabase {
public:

    /**
     * Connect to database file *.xml
     * @param path
     * @return
     */
    int connect(const char *path);

    /**
     * Create database file *.xml
     * @param name
     * @return
     */
    int create(const char *name);

    /**
     * Return all records from database who is currently set
     * @return
     */
    list<Record *> select();

    /**
     * Return all records who meet the condition where
     * @param where
     * @return
     */
    list<Record *> select(Record *where);

    /**
     * Insert record to database
     * @param record
     * @return
     */
    int insert(Record *record);

    /**
     * Remove record from database
     * @param id
     */
    void remove(const char *id);

    /**
     * Update record to database
     * @param record
     */
    void update(Record *record);

    /**
     * Alter database schema and add new column
     * @param name
     * @return
     */
    bool insertColumn(const char *name);

    /**
     * Alter database and remove column
     * @param name
     * @return
     */
    bool removeColumn(const char *name);

    /**
     * Get database schema
     * @return
     */
    vector<const char *> getSchema();

    /**
     * Get column count
     * @return
     */
    int columnCount();

    /**
     * Get specify database path
     * @param name
     * @return
     */
    const char *getDatabasePath();

    /**
     * @brief setDatabasePath
     * @param path
     */
    void setDatabasePath(const char *path);

    /**
     * Get data set
     * @return
     */
    DataSet getDataSet();

    /**
     * @brief getIndexCount
     * @return
     */
    int getIndexCount();

private:

    const char *dbName;
    const char *dbPath;
    XMLDocument xmlDocument;
    DataSet dataSet;
    void saveFile();
    bool columnExist(const char *name);
    Record *findRecordById(const char *id);
    XMLNode *xmlGetRootNode();
    XMLNode *xmlFindRecordById(const char *id);
    vector<string> getDatabaseList(const char *path);
};

#endif // XMLDATABASE_H
