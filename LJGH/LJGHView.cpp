
// LJGHView.cpp : CLJGHView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "LJGH.h"
#endif
//**********************************************************����ͷ�ļ�
#include "LJGHDialog.h"  
#include"LJGHDialog2.h"

#include "LJGHDoc.h"
#include "LJGHView.h"
#include <Windows.h>
#include<fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLJGHView

IMPLEMENT_DYNCREATE(CLJGHView, CView)

BEGIN_MESSAGE_MAP(CLJGHView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
//	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CLJGHView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_32771, &CLJGHView::On32771)
	ON_COMMAND(ID_32772, &CLJGHView::On32772)
	ON_COMMAND(ID_32773, &CLJGHView::On32773)
	ON_WM_RBUTTONDOWN()
//	ON_COMMAND(ID_32776, &CLJGHView::On32776)
ON_COMMAND(ID_32775, &CLJGHView::On32775)
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CLJGHView ����/����

CLJGHView::CLJGHView()
{
	// TODO:  �ڴ˴���ӹ������

}

CLJGHView::~CLJGHView()
{
}

BOOL CLJGHView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CLJGHView ����

Astar astar;
Node *current;
Node *bc;
Node *grey;

void CLJGHView::OnDraw(CDC* pDC)
{
	CLJGHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
	//���̶���
	for (int j = 0; j <= 900; j=j+50){
		CString num;
		num.Format(_T("%d"), j);
		pDC->TextOutW(j, 5, num);
		pDC->TextOutW(5, j, num);

	}

	//���ϰ��Ｐ����յ�
	for (int j=0; j < pDoc->i; j++){
		pDC->Ellipse(pDoc->barrier[j]);		
	}
	
	if (pDoc->startx != 0){
		pDC->TextOut(pDoc->startx - 20, pDoc->starty - 20, _T("�յ�"));
		pDC->Ellipse(pDoc->final);
	}
	
	if (pDoc->finalx != 0){
		pDC->Ellipse(pDoc->start);
		pDC->TextOut(pDoc->finalx - 20, pDoc->finaly - 20, _T("���"));
	}
	

	//��·��

	if (astar.go == 1){
		bc = current;
		CPen penred;
		penred.CreatePen(1, 3, RGB(255, 0, 0));
		pDC->SelectObject(&penred);
		

		while (current->father != NULL){		
			pDC->MoveTo(current->x, current->y);
			pDC->LineTo(current->father->x, current->father->y);	
			Sleep(8);
			current = current->father;
		}
	}
	
}


// CLJGHView ��ӡ


//void CLJGHView::OnFilePrintPreview()
//{
//#ifndef SHARED_HANDLERS
//	AFXPrintPreview(this);
//#endif
//}

BOOL CLJGHView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CLJGHView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CLJGHView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}

void CLJGHView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CLJGHView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CLJGHView ���

#ifdef _DEBUG
void CLJGHView::AssertValid() const
{
	CView::AssertValid();
}

void CLJGHView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLJGHDoc* CLJGHView::GetDocument()const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLJGHDoc)));
	return (CLJGHDoc*)m_pDocument;
}
#endif //_DEBUG


// CLJGHView ��Ϣ�������

//   CLJGHDoc* pDoc = GetDocument();
//ASSERT_VALID(pDoc);
//*********ʹ��pDoc����������



//�˵����

//��ʼ
void CLJGHView::On32771()
{
	CLJGHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO:  �ڴ���������������

	//��doc�ϰ�����Ϣ��ֵ��Astar��
	astar.i = pDoc->i;//iΪ�ϰ������
	for (int j = 0; j < astar.i; j++){
		astar.wall[j] = pDoc->barrier[j];
	}

	Node *startPos = new Node(pDoc->startx, pDoc->starty);
	Node *endPos = new Node(pDoc->finalx, pDoc->finaly);
	astar.search(startPos, endPos);
	if (astar.go==1)  Invalidate();//����������յ㣬ˢ�»���

}

//ˢ��
void CLJGHView::On32772()
{
	CLJGHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO:  �ڴ���������������
	astar.shuaxin = 1;
	astar.go = 0;
	astar.i = 0;
	pDoc->i = 0;
	
	pDoc->startx = pDoc->starty = 0;
	pDoc->finalx = pDoc->finaly = 0;
	for (int j = 0; j < pDoc->i; j++){
		pDoc->barrier[j].top = pDoc->barrier[j].bottom = pDoc->barrier[j].right = 0;
	}
	for (int j = 0; j < pDoc->i; j++){
		astar.wall[j].top = astar.wall[j].bottom =astar.wall[j].right =astar.wall[j].left=0;
	}
	Invalidate();
	CString str;
	str.Format(_T("ˢ�³ɹ���"));
	MessageBox(str);
}

//����
void CLJGHView::On32773()
{
	CLJGHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO:  �ڴ���������������
	
	if (astar.go == 1){
		ofstream ofs;
		ofs.open("D:\\LJGH_Date.txt", ios::app);
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		if (sys.wMinute < 10){
			ofs << sys.wYear << "��" << sys.wMonth << "��" << sys.wDay << "��" << sys.wHour << ":" << "0"<<sys.wMinute << "����" << endl;
		}
		else{
			ofs << sys.wYear << "��" << sys.wMonth << "��" << sys.wDay << "��" << sys.wHour << ":" << sys.wMinute << "����" << endl;
		}
		ofs << "·����:" << endl;
		while (bc->father != NULL){
			ofs << "(" << bc->x << "," << bc->y << ")" << "   ";
			bc = bc->father;
		}
		ofs << endl;
		ofs <<pDoc->i<<"��" <<"�ϰ�����Ϣ:" << endl;
		for (int j = 0; j < astar.i; j++){
			int r = (astar.wall[j].right - astar.wall[j].left) / 2;
			if (r != 0){
				ofs << "(" << astar.wall[j].left + r << "," << astar.wall[j].top + r << "," << r << ")" << "   ";
			}
			
		}
		ofs << endl << endl;
		CString str;
		str.Format(_T("����ɹ���"));
		MessageBox(str);
	}


}



//����Ҽ������˵��������û�����
void CLJGHView::OnRButtonDown(UINT nFlags, CPoint point)
{
	
	CLJGHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CLJGHDialog dig;
	   
	    dig.m_startx = pDoc->startx;
		dig.m_starty = pDoc->starty;
		dig.m_finalx = pDoc->finalx;
		dig.m_finaly = pDoc->finaly;

	if (IDOK == dig.DoModal()){
		//���û����õ���Ϣ��ֵ���ĵ�DOC��
		

		pDoc->startx = dig.m_startx;
		pDoc->starty = dig.m_starty;

		pDoc->finalx = dig.m_finalx;
		pDoc->finaly = dig.m_finaly;

		if (dig.m_circlex != 0 && dig.m_circley != 0 && dig.m_circler != 0){
			pDoc->circlex = dig.m_circlex;
			pDoc->circley = dig.m_circley;
			pDoc->circler = dig.m_circler;
			pDoc->barrier[pDoc->i] = CRect(pDoc->circlex - pDoc->circler, pDoc->circley - pDoc->circler, pDoc->circlex + pDoc->circler, pDoc->circley + pDoc->circler);
			pDoc->i++;//�ϰ�����������
		}
		pDoc->start = CRect(pDoc->startx, pDoc->starty, pDoc->startx + 5, pDoc->starty+5);
		pDoc->final = CRect(pDoc->finalx, pDoc->finaly, pDoc->finalx + 5, pDoc->finaly + 5);
		Invalidate();
	}
	    
	CView::OnRButtonDown(nFlags, point);
}





//A*cpp



Astar::Astar()
{
	this->go = 0;//��ʼ��goΪ0
	this->i = 0;
	this->shuaxin = 0;
}


Astar::~Astar()
{
}

//�����ܳ���
void Astar::search(Node *startPos, Node* endPos){

	//ˢ�¹��ܣ���ʼǰ�������һ�ε�vector
	if (astar.shuaxin == 1){
		openList.clear();
		closeList.clear();
		astar.shuaxin == 0;
	}
	this->startPos = startPos;
	this->endPos = endPos;
	openList.push_back(startPos);
	//��ʼ��������Ա�8����
	while (openList.size() > 0){
		//��ǰ��Ϊopenlist�ĵ�һ����
		current = openList[0];
		//���current�����յ��غ�
		if (current->x == endPos->x&&current->y == endPos->y){
			astar.go = 1;
			break;
		}
		//������غϣ���δ�ҵ�
		NextStep(current);
		closeList.push_back(current);//current������б�β��
		openList.erase(openList.begin());//current�ӿ��б�ͷ����ʧ
		sort(openList.begin(), openList.end(), compare);//���򣬽�openlist����Сf�������ǰ                               
	}
}

//����ܱߵ㣬������/������Ϣ
void Astar::checkPoint(int x, int y, Node*father, int g){


	//��������ϰ������closeList��ĵ㣬����
	if (this->unWalk(x, y))return;
	if (isContains(&closeList, x, y) != -1)return;
	if (x > 900 || y > 500)return;
	//������gֵС�Ĳ�����
	int index;

	//�����openList�ĵ�
	if ((index = isContains(&openList, x, y)) != -1){

		Node *point = openList[index];
		//��������βν�㵽point�õ��gС�����point����Ϊ�βν�㣬���Ҹ���point��g��f
		if (point->g > father->g + g){

			point->father = father;
			point->g = father->g + g;
			point->f = point->g + point->h;

		}

	}
	//�����δ��openList���µ�
	else{
		Node*point = new Node(x, y, father);
		coutGHF(point, endPos, g);
		openList.push_back(point);//��������µ�
	}
}

//��Χ�ĵ㣬��ͨ��checkPoint���������������Ϣ
void Astar::NextStep(Node*current){
	checkPoint(current->x - 1, current->y, current, WeightW);
	checkPoint(current->x + 1, current->y, current, WeightW);
	checkPoint(current->x, current->y + 1, current, WeightW);
	checkPoint(current->x, current->y - 1, current, WeightW);

	checkPoint(current->x - 1, current->y + 1, current, WeightWH);
	checkPoint(current->x - 1, current->y - 1, current, WeightWH);
	checkPoint(current->x + 1, current->y - 1, current, WeightWH);
	checkPoint(current->x + 1, current->y + 1, current, WeightWH);
}


int Astar::isContains(vector<Node*>*Nodelist, int x, int y){
	//����vector���Ƿ��иõ㣻����У��������
	for (int i = 0; i < Nodelist->size(); i++){
		if (Nodelist->at(i)->x == x&&Nodelist->at(i)->y == y){
			return i;
		}
	}
	return -1;
}

//����g,h,f
void Astar::coutGHF(Node* sNode, Node*eNode, int g){

	int h = abs(sNode->x - eNode->x)*WeightW + abs(sNode->y - eNode->y)*WeightW;//absΪ����ֵ
	int currentg = sNode->father->g + g;
	int f = currentg + h;
	sNode->f = f;
	sNode->h = h;
	sNode->g = currentg;

}

//�Ƚ��������f�����ǰ���С����Ϊ��
bool Astar::compare(Node*n1, Node*n2){

	return n1->f < n2->f;

}
//�ж��ϰ��������򷵻���
bool Astar::unWalk(int x, int y){

	
	for (int j = 0; j < astar.i; j++){
		
		int a = (astar.wall[j].right - astar.wall[j].left) / 2;
		int b = (astar.wall[j].bottom - astar.wall[j].top) / 2;
		int circlex = astar.wall[j].right - a;
		int circley = astar.wall[j].top + b;
		int absx = circlex - x;
		int absy = circley - y;
		float num = (absx*absx) / (a*a) + (absy*absy) / (b*b);
		bool result = num < 1.0;
		if (result)return TRUE;
		/*int r = (astar.wall[j].right - astar.wall[j].left) / 2;//rΪ�ϰ���Բ�İ뾶
		int circlex = astar.wall[j].right - r;
		int circley = astar.wall[j].top + r;
		int absx = abs(circlex - x);
		int absy = abs(circley - y);
		int juli = absx*absx + absy*absy;
		if (juli < r*r*1.2) return TRUE;//1.2Ϊ��ȫ����*/
		
	}
	
	return FALSE;

	
}



//��������
void CLJGHView::On32775()
{
	// TODO:  �ڴ���������������
	CLJGHDialog2 dig;
	dig.DoModal();
}


void CLJGHView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CLJGHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	astar.go = 0;
	astar.shuaxin = 1;
	SetCapture();
	pDoc->bCaptured = TRUE;
	pDoc->pointmouse = point;
	pDoc->barrier[pDoc->i] = CRect(point.x, point.y, point.x+1, point.y + 1);
	pDoc->i++;
	Invalidate();
	CView::OnLButtonDown(nFlags, point);
}


void CLJGHView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CLJGHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (pDoc->bCaptured){
		::ReleaseCapture();
		pDoc->bCaptured = FALSE;
	}
	CView::OnLButtonUp(nFlags, point);
}


void CLJGHView::OnMouseMove(UINT nFlags, CPoint point)
{
	CLJGHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (pDoc->bCaptured){
		InvalidateRect(pDoc->barrier[pDoc->i]);
		int offsety = point.y - pDoc->pointmouse.y;
		pDoc->barrier[pDoc->i-1].bottom += offsety;
		int offsetx = point.x - pDoc->pointmouse.x;
		pDoc->barrier[pDoc->i-1].right += offsetx;
		InvalidateRect(pDoc->barrier[pDoc->i-1]);
		pDoc->pointmouse = point;
	}
	CView::OnMouseMove(nFlags, point);
}
