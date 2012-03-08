// CLLKDlg.cpp : 实现文件
//




#include "stdafx.h"
#include "CLLK.h"
#include "CLLKDlg.h"
#include "Option.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCLLKDlg 对话框




CCLLKDlg::CCLLKDlg(CWnd* pParent /*=NULL*/)
: CDialog(CCLLKDlg::IDD, pParent)
, m_map(NULL)
, m_nRow(ROWCOUNT)
, m_nCol(COLCOUNT)
, m_nX1(BLANK_STATE)
, m_nY1(BLANK_STATE)
, IsSelected(false)
, m_Kind(8)
, LinkKind(0)
, m_bIsFullScreen(false)
, m_iSeekX(0)
, m_iSeekY(0)
, m_popupMenu(NULL)
, strTiShi1(_T(""))
, strTiShi2(_T(""))
, strTiShi3(_T(""))
, m_b3DBar(true)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_map=new int[m_nCol*m_nRow];
	m_popupMenu=new CMenu();

}

CCLLKDlg::~CCLLKDlg()
{
	delete[] m_map;
	delete m_popupMenu;
}

void CCLLKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCLLKDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SYSCOMMAND()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(IDI_MENU_OPTIOM, &CCLLKDlg::OnConfig)
	ON_COMMAND(IDI_MENU_NEW, &CCLLKDlg::StartNewGame)
	ON_COMMAND(IDI_MENU_EXIT, &CCLLKDlg::OnClose)
	ON_COMMAND(IDI_MENU_MINISIZE, &CCLLKDlg::OnMyMiniSize)
END_MESSAGE_MAP()


// CCLLKDlg 消息处理程序

BOOL CCLLKDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO: 在此添加额外的初始化代码	
	UINT uWidth=DEFAULT_FRAME_X+(m_nCol-2)*FRONTWIDTH+10;
	UINT uHeight=DEFAULT_FRAME_Y+(m_nRow-2)*FRONTHEIGHT+10+STATUSBARHEIGHT;
	SetWindowPos(&wndTopMost,0,0,uWidth,uHeight,SWP_NOZORDER|SWP_NOMOVE|SWP_NOCOPYBITS);

	//状态栏生成
	CRect a;
	this->GetClientRect(&a);
	m_StatusBar.Create(WS_VISIBLE|WS_CHILD|CCS_BOTTOM,a,this,ID_SBAR);
	SizeWindow();

	//系统菜单
	CMenu*p=GetSystemMenu(FALSE);
	p->AppendMenu(MF_STRING,IDI_MENU_NEW,"新游戏");
	p->AppendMenu(MF_STRING,IDI_MENU_OPTIOM,"设置");

	//弹出菜单
	m_popupMenu->CreatePopupMenu();
	m_popupMenu->AppendMenu(MF_STRING,IDI_MENU_NEW,"新游戏");
	m_popupMenu->AppendMenu(MF_STRING,IDI_MENU_OPTIOM,"设置");
	m_popupMenu->AppendMenu(MF_SEPARATOR,0,"");
	m_popupMenu->AppendMenu(MF_STRING,IDI_MENU_EXIT,"关闭");
	m_popupMenu->AppendMenu(MF_STRING,IDI_MENU_MINISIZE,"最小化");


	CDC* pWinDC=GetDC();
	m_mem3DBkDC.CreateCompatibleDC(pWinDC);
	m_mem3DBkBmp.LoadBitmap(IDB_BMP_BK);
	m_mem3DBkDC.SelectObject(&m_mem3DBkBmp);

	m_memAnimaDC.CreateCompatibleDC(pWinDC);
	m_memAnimaBmp.LoadBitmap(IDB_BMP_ANIMAL);
	m_memAnimaDC.SelectObject(&m_memAnimaBmp);
	int x=GetSystemMetrics(SM_CXSCREEN);
	int y=GetSystemMetrics(SM_CYSCREEN);
	m_memDC.CreateCompatibleDC(pWinDC);
	m_memBmp.CreateCompatibleBitmap(pWinDC,x,y);
	m_memDC.SelectObject(&m_memBmp);




	SetTimer(111,1000,NULL);
	StartNewGame();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCLLKDlg::OnPaint()
{
	CRect rect;
	GetClientRect(&rect);
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);

		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		CPaintDC dc(this);
		DrawGame(&m_memDC);
		dc.BitBlt(0,0,rect.Width(),rect.Height(),&m_memDC,0,0,SRCCOPY);
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CCLLKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCLLKDlg::StartNewGame(void)
{
	CTime t=CTime::GetCurrentTime();
	tGameTime=t;
	strTiShi1="系统时间:"+t.Format("%H:%M:%S");
	m_StatusBar.SetText(strTiShi1,2,0);
	strTiShi2.Format(" 该局时间:00:00:00");
	m_StatusBar.SetText(strTiShi2,1,0);
	strTiShi3.Format("当前游戏:%d行%d列%d种方块",m_nRow-2,m_nCol-2,m_Kind);
	m_StatusBar.SetText(strTiShi3,0,0);

	delete[] m_map;
	m_map=new int[m_nCol*m_nRow];
	for (int iNum=0;iNum<(m_nCol*m_nRow);iNum++)
	{
		m_map[iNum]=BLANK_STATE;
	}
	srand(time(NULL));
	CDWordArray tmpMap;

	for (int i=0;i<(m_nRow-2)*(m_nCol-2)/2;i++)
	{
		int x=rand()%m_Kind;
		tmpMap.Add(x);
		tmpMap.Add(x);

	}

	for (int i=1;i<(m_nCol-1);i++)
	{
		for (int j=1;j<(m_nRow-1);j++)
		{
			INT_PTR nIndex=(int(rand()*0.1+rand()*0.01+rand()))%tmpMap.GetSize();
			m_map[i+j*m_nCol]=tmpMap.GetAt(nIndex);
			tmpMap.RemoveAt(nIndex);

		}
	}
	Invalidate(false);
}

void CCLLKDlg::DrawGame(CDC* pDC)
{

	pDC->FillSolidRect(0,0,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN),BKCOLOR);
	for (int i=0;i<m_nRow;i++)
	{
		for (int j=0;j<m_nCol;j++)
		{
			if(m_map[i*m_nCol+j]==BLANK_STATE)
				continue;
			if(m_b3DBar)
			{
				pDC->StretchBlt(m_iSeekX+(j-1)*FRONTWIDTH,m_iSeekY+(i-1)*FRONTHEIGHT,FRONTWIDTH+FRONTWIDTH*PICBAR/PICWIDTH,FRONTHEIGHT+FRONTHEIGHT*PICBAR/PICHEIGHT,&m_mem3DBkDC,0,PICBKHEIGHT,PICBKWIDTH,PICBKHEIGHT,SRCPAINT);//3d边框
				pDC->StretchBlt(m_iSeekX+(j-1)*FRONTWIDTH,m_iSeekY+(i-1)*FRONTHEIGHT,FRONTWIDTH+FRONTWIDTH*PICBAR/PICWIDTH,FRONTHEIGHT+FRONTHEIGHT*PICBAR/PICHEIGHT,&m_mem3DBkDC,0,0,PICBKWIDTH,PICBKHEIGHT,SRCAND);//3d边框
			}
			pDC->StretchBlt(m_iSeekX+(j-1)*FRONTWIDTH,m_iSeekY+(i-1)*FRONTHEIGHT,FRONTWIDTH,FRONTHEIGHT,&m_memAnimaDC,PICWIDTH,m_map[i*m_nCol+j]*(PICHEIGHT),PICWIDTH,PICHEIGHT,SRCPAINT);
			pDC->StretchBlt(m_iSeekX+(j-1)*FRONTWIDTH,m_iSeekY+(i-1)*FRONTHEIGHT,FRONTWIDTH,FRONTHEIGHT,&m_memAnimaDC,0,			m_map[i*m_nCol+j]*(PICHEIGHT),PICWIDTH,PICHEIGHT,SRCAND);

		}
	}
	if (m_bIsFullScreen)
	{
		COLORREF clrOldText=pDC->GetTextColor();
		int BkOldModle=pDC->GetBkMode();
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkMode(TRANSPARENT);
		pDC->TextOut(540,0,"ESC退出全屏");
		pDC->TextOut(380,0,strTiShi1);
		pDC->TextOut(200,0,strTiShi2);
		pDC->TextOut(0,0,strTiShi3);
		pDC->SetTextColor(clrOldText);
		pDC->SetBkMode(BkOldModle);

		if (IsSelected)
			SelectShell(m_nX1-1,m_nY1-1,pDC);

	}
}

void CCLLKDlg::SizeWindow(void)
{

	if(!m_bIsFullScreen)
	{
		UINT uWidth=DEFAULT_FRAME_X+(m_nCol-2)*FRONTWIDTH+10;
		UINT uHeight=DEFAULT_FRAME_Y+(m_nRow-2)*FRONTHEIGHT+10+STATUSBARHEIGHT;
		int sx=GetSystemMetrics(SM_CXSCREEN)/2-uWidth/2;
		int sy=GetSystemMetrics(SM_CYSCREEN)/2-uHeight/2;
		LONG lStyle=::GetWindowLong(this->m_hWnd,GWL_STYLE);

		::SetWindowLong(this->m_hWnd,GWL_STYLE,lStyle|WS_CAPTION|WS_SYSMENU );
		SetWindowPos(&wndNoTopMost,sx,sy,uWidth,uHeight,SWP_SHOWWINDOW|SWP_NOCOPYBITS|SWP_FRAMECHANGED);

		CRect a;
		this->GetClientRect(&a);
		m_StatusBar.MoveWindow(&a);
		int ina[3];
		if(uWidth>370)
		{
			ina[0]=a.Width()/3+20;
			ina[1]=a.Width()-115;
		}
		else if(uWidth>200)
		{
			ina[0]=a.Width()-115;
			ina[1]=a.Width();
		}
		else
		{
			ina[0]=0;
			ina[1]=a.Width();
		}
		ina[2]=a.Width();
		m_StatusBar.SetParts(3,ina);
		m_StatusBar.ShowWindow(SW_SHOW);
	}
	else
	{
		UINT uWidth=GetSystemMetrics(SM_CXSCREEN);
		UINT uHeight=GetSystemMetrics(SM_CYSCREEN);
		LONG lStyle=::GetWindowLong(this->m_hWnd,GWL_STYLE);
		::SetWindowLong(this->m_hWnd,GWL_STYLE,lStyle&~WS_CAPTION);
		SetWindowPos(&wndTopMost,0,0,uWidth,uHeight,SWP_NOCOPYBITS);
		m_StatusBar.ShowWindow(SW_HIDE);
	}
}
void CCLLKDlg::SelectShell(int x,int y)
{
	int xx=x*FRONTWIDTH+m_iSeekX;
	int yy=y*FRONTHEIGHT+m_iSeekY;
	CDC* pWinDC=GetDC();
	CPen myPen;
	CPen *pOldPen;
	myPen.CreatePen(PS_SOLID,4,RGB(255,0,0));
	pOldPen=pWinDC->SelectObject(&myPen);
	pWinDC->MoveTo(xx,yy);
	pWinDC->LineTo(xx,yy+FRONTHEIGHT);
	pWinDC->LineTo(xx+FRONTWIDTH,yy+FRONTHEIGHT);
	pWinDC->LineTo(xx+FRONTWIDTH,yy);
	pWinDC->LineTo(xx,yy);
	pWinDC->SelectObject(pOldPen);

}

void CCLLKDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int x=(point.x-m_iSeekX)/FRONTWIDTH+((point.x-m_iSeekX)%FRONTWIDTH?1:0);
	int y=(point.y-m_iSeekY)/FRONTHEIGHT+((point.y-m_iSeekY)%FRONTHEIGHT?1:0);
	if(x>0&&y>0&&x<m_nCol&&y<m_nRow)
	{
		if((x!=m_nX1||y!=m_nY1))
		{
			if (x<m_nCol&&y<m_nRow&&m_map[y*m_nCol+x]!=BLANK_STATE)
			{
				if (!IsSelected)
				{
					IsSelected=!IsSelected;
					m_nX1=x;
					m_nY1=y;
				}
				else//Selected
				{
					if (m_map[m_nY1*m_nCol+m_nX1]==m_map[y*m_nCol+x])
					{
						if (IsLink(m_nX1,m_nY1,x,y))
						{
							DrawLink(m_nX1,m_nY1,x,y);
							m_map[m_nY1*m_nCol+m_nX1]=BLANK_STATE;
							m_map[y*m_nCol+x]=BLANK_STATE;
							IsSelected=!IsSelected;
						}
						else
						{
							m_nY1=y;
							m_nX1=x;
						}
					}
					else
					{
						m_nY1=y;
						m_nX1=x;
					}

				}
				if (IsWin())
				{
					Invalidate(false);
					MessageBox("胜利闯关，即将开始新局！","恭喜您",MB_OK|MB_ICONWARNING);
					StartNewGame();
				}
			}
		}
	}

	Invalidate(FALSE);
	//CDialog::OnLButtonDown(nFlags, point);
}

bool CCLLKDlg::IsWin(void)
{
	for (int i=0;i<m_nRow*m_nCol;i++)
	{
		if (m_map[i]!=BLANK_STATE)
		{
			return false;
		}
	}
	return true;
}

bool CCLLKDlg::IsLink(int x1, int y1, int x2, int y2)
{
	StartPoint.x=m_iSeekX+x1*FRONTWIDTH-FRONTWIDTH/2;
	StartPoint.y=m_iSeekY+y1*FRONTHEIGHT-FRONTHEIGHT/2;
	EndPoint.x=m_iSeekX+x2*FRONTWIDTH-FRONTWIDTH/2;
	EndPoint.y=m_iSeekY+y2*FRONTHEIGHT-FRONTHEIGHT/2;
	if (x1==x2)
	{
		if (X1_Link_X2(x1,y1,y2))
		{
			LinkKind=LINK_0_POINT;		
			return true;
		}
	}
	else if (y1==y2)
	{
		if (Y1_Link_Y2(x1,x2,y1))
		{
			LinkKind=LINK_0_POINT;		
			return true;
		}
	}
	if(OneCornerLink(x1,y1,x2,y2))
	{
		LinkKind=LINK_1_POINT;		
		return true;
	}
	else if (TwoCornerLink(x1,y1,x2,y2))
	{
		LinkKind=LINK_2_POINT;		
		return true;
	}
	return false;
}


bool CCLLKDlg::OneCornerLink(int x1, int y1, int x2, int y2)
{
	if (m_map[y1*m_nCol+x2]==BLANK_STATE)//(x2,y1)
	{
		if (X1_Link_X2(x2,y1,y2)&&Y1_Link_Y2(x1,x2,y1))
		{
			CornerPoint1.x=m_iSeekX+x2*FRONTWIDTH-FRONTWIDTH/2;
			CornerPoint1.y=m_iSeekY+y1*FRONTHEIGHT-FRONTHEIGHT/2;
			return true;
		}

	}
	if (m_map[y2*m_nCol+x1]==BLANK_STATE)
	{
		if(X1_Link_X2(x1,y1,y2)&&Y1_Link_Y2(x1,x2,y2))
		{
			CornerPoint1.x=m_iSeekX+x1*FRONTWIDTH-FRONTWIDTH/2;
			CornerPoint1.y=m_iSeekY+y2*FRONTHEIGHT-FRONTHEIGHT/2;		
			return true;
		}
	}
	return false;
}

bool CCLLKDlg::TwoCornerLink(int x1, int y1, int x2, int y2)
{
	for (int i=0;i<m_nCol;i++)
	{
		if (i!=x1&&i!=x2)
		{
			if (m_map[y1*m_nCol+i]==BLANK_STATE&&m_map[y2*m_nCol+i]==BLANK_STATE)
			{

				if (X1_Link_X2(i,y1,y2)&&Y1_Link_Y2(i,x2,y2)&&Y1_Link_Y2(i,x1,y1))
				{
					CornerPoint1.x=m_iSeekX+i*FRONTWIDTH-FRONTWIDTH/2;
					CornerPoint1.y=m_iSeekY+y1*FRONTHEIGHT-FRONTHEIGHT/2;				
					CornerPoint2.x=m_iSeekX+i*FRONTWIDTH-FRONTWIDTH/2;
					CornerPoint2.y=m_iSeekY+y2*FRONTHEIGHT-FRONTHEIGHT/2;
					return true;
				}

			}
			else
				continue;
		}
	}
	for (int i=0;i<m_nRow;i++)
	{
		if (i!=y1&&i!=y2)
		{
			if (m_map[i*m_nCol+x1]==BLANK_STATE&&m_map[i*m_nCol+x2]==BLANK_STATE)
			{

				if (Y1_Link_Y2(x1,x2,i)&&X1_Link_X2(x1,i,y1)&&X1_Link_X2(x2,i,y2))
				{
					CornerPoint1.x=m_iSeekX+x1*FRONTWIDTH-FRONTWIDTH/2;
					CornerPoint1.y=m_iSeekY+i*FRONTHEIGHT-FRONTHEIGHT/2;				
					CornerPoint2.x=m_iSeekX+x2*FRONTWIDTH-FRONTWIDTH/2;
					CornerPoint2.y=m_iSeekY+i*FRONTHEIGHT-FRONTHEIGHT/2;				
					return true;
				}
			}
			else
				continue;
		}
	}

	return false;
}

bool CCLLKDlg::X1_Link_X2(int x, int y1, int y2)
{

	if (y1>y2)
	{
		int n=y1;
		y1=y2;
		y2=n;
	}
	if (y2-y1==1)
		return true;
	else
	{

		int n=y1+1;
		for (int i=n;i<y2;i++)
		{

			if (m_map[i*m_nCol+x]!=BLANK_STATE)
				break;
			n++;
		}
		if (n==y2)
			return true;
	}
	return false;
}

bool CCLLKDlg::Y1_Link_Y2(int x1, int x2, int y)
{
	if (x1>x2)
	{
		int n=x1;
		x1=x2;
		x2=n;
	}
	if (x2-x1==1)
		return true;
	else
	{

		int n=x1+1;
		for (int i=n;i<x2;i++)
		{

			if (m_map[y*m_nCol+i]!=BLANK_STATE)
				break;
			n++;
		}
		if (n==x2)
			return true;
	}
	return false;
}

void CCLLKDlg::DrawLink(int x1, int y1, int x2, int y2)
{
	CDC* pWinDC=GetDC();
	CPen *pOldPen,RedPen;
	RedPen.CreatePen(PS_SOLID,5,RGB(255,0,0));
	pOldPen=pWinDC->SelectObject(&RedPen);
	switch (LinkKind)
	{
	case LINK_0_POINT:
		pWinDC->MoveTo(StartPoint);
		pWinDC->LineTo(EndPoint);
		break;
	case LINK_1_POINT:
		pWinDC->MoveTo(StartPoint);
		pWinDC->LineTo(CornerPoint1);		
		pWinDC->LineTo(EndPoint);		
		break;
	case LINK_2_POINT:
		pWinDC->MoveTo(StartPoint);
		pWinDC->LineTo(CornerPoint1);
		pWinDC->LineTo(CornerPoint2);
		pWinDC->LineTo(EndPoint);		
		break;

	}
	Sleep(100);
	pWinDC->SelectObject(pOldPen);
}

void CCLLKDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(IsSelected)
		SelectShell(m_nX1-1,m_nY1-1);
	CDialog::OnLButtonUp(nFlags, point);
}

void CCLLKDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nID==IDI_MENU_OPTIOM)
	{
		OnConfig();
	}
	else if (nID==IDI_MENU_NEW)
	{
		StartNewGame();
	}
	else if (nID==IDI_MENU_EXIT)
	{
		OnClose();
	}
	CDialog::OnSysCommand(nID, lParam);
}


void CCLLKDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CTime t=CTime::GetCurrentTime();
	strTiShi1="系统时间:"+t.Format("%H:%M:%S");
	strTiShi2=" 该局时间:"+(t-tGameTime).Format("%H:%M:%S");
	if(!m_bIsFullScreen)
	{
		m_StatusBar.SetText(strTiShi1,2,0);
		m_StatusBar.SetText(strTiShi2,1,0);
	}
	else
		Invalidate(false);
	CDialog::OnTimer(nIDEvent);
}

void CCLLKDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (MessageBox("确认退出","系统提示",MB_YESNO|MB_ICONQUESTION)==IDYES)
	{
		KillTimer(111);
		PostQuitMessage(0);
		CDialog::OnClose();
	}

}
void CCLLKDlg::OnMyMiniSize()
{
	PostMessage(WM_SYSCOMMAND,SC_MINIMIZE,0);
}
void CCLLKDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ClientToScreen(&point);
	m_popupMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL,point.x,point.y,this);
	CDialog::OnRButtonDown(nFlags, point);
}

void CCLLKDlg::OnConfig(void)
{
	COption dlg;
	dlg.m_uColNum=m_nCol-2;
	dlg.m_uRowNum=m_nRow-2;
	dlg.m_uKindNum=m_Kind;
	dlg.m_iBlockWidth=FRONTWIDTH;
	dlg.m_iBlockHeight=FRONTHEIGHT;
	dlg.m_bFullScreen=m_bIsFullScreen;
	dlg.m_b3DBar=m_b3DBar;
	if(dlg.DoModal()==IDOK)
	{
		m_nCol=dlg.m_uColNum+2;
		m_nRow=dlg.m_uRowNum+2;
		m_Kind=dlg.m_uKindNum;
		FRONTWIDTH=dlg.m_iBlockWidth;
		FRONTHEIGHT=dlg.m_iBlockHeight;
		m_bIsFullScreen=dlg.m_bFullScreen;
		m_b3DBar=dlg.m_b3DBar;
		m_iSeekX=dlg.SeekX;
		m_iSeekY=dlg.SeekY;
		SizeWindow();
		if(dlg.m_bNeedReStart)
			StartNewGame();
	}
}


BOOL CCLLKDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)
	{
		if(m_bIsFullScreen)
		{
			m_bIsFullScreen=false;
			m_iSeekX=m_iSeekY=0;
			SizeWindow();
		}
		else
			OnClose();

		return NULL;

	}
	return CDialog::PreTranslateMessage(pMsg);
}

//内存设备-选框
void CCLLKDlg::SelectShell(int x, int y, CDC* pDC)
{
	int xx=x*FRONTWIDTH+m_iSeekX;
	int yy=y*FRONTHEIGHT+m_iSeekY;
	CPen myPen;
	CPen *pOldPen;
	myPen.CreatePen(PS_SOLID,4,RGB(255,0,0));
	pOldPen=pDC->SelectObject(&myPen);
	pDC->MoveTo(xx,yy);
	pDC->LineTo(xx,yy+FRONTHEIGHT);
	pDC->LineTo(xx+FRONTWIDTH,yy+FRONTHEIGHT);
	pDC->LineTo(xx+FRONTWIDTH,yy);
	pDC->LineTo(xx,yy);
	pDC->SelectObject(pOldPen);
}
