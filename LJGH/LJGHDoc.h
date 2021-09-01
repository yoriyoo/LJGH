
// LJGHDoc.h : CLJGHDoc ��Ľӿ�
//


#pragma once

#define MAX 100  //�����������100���ϰ��� 


class CLJGHDoc : public CDocument
{
protected: // �������л�����
	CLJGHDoc();
	DECLARE_DYNCREATE(CLJGHDoc)

// ����
public:
	//�û�������Ϣ
	int circlex, circley, circler;
	int startx, starty;
	int finalx, finaly;
	CRect barrier[MAX];
	int i;
	CRect start, final;
	int x, y;//���ʵĵ�λ
	CPoint pointmouse;
	bool bCaptured;

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CLJGHDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
