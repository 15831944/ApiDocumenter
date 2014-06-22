
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "HomsApiTool.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
    ON_WM_CREATE()
    ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
    ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
END_MESSAGE_MAP()

static UINT indicators[] =
{
    ID_SEPARATOR,           // ״̬��ָʾ��
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
    // TODO: �ڴ����ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
        return -1;

    BOOL bNameValid;

    // �������ڻ��������û�����Ԫ�ص��Ӿ�������
    CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));

    //if (!m_wndMenuBar.Create(this))
    //{
    //    TRACE0("δ�ܴ����˵���\n");
    //    return -1;      // δ�ܴ���
    //}

    //m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

    // ��ֹ�˵����ڼ���ʱ��ý���
    CMFCPopupMenu::SetForceMenuFocus(FALSE);

    //if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
    //    !m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
    //{
    //    TRACE0("δ�ܴ���������\n");
    //    return -1;      // δ�ܴ���
    //}

    CString strToolBarName;
    bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
    ASSERT(bNameValid);
    //m_wndToolBar.SetWindowText(strToolBarName);

    CString strCustomize;
    bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
    ASSERT(bNameValid);
    //m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

    if (!m_wndStatusBar.Create(this))
    {
        TRACE0("δ�ܴ���״̬��\n");
        return -1;      // δ�ܴ���
    }
    m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

    // TODO: �������ϣ���������Ͳ˵�����ͣ������ɾ��������
    //m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
    //m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
    EnableDocking(CBRS_ALIGN_ANY);
    //DockPane(&m_wndMenuBar);
    //DockPane(&m_wndToolBar);


    // ���� Visual Studio 2005 ��ʽͣ��������Ϊ
    CDockingManager::SetDockingMode(DT_SMART);
    // ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
    EnableAutoHidePanes(CBRS_ALIGN_ANY);

    // ���ù�������ͣ�����ڲ˵��滻
    EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

    // ���ÿ���(��ס Alt �϶�)�������Զ���
    CMFCToolBar::EnableQuickCustomization();

    return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    //cs.cx = 100;
    //cs.cy=800;
    //cs.style |= FWS_ADDTOTITLE;
    //lstrcpy(cs.lpszName, _T("tet"));

    if( !CFrameWndEx::PreCreateWindow(cs) )
        return FALSE;
    // TODO: �ڴ˴�ͨ���޸�
    //  CREATESTRUCT cs ���޸Ĵ��������ʽ

    return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
    CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
    CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ��������

void CMainFrame::OnViewCustomize()
{
    CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* ɨ��˵�*/);
    pDlgCust->Create();
}