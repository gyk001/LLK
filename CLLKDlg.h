// CLLKDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CCLLKDlg �Ի���
class CCLLKDlg sealed : public CDialog
{
// ����
public:
	CCLLKDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CCLLKDlg();
// �Ի�������
	enum { IDD = IDD_CLLK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	BOOL CCLLKDlg::PreTranslateMessage(MSG* pMsg);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


protected:
	//��ͼָ��
	int* m_map;
	// ����
	int m_nRow;
	// ����
	int m_nCol;
	//����������
	int m_Kind;
	// 3d����ڴ��豸����
	CDC m_mem3DBkDC;
	// ����ͼ���ڴ��豸����
	CDC m_memAnimaDC;
	// �ڴ��豸����
	CDC m_memDC;
	// 3d����ڴ�λͼ
	CBitmap m_mem3DBkBmp;
	// ����ͼ���ڴ�λͼ
	CBitmap m_memAnimaBmp;
	// �ڴ�λͼ
	CBitmap m_memBmp;
	//���ӵ��۵�ʵ������
	CPoint CornerPoint1,CornerPoint2;
	//�����ʵ������
	CPoint StartPoint,EndPoint;
	//�Ƿ�ѡ�з���
	bool IsSelected;
	//��ǰѡ�з����߼�����X
	int m_nX1;
	//��ǰѡ�з����߼�����Y
	int m_nY1;
	//ȫ������Xƫ��
	int m_iSeekX;
	//ȫ������Yƫ��
	int m_iSeekY;
	//�Ƿ�ȫ��
	bool m_bIsFullScreen;
	// ֱ�� ������ ������
	int LinkKind;
	//�����˵�
	CMenu* m_popupMenu;
	// ״̬��
	CStatusBarCtrl m_StatusBar;
	//��Ϸ��ʼʱ��
	CTime tGameTime;
	CString strTiShi1;
	CString strTiShi2;
	CString strTiShi3;

protected:

	void DrawGame(CDC* pDC);
	void SizeWindow(void);
	bool IsLink(int x1, int y1, int x2, int y2);
	bool IsWin(void);
	bool OneCornerLink(int x1, int y1, int x2, int y2);
	bool TwoCornerLink(int x1, int y1, int x2, int y2);
	bool X1_Link_X2(int x, int y1, int y2);
	bool Y1_Link_Y2(int x1, int x2, int y);
	void SelectShell(int x,int y);
	void SelectShell(int x, int y, CDC* pDC);
	void DrawLink(int x1, int y1, int x2, int y2);
	void OnConfig(void);
	void StartNewGame(void);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnMyMiniSize();
public:
	// 3D�߿�
	bool m_b3DBar;
};
