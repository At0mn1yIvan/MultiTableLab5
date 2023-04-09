#include "TArrayTable.h"

TKey TArrayTable::GetKey(Position pos) const
{
    int localPos = -1;
    if (!this->isEmpty())
        switch (pos) {
        case Position::FIRST: 
            localPos = 0;
            break;
        case Position::LAST:
            localPos = DataCount - 1;
            break;
        default:
            localPos = curPos;
            break;
        }
    return (localPos == -1 ? std::string("") : pData[localPos]->_key);
}

PTDatValue TArrayTable::GetValuePTR(Position pos) const
{
    int localPos = -1;
    if (!this->isEmpty())
        switch (pos) {
        case Position::FIRST:
            localPos = 0;
            break;
        case Position::LAST:
            localPos = DataCount - 1;
            break;
        default:
            localPos = curPos;
            break;
        }
    return (localPos == -1 ? nullptr : pData[localPos]->_value);
}
