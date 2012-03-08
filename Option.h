#pragma once
#include "afxwin.h"


// COption 对话框

class COption : public CDialog
{
	DECLARE_DYNAMIC(COption)

public:
	COption(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COption();

// 对话框数据
	enum { IDD = IDD_DIALOG_OPTION };
protected:
	int m_iOldCol;
	int m_iOldRow;
	int m_iOldKind;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	UINT m_uColNum;
	UINT m_uRowNum;
	UINT m_uKindNum;
	int m_iBlockWidth;
	int m_iBlockHeight;
	int SeekX;
	int SeekY;
	bool m_bNeedReStart;
	CButton m_ctrlCheck1;
	bool m_bFullScreen;
	
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCheck1();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonDelauft();

public:
	CButton m_ctrl3DBar;
public:
	bool m_b3DBar;
public:
	afx_msg void OnBnClickedCheck3dBar();
};
