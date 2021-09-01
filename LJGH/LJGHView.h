
// LJGHView.h : CLJGHView 类的接口
//

#pragma once


#include<iostream>
#include<queue>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;

class CLJGHView : public CView
{
protected: // 仅从序列化创建
	CLJGHView();
	DECLARE_DYNCREATE(CLJGHView)

// 特性
public:
	CLJGHDoc* GetDocument()const ;

// 操作
public:

	

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CLJGHView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
//	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void On32771();
	afx_msg void On32772();
	afx_msg void On32773();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
//	afx_msg void On32776();
	afx_msg void On32775();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // LJGHView.cpp 中的调试版本
inline CLJGHDoc* CLJGHView::GetDocument() const
   { return reinterpret_cast<CLJGHDoc*>(m_pDocument); }
#endif












//A*算法头文件补充


typedef struct Node{

	int x, y;
	int g, h, f;
	Node *father;
	Node(int x, int y){
		
		this->x = x;
		this->y = y;
		this->g = this->h = this->f = 0;
		this->father = NULL;
	}
	Node(int x, int y, Node*father){
		
		this->x = x;
		this->y = y;
		this->g = this->h = this->f = 0;
		this->father = father;
	}
}Node;


class Astar
{
public:
	Astar();
	~Astar();


	void search(Node* startPos, Node* endPos);//搜索功能
	void checkPoint(int x, int y, Node*father, int g);//判断点，并更新信息
	void NextStep(Node* currentPoint);//下一步点的移动
	int isContains(vector<Node*>* Nodelist, int x, int y);//判断点是否在列表中
	void coutGHF(Node* sNode, Node* eNode, int g);//计算g,h,f
	static bool compare(Node *n1, Node* n2);//比较两个点的f
	bool unWalk(int x, int y);//判断是否为障碍物

	vector<Node*> openList;
	vector<Node*> closeList;
	Node *startPos, *endPos;

	const int WeightW = 10;//正方形消耗	
	const int WeightWH = 14;//斜方向消耗

	CRect wall[MAX];//障碍物
	int i;//i为wall的个数
	int go=0;//go为判定是否找到终点，如果找到则为1
	int shuaxin = 0;


};