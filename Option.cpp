// Option.cpp : 实现文件
//

#include "stdafx.h"
#include "CLLK.h"
#include "Option.h"


// COption 对话框

IMPLEMENT_DYNAMIC(COption, CDialog)

COption::COption(CWnd* pParent /*=NULL*/)
	: CDialog(COption::IDD, pParent)
	, m_uColNum(0)
	, m_uRowNum(0)
	, m_uKindNum(0)
	, m_iBlockWidth(0)
	, m_iBlockHeight(0)
	, SeekX(0)
	, SeekY(0)
	, m_bFullScreen(false)
	, m_bNeedReStart(false)
	, m_iOldCol(0)
	, m_iOldRow(0)
	, m_iOldKind(0)
	, m_b3DBar(false)
{

}

COption::~COption()
{
}

void COption::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_uColNum);
	DDX_Text(pDX, IDC_EDIT2, m_uRowNum);
	DDX_Text(pDX, IDC_EDIT3, m_uKindNum);
	DDX_Text(pDX, IDC_EDIT4, m_iBlockWidth);
	DDX_Text(pDX, IDC_EDIT5, m_iBlockHeight);
	DDX_Control(pDX, IDC_CHECK1, m_ctrlCheck1);
	DDX_Control(pDX, IDC_CHECK_3D_BAR, m_ctrl3DBar);
}


BEGIN_MESSAGE_MAP(COption, CDialog)
	ON_BN_CLICKED(IDOK, &COption::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK1, &COption::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON_DELAUFT, &COption::OnBnClickedButtonDelauft)
	ON_BN_CLICKED(IDC_CHECK_3D_BAR, &COption::OnBnClickedCheck3dBar)
END_MESSAGE_MAP()


// COption 消息处理程序

void COption::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if((m_uColNum%2==0||m_uRowNum%2==0)&&m_iBlockWidth>29&&m_iBlockHeight>39)
	{
		if ((m_uColNum>=2&&m_uRowNum>=2&&m_uKindNum>0&&m_uKindNum<MAX_BLOCK_KIND+1))
		{
			UINT x=GetSystemMetrics(SM_CXSCREEN);
			UINT y=GetSystemMetrics(SM_CYSCREEN);
			if(m_uRowNum*m_iBlockHeight+DEFAULT_FRAME_Y>y||m_uColNum*m_iBlockWidth+DEFAULT_FRAME_X>x)
				MessageBox("该设置相对于您的屏幕来说太大！","系统提示",MB_OK|MB_ICONWARNING);
			else
			{
				if (m_uColNum!=m_iOldCol||m_uKindNum!=m_iOldKind||m_uRowNum!=m_iOldRow)
					m_bNeedReStart=true;
				if(m_bFullScreen)
				{
					SeekY=(y-m_uRowNum*m_iBlockHeight)/2;
					SeekX=(x-m_uColNum*m_iBlockWidth)/2;
				}
				else
				{
					SeekY=0;
					SeekX=0;
				}
				OnOK();
				return;
			}
		}
	}
	else
		MessageBox("请输入有效数据！","系统提示",MB_OK|MB_ICONWARNING);
}

void COption::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bFullScreen=!m_bFullScreen;
}

BOOL COption::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if(m_bFullScreen)
		m_ctrlCheck1.SetCheck(BST_CHECKED);
	if(m_b3DBar)
		m_ctrl3DBar.SetCheck(BST_CHECKED);
	m_iOldCol=m_uColNum;
	m_iOldRow=m_uRowNum;
	m_iOldKind=m_uKindNum;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void COption::OnBnClickedButtonDelauft()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bFullScreen=false;
	m_ctrlCheck1.SetCheck(0);
	m_iBlockHeight=PICHEIGHT;
	m_iBlockWidth=PICWIDTH;
	m_uColNum=COLCOUNT-2;
	m_uRowNum=ROWCOUNT-2;
	UpdateData(false);
}


void COption::OnBnClickedCheck3dBar()
{
	// TODO: 在此添加控件通知处理程序代码
	m_b3DBar=!m_b3DBar;
}
