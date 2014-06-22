
// HomsApiToolView.h : CHomsApiToolView ��Ľӿ�
//

#pragma once

#include "resource.h"
#include "ApiTypeDefine.h"
#include "ApiDocLib.h"
#include "EditBrowseCtrlXml.h"

class CHomsApiToolView : public CFormView
{
protected: // �������л�����
    CHomsApiToolView();
    DECLARE_DYNCREATE(CHomsApiToolView)

public:
    enum{ IDD = IDD_HOMSAPITOOL_FORM };

// ����
public:
    CHomsApiToolDoc* GetDocument() const;

// ����
public:

// ��д
public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
    virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
    virtual ~CHomsApiToolView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
    afx_msg void OnFilePrintPreview();
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonShift();
    afx_msg void OnBnClickedButtonExit();

public:
    CEditBrowseCtrlXml editBrowseInputFile;
    CEditBrowseCtrlXml editBrowseOutputFile;
private:
    CString fileNameInputFile;
    CString fileNameOutputFile;
    CRect rectForm;
    ApiDoc *apiDoc;
private:
    int LogerError(CString info);
    int LogerInfo(CString info);
    int LogerDebug(CString info);
public:
    CRichEditCtrl richEditCtrlInfo;
    afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // HomsApiToolView.cpp �еĵ��԰汾
inline CHomsApiToolDoc* CHomsApiToolView::GetDocument() const
   { return reinterpret_cast<CHomsApiToolDoc*>(m_pDocument); }
#endif

