#ifndef IRECORD_H
#define IRECORD_H

#include <vector>

/**
 * Record template interface
 */
template<typename TColumn>
class IRecord {

    /**
     * Add new column to record
     * @param column
     */
    void addColumn(TColumn *column);

    /**
    * Get all columns from record
    * @return
    */
    std::vector<TColumn *> getColumns();
};

#endif // IRECORD_H
