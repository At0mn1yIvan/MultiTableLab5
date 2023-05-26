#include "TTreeTable.h"

bool TTreeTable::isFull() const
{
    PTreeNode node = new TreeNode();
    bool isValid = (node != nullptr);
    delete node;
    return !isValid;
}
