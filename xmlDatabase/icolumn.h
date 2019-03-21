#ifndef ICOLUMN_H
#define ICOLUMN_H

/**
 * Column template interface
 */
template<typename TKey, typename TValue>
class IColumn{
    void setKey(TKey key);
    void setValue(TValue value);
    TKey getKey() const;
    TValue getValue() const;
};

#endif // ICOLUMN_H
