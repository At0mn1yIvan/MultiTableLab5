#pragma once

#include <stack>

#include "TTable.h"
#include "TreeNode.h"

class TTreeTable : public TTable
{
protected:
	PTreeNode pRoot;
	PTreeNode* pTmp; // указатель на вершину поддерева, в которой хранится наш результат
	PTreeNode pCurrent;
	size_t curPos; // 
	std::stack<PTreeNode> st;

	void Print(std::ostream& os, PTreeNode tmp);
	void Draw(PTreeNode tmp, unsigned char level);
	void DeleteTree(TreeNode* tmp);
public:
	TTreeTable() : TTable(), pRoot(nullptr), pTmp(nullptr), pCurrent(nullptr), curPos(0){}
	~TTreeTable()
	{
		DeleteTree(pRoot);
	}
	virtual bool isFull() const override;

	virtual PTDatValue FindRecord(TKey key);
	virtual bool InsertRecord(TKey key, PTDatValue value); // передача value по ссылке
	virtual void DeleteRecord(TKey key);

	virtual int Reset();
	virtual int IsTabEnded() const;
	virtual int GoNext();
	virtual TKey GetKey() const;
	virtual PTDatValue GetValuePTR() const;
};

