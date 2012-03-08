// CLLKDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CCLLKDlg 对话框
class CCLLKDlg sealed : public CDialog
{
// 构造
public:
	CCLLKDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CCLLKDlg();
// 对话框数据
	enum { IDD = IDD_CLLK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	BOOL CCLLKDlg::PreTranslateMessage(MSG* pMsg);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


protected:
	//地图指针
	int* m_map;
	// 行数
	int m_nRow;
	// 列数
	int m_nCol;
	//方块种类数
	int m_Kind;
	// 3d框架内存设备环境
	CDC m_mem3DBkDC;
	// 动物图案内存设备环境
	CDC m_memAnimaDC;
	// 内存设备环境
	CDC m_memDC;
	// 3d框架内存位图
	CBitmap m_mem3DBkBmp;
	// 动物图案内存位图
	CBitmap m_memAnimaBmp;
	// 内存位图
	CBitmap m_memBmp;
	//连接的折点实际坐标
	CPoint CornerPoint1,CornerPoint2;
	//方块的实际坐标
	CPoint StartPoint,EndPoint;
	//是否选中方块
	bool IsSelected;
	//当前选中方块逻辑坐标X
	int m_nX1;
	//当前选中方块逻辑坐标Y
	int m_nY1;
	//全屏画面X偏移
	int m_iSeekX;
	//全屏画面Y偏移
	int m_iSeekY;
	//是否全屏
	bool m_bIsFullScreen;
	// 直连 单点连 两点连
	int LinkKind;
	//弹出菜单
	CMenu* m_popupMenu;
	// 状态栏
	CStatusBarCtrl m_StatusBar;
	//游戏开始时间
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
	// 3D边框
	bool m_b3DBar;
};
