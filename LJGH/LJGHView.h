
// LJGHView.h : CLJGHView ��Ľӿ�
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
protected: // �������л�����
	CLJGHView();
	DECLARE_DYNCREATE(CLJGHView)

// ����
public:
	CLJGHDoc* GetDocument()const ;

// ����
public:

	

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CLJGHView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // LJGHView.cpp �еĵ��԰汾
inline CLJGHDoc* CLJGHView::GetDocument() const
   { return reinterpret_cast<CLJGHDoc*>(m_pDocument); }
#endif












//A*�㷨ͷ�ļ�����


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


	void search(Node* startPos, Node* endPos);//��������
	void checkPoint(int x, int y, Node*father, int g);//�жϵ㣬��������Ϣ
	void NextStep(Node* currentPoint);//��һ������ƶ�
	int isContains(vector<Node*>* Nodelist, int x, int y);//�жϵ��Ƿ����б���
	void coutGHF(Node* sNode, Node* eNode, int g);//����g,h,f
	static bool compare(Node *n1, Node* n2);//�Ƚ��������f
	bool unWalk(int x, int y);//�ж��Ƿ�Ϊ�ϰ���

	vector<Node*> openList;
	vector<Node*> closeList;
	Node *startPos, *endPos;

	const int WeightW = 10;//����������	
	const int WeightWH = 14;//б��������

	CRect wall[MAX];//�ϰ���
	int i;//iΪwall�ĸ���
	int go=0;//goΪ�ж��Ƿ��ҵ��յ㣬����ҵ���Ϊ1
	int shuaxin = 0;


};