#pragma once

#include "resource.h"

class CEditBrowseCtrlXml : public CMFCEditBrowseCtrl
{
	//DECLARE_DYNAMIC(CEditBrowseCtrlXml)

public:
	CEditBrowseCtrlXml();
	virtual ~CEditBrowseCtrlXml();

public:
	CString m_strFileType;//�Զ��忪�ļ�����

private:
	virtual void OnBrowse();//��дCMFCEditBrowseCtrl�Ĵ򿪺���

protected:
	DECLARE_MESSAGE_MAP()
};