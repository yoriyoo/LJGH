
// LJGHView.cpp : CLJGHView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "LJGH.h"
#endif
//**********************************************************增加头文件
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
	// 标准打印命令
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

// CLJGHView 构造/析构

CLJGHView::CLJGHView()
{
	// TODO:  在此处添加构造代码

}

CLJGHView::~CLJGHView()
{
}

BOOL CLJGHView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CLJGHView 绘制

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

	// TODO:  在此处为本机数据添加绘制代码
	//画刻度线
	for (int j = 0; j <= 900; j=j+50){
		CString num;
		num.Format(_T("%d"), j);
		pDC->TextOutW(j, 5, num);
		pDC->TextOutW(5, j, num);

	}

	//画障碍物及起点终点
	for (int j=0; j < pDoc->i; j++){
		pDC->Ellipse(pDoc->barrier[j]);		
	}
	
	if (pDoc->startx != 0){
		pDC->TextOut(pDoc->startx - 20, pDoc->starty - 20, _T("终点"));
		pDC->Ellipse(pDoc->final);
	}
	
	if (pDoc->finalx != 0){
		pDC->Ellipse(pDoc->start);
		pDC->TextOut(pDoc->finalx - 20, pDoc->finaly - 20, _T("起点"));
	}
	

	//画路径

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


// CLJGHView 打印


//void CLJGHView::OnFilePrintPreview()
//{
//#ifndef SHARED_HANDLERS
//	AFXPrintPreview(this);
//#endif
//}

BOOL CLJGHView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CLJGHView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CLJGHView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
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


// CLJGHView 诊断

#ifdef _DEBUG
void CLJGHView::AssertValid() const
{
	CView::AssertValid();
}

void CLJGHView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLJGHDoc* CLJGHView::GetDocument()const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLJGHDoc)));
	return (CLJGHDoc*)m_pDocument;
}
#endif //_DEBUG


// CLJGHView 消息处理程序

//   CLJGHDoc* pDoc = GetDocument();
//ASSERT_VALID(pDoc);
//*********使用pDoc来处理数据



//菜单设计

//开始
void CLJGHView::On32771()
{
	CLJGHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO:  在此添加命令处理程序代码

	//给doc障碍物信息赋值到Astar里
	astar.i = pDoc->i;//i为障碍物个数
	for (int j = 0; j < astar.i; j++){
		astar.wall[j] = pDoc->barrier[j];
	}

	Node *startPos = new Node(pDoc->startx, pDoc->starty);
	Node *endPos = new Node(pDoc->finalx, pDoc->finaly);
	astar.search(startPos, endPos);
	if (astar.go==1)  Invalidate();//如果发现了终点，刷新画画

}

//刷新
void CLJGHView::On32772()
{
	CLJGHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO:  在此添加命令处理程序代码
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
	str.Format(_T("刷新成功！"));
	MessageBox(str);
}

//保存
void CLJGHView::On32773()
{
	CLJGHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO:  在此添加命令处理程序代码
	
	if (astar.go == 1){
		ofstream ofs;
		ofs.open("D:\\LJGH_Date.txt", ios::app);
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		if (sys.wMinute < 10){
			ofs << sys.wYear << "年" << sys.wMonth << "月" << sys.wDay << "日" << sys.wHour << ":" << "0"<<sys.wMinute << "创建" << endl;
		}
		else{
			ofs << sys.wYear << "年" << sys.wMonth << "月" << sys.wDay << "日" << sys.wHour << ":" << sys.wMinute << "创建" << endl;
		}
		ofs << "路径点:" << endl;
		while (bc->father != NULL){
			ofs << "(" << bc->x << "," << bc->y << ")" << "   ";
			bc = bc->father;
		}
		ofs << endl;
		ofs <<pDoc->i<<"个" <<"障碍物信息:" << endl;
		for (int j = 0; j < astar.i; j++){
			int r = (astar.wall[j].right - astar.wall[j].left) / 2;
			if (r != 0){
				ofs << "(" << astar.wall[j].left + r << "," << astar.wall[j].top + r << "," << r << ")" << "   ";
			}
			
		}
		ofs << endl << endl;
		CString str;
		str.Format(_T("保存成功！"));
		MessageBox(str);
	}


}



//鼠标右键弹出菜单，进行用户设置
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
		//将用户设置的信息赋值到文档DOC中
		

		pDoc->startx = dig.m_startx;
		pDoc->starty = dig.m_starty;

		pDoc->finalx = dig.m_finalx;
		pDoc->finaly = dig.m_finaly;

		if (dig.m_circlex != 0 && dig.m_circley != 0 && dig.m_circler != 0){
			pDoc->circlex = dig.m_circlex;
			pDoc->circley = dig.m_circley;
			pDoc->circler = dig.m_circler;
			pDoc->barrier[pDoc->i] = CRect(pDoc->circlex - pDoc->circler, pDoc->circley - pDoc->circler, pDoc->circlex + pDoc->circler, pDoc->circley + pDoc->circler);
			pDoc->i++;//障碍物数量增加
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
	this->go = 0;//初始化go为0
	this->i = 0;
	this->shuaxin = 0;
}


Astar::~Astar()
{
}

//搜索总程序
void Astar::search(Node *startPos, Node* endPos){

	//刷新功能，开始前先清除上一次的vector
	if (astar.shuaxin == 1){
		openList.clear();
		closeList.clear();
		astar.shuaxin == 0;
	}
	this->startPos = startPos;
	this->endPos = endPos;
	openList.push_back(startPos);
	//开始查找起点旁边8个点
	while (openList.size() > 0){
		//当前点为openlist的第一个点
		current = openList[0];
		//如果current点与终点重合
		if (current->x == endPos->x&&current->y == endPos->y){
			astar.go = 1;
			break;
		}
		//如果不重合，及未找到
		NextStep(current);
		closeList.push_back(current);//current放入关列表尾部
		openList.erase(openList.begin());//current从开列表头部消失
		sort(openList.begin(), openList.end(), compare);//排序，将openlist的最小f点放置最前                               
	}
}

//检查周边点，并创建/更新信息
void Astar::checkPoint(int x, int y, Node*father, int g){


	//如果遇到障碍物或则closeList里的点，跳过
	if (this->unWalk(x, y))return;
	if (isContains(&closeList, x, y) != -1)return;
	if (x > 900 || y > 500)return;
	//遍历找g值小的并更新
	int index;

	//如果是openList的点
	if ((index = isContains(&openList, x, y)) != -1){

		Node *point = openList[index];
		//如果经由形参结点到point该点的g小，则改point父亲为形参结点，并且更新point的g和f
		if (point->g > father->g + g){

			point->father = father;
			point->g = father->g + g;
			point->f = point->g + point->h;

		}

	}
	//如果是未在openList的新点
	else{
		Node*point = new Node(x, y, father);
		coutGHF(point, endPos, g);
		openList.push_back(point);//往后加入新点
	}
}

//周围的点，并通过checkPoint方法来创建点的信息
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
	//查找vector中是否有该点；如果有，返回序号
	for (int i = 0; i < Nodelist->size(); i++){
		if (Nodelist->at(i)->x == x&&Nodelist->at(i)->y == y){
			return i;
		}
	}
	return -1;
}

//计算g,h,f
void Astar::coutGHF(Node* sNode, Node*eNode, int g){

	int h = abs(sNode->x - eNode->x)*WeightW + abs(sNode->y - eNode->y)*WeightW;//abs为绝对值
	int currentg = sNode->father->g + g;
	int f = currentg + h;
	sNode->f = f;
	sNode->h = h;
	sNode->g = currentg;

}

//比较两个点的f，如果前点更小，则为真
bool Astar::compare(Node*n1, Node*n2){

	return n1->f < n2->f;

}
//判断障碍物，如果是则返回真
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
		/*int r = (astar.wall[j].right - astar.wall[j].left) / 2;//r为障碍物圆的半径
		int circlex = astar.wall[j].right - r;
		int circley = astar.wall[j].top + r;
		int absx = abs(circlex - x);
		int absy = abs(circley - y);
		int juli = absx*absx + absy*absy;
		if (juli < r*r*1.2) return TRUE;//1.2为安全倍数*/
		
	}
	
	return FALSE;

	
}



//帮助窗口
void CLJGHView::On32775()
{
	// TODO:  在此添加命令处理程序代码
	CLJGHDialog2 dig;
	dig.DoModal();
}


void CLJGHView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CLJGHDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO:  在此添加消息处理程序代码和/或调用默认值
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
	// TODO:  在此添加消息处理程序代码和/或调用默认值
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
	// TODO:  在此添加消息处理程序代码和/或调用默认值
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
