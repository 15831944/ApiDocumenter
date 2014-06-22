
// HomsApiTool.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "afxwin.h"
#include "HomsApiTool.h"
#include "MainFrm.h"

#include "HomsApiToolDoc.h"
#include "HomsApiToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHomsApiToolApp

BEGIN_MESSAGE_MAP(CHomsApiToolApp, CWinAppEx)
    ON_COMMAND(ID_APP_ABOUT, &CHomsApiToolApp::OnAppAbout)
    // �����ļ��ı�׼�ĵ�����
    ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
    ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CHomsApiToolApp ����

CHomsApiToolApp::CHomsApiToolApp()
{
    m_bHiColorIcons = TRUE;

    // TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
    //Ϊ CompanyName.ProductName.SubProduct.VersionInformation
    SetAppID(_T("HomsApiTool.AppID.NoVersion"));

    // TODO: �ڴ˴���ӹ�����룬
    // ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CHomsApiToolApp ����

CHomsApiToolApp theApp;


// CHomsApiToolApp ��ʼ��

BOOL CHomsApiToolApp::InitInstance()
{
    CWinAppEx::InitInstance();
    AfxInitRichEdit2();

    EnableTaskbarInteraction(FALSE);

    // ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()    
    // AfxInitRichEdit2();

    // ��׼��ʼ��
    // ���δʹ����Щ���ܲ�ϣ����С
    // ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
    // ����Ҫ���ض���ʼ������
    // �������ڴ洢���õ�ע�����
    // TODO: Ӧ�ʵ��޸ĸ��ַ�����
    // �����޸�Ϊ��˾����֯��
    SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
    LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


    InitContextMenuManager();

    InitKeyboardManager();

    InitTooltipManager();
    CMFCToolTipInfo ttParams;
    ttParams.m_bVislManagerTheme = TRUE;
    theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
        RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

    // ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
    // �������ĵ�����ܴ��ں���ͼ֮�������
    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate(
        IDR_MAINFRAME,
        RUNTIME_CLASS(CHomsApiToolDoc),
        RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
        RUNTIME_CLASS(CHomsApiToolView));
    if (!pDocTemplate)
        return FALSE;
    AddDocTemplate(pDocTemplate);


    // ������׼ shell ���DDE�����ļ�������������
    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);

    // ���á�DDE ִ�С�
    EnableShellOpen();
    RegisterShellFileTypes(TRUE);


    // ��������������ָ����������
    // �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
    if (!ProcessShellCommand(cmdInfo))
        return FALSE;

    // Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
    m_pMainWnd->ShowWindow(SW_SHOW);
    m_pMainWnd->UpdateWindow();
    // �������к�׺ʱ�ŵ��� DragAcceptFiles
    //  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand ֮����
    // ������/��
    m_pMainWnd->DragAcceptFiles();
    return TRUE;
}

// CHomsApiToolApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

// �Ի�������
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CHomsApiToolApp::OnAppAbout()
{
    CAboutDlg aboutDlg;
    aboutDlg.DoModal();
}

// CHomsApiToolApp �Զ������/���淽��

void CHomsApiToolApp::PreLoadState()
{
    BOOL bNameValid;
    CString strName;
    bNameValid = strName.LoadString(IDS_EDIT_MENU);
    ASSERT(bNameValid);
    //GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CHomsApiToolApp::LoadCustomState()
{
}

void CHomsApiToolApp::SaveCustomState()
{
}

// CHomsApiToolApp ��Ϣ�������



