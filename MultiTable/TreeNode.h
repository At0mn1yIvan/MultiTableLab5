#pragma once

#include "TTabRecord.h"s

using PTreeNode = TreeNode*;

class TreeNode: public TTabRecord
{
	protected:
		PTreeNode pLeft, pRight;
	public:	
		TreeNode(TKey key = "", PTDatValue value = nullptr, PTreeNode left = nullptr, PTreeNode right = nullptr): TTabRecord(key, value), pLeft(left), pRight(right){}

		PTreeNode GetPLeft() const
		{
			return pLeft;
		}

		PTreeNode GetPRight() const
		{
			return pRight;
		}

		virtual PTDatValue GetCopy() override 
		{
			TreeNode* node = new TreeNode(_key, _value->GetCopy());
			return node;
		}
};

