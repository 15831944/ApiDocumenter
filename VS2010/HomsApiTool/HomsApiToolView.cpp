
// HomsApiToolView.cpp : CHomsApiToolView ���ʵ��
//
#include <string>

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "HomsApiTool.h"
#endif

#include "HomsApiToolDoc.h"
#include "HomsApiToolView.h"
#include "ApiDocExcel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHomsApiToolView

IMPLEMENT_DYNCREATE(CHomsApiToolView, CFormView)

BEGIN_MESSAGE_MAP(CHomsApiToolView, CFormView)
    ON_WM_CONTEXTMENU()
    ON_WM_RBUTTONUP()
    ON_BN_CLICKED(IDC_BUTTON_SHIFT, &CHomsApiToolView::OnBnClickedButtonShift)
    ON_BN_CLICKED(IDC_BUTTON_EXIT, &CHomsApiToolView::OnBnClickedButtonExit)
    ON_WM_SIZE()
END_MESSAGE_MAP()

// CHomsApiToolView ����/����

CHomsApiToolView::CHomsApiToolView()
    : CFormView(CHomsApiToolView::IDD)
{
    // TODO: �ڴ˴���ӹ������
    SetCurrentDirectory("./");
    apiDoc = ApiDoc::CreateApiDoc();
    apiDoc->Init();
}

CHomsApiToolView::~CHomsApiToolView()
{
    apiDoc->Release();
    apiDoc = NULL;
}

void CHomsApiToolView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    DDX_Control( pDX, IDC_MFCEDITBROWSE_INPUT_FILE, editBrowseInputFile);
    DDX_Control( pDX, IDC_MFCEDITBROWSE_OUTPUT_FILE, editBrowseOutputFile);
    DDX_Control(pDX, IDC_RICHEDIT2_INFO, richEditCtrlInfo);
}

BOOL CHomsApiToolView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: �ڴ˴�ͨ���޸�
    //  CREATESTRUCT cs ���޸Ĵ��������ʽ

    return CFormView::PreCreateWindow(cs);
}

void CHomsApiToolView::OnInitialUpdate()
{
    CFormView::OnInitialUpdate();
    GetParentFrame()->RecalcLayout();
    ResizeParentToFit();

    editBrowseInputFile.EnableFileBrowseButton();
    editBrowseInputFile.m_strFileType=_T("Xml Files(*.xml)|*.xml|All Files (*.*)|*.*||");
}

void CHomsApiToolView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
    ClientToScreen(&point);
    OnContextMenu(this, point);
}

void CHomsApiToolView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
    //theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CHomsApiToolView ���

#ifdef _DEBUG
void CHomsApiToolView::AssertValid() const
{
    CFormView::AssertValid();
}

void CHomsApiToolView::Dump(CDumpContext& dc) const
{
    CFormView::Dump(dc);
}

CHomsApiToolDoc* CHomsApiToolView::GetDocument() const // �ǵ��԰汾��������
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHomsApiToolDoc)));
    return (CHomsApiToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CHomsApiToolView ��Ϣ�������
void CHomsApiToolView::OnBnClickedButtonShift()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    LogerInfo(_T("Shift"));

    CEdit *pEdit = (CEdit*)(&editBrowseInputFile);
    CString strInput;
    pEdit->GetWindowText(strInput);

    pEdit = (CEdit*)(&editBrowseOutputFile);
    CString strOutput;
    pEdit->GetWindowText(strOutput);

    fileNameInputFile = strInput;
    fileNameOutputFile = strOutput;

    LogerDebug(strInput);
    LogerDebug(strOutput);

    std::string strFiledInput(strInput.GetBuffer());
    apiDoc->LoadFuncFromXml(strFiledInput.c_str());

    std::vector<FunctionItem*> *funcs = NULL;
    int iRet = apiDoc->GetFuncList(&funcs);
    if(iRet >= 0 && funcs){
        CString logMessage;
        logMessage.Format(_T("Function Count: %d"), funcs->size());
        LogerDebug(logMessage);

        iRet = ApiDocExcel::SaveDataToExcel(funcs, "api.xlsx");
        if(iRet >= 0){
            LogerDebug("Save Data To Excel Success.");
        }else{
            logMessage.Format(_T("Save Data To Excel Faild.iRet=%d"), iRet);
            LogerDebug(logMessage);
        }
    }
}


void CHomsApiToolView::OnBnClickedButtonExit()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
}

int CHomsApiToolView::LogerDebug(CString info)
{
    int line = richEditCtrlInfo.GetLineCount();
    CString logMessage;
    logMessage.Format(_T("%d: %s\r\n"), line, info);

    CHARFORMAT cf;
    richEditCtrlInfo.GetDefaultCharFormat(cf);
    cf.dwMask = CFM_COLOR;
    cf.dwEffects = 0;
    cf.crTextColor = RGB(256, 0, 0);
   
    // Set Focus to auto scroll the Richedit window and update it
    richEditCtrlInfo.SetFocus();
    richEditCtrlInfo.SetSel(0xFFFF, 0xFFFF);
                    
    richEditCtrlInfo.HideSelection(FALSE, TRUE);
                    
    richEditCtrlInfo.SetSelectionCharFormat(cf);
    richEditCtrlInfo.ReplaceSel(logMessage);
    richEditCtrlInfo.HideSelection(TRUE, TRUE);

    return richEditCtrlInfo.GetLineCount();
}

int CHomsApiToolView::LogerError(CString info)
{
    int line = richEditCtrlInfo.GetLineCount();
    CString logMessage;
    logMessage.Format(_T("%d: %s\r\n"), line, info);

    CHARFORMAT cf;
    richEditCtrlInfo.GetDefaultCharFormat(cf);
    cf.dwMask = CFM_COLOR;
    cf.dwEffects = 0;
    cf.crTextColor = RGB(160, 0, 0);
   
    // Set Focus to auto scroll the Richedit window and update it
    richEditCtrlInfo.SetFocus();
    richEditCtrlInfo.SetSel(0xFFFF, 0xFFFF);
                    
    richEditCtrlInfo.HideSelection(FALSE, TRUE);
                    
    richEditCtrlInfo.SetSelectionCharFormat(cf);
    richEditCtrlInfo.ReplaceSel(logMessage);
    richEditCtrlInfo.HideSelection(TRUE, TRUE);

    return richEditCtrlInfo.GetLineCount();
}

int CHomsApiToolView::LogerInfo(CString info)
{
    int line = richEditCtrlInfo.GetLineCount();
    CString logMessage;
    logMessage.Format(_T("%d: %s\r\n"), line, info);

    CHARFORMAT cf;
    richEditCtrlInfo.GetDefaultCharFormat(cf);
    cf.dwMask = CFM_COLOR;
    cf.dwEffects = 0;
    cf.crTextColor = RGB(30, 0, 0);
   
    // Set Focus to auto scroll the Richedit window and update it
    richEditCtrlInfo.SetFocus();
    richEditCtrlInfo.SetSel(0xFFFF, 0xFFFF);
                    
    richEditCtrlInfo.HideSelection(FALSE, TRUE);
                    
    richEditCtrlInfo.SetSelectionCharFormat(cf);
    richEditCtrlInfo.ReplaceSel(logMessage);
    richEditCtrlInfo.HideSelection(TRUE, TRUE);

    return richEditCtrlInfo.GetLineCount();
}


void CHomsApiToolView::OnSize(UINT nType, int cx, int cy)
{
    CFormView::OnSize(nType, cx, cy);

    if (richEditCtrlInfo.GetSafeHwnd()) //�ж�RichEdit�ؼ��Ƿ��ʼ���ɹ�  
    {  
        if (nType==SIZE_RESTORED)  
        {  
            CRect rs;  
            GetClientRect(&rs);  //�õ�������CFormView�Ĵ�С��λ��  

            CRect rsOld;
            richEditCtrlInfo.GetWindowRect(rsOld);
            ScreenToClient(rsOld);

            richEditCtrlInfo.SetWindowPos(this, 0, rsOld.top, rs.Width(), rs.Height() - rsOld.top, 
                SWP_SHOWWINDOW | SWP_NOZORDER);  
            //���ո�����Ĵ�С��λ�ã���RichEdit�ؼ��Ƶ���Ӧ��λ��  
        }
    }
}
