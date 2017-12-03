#include "stdafx.h"
#include "YUIObject.h"
#include "YDialog.h"
#include "YMessageBox.h"
#include "YWin32Application.h"

YMessageBox::YMessageBox(YUIObject *pParent)
	:YDialog(pParent->GetHwnd())
{
	SetWindowLong(GetHwnd(),   GWL_STYLE,   WS_SYSMENU|WS_CAPTION); 
	SetWindowTitle("Warning");

	m_btn=new YButton("ÄãºÃ",this);
	m_btn->SetGeometry(90,30,70,20);
	
	YUIObject *pMainDlg=YWin32Application::GetUIObjectByHWND(GetHwnd());
	YRect &&re=pMainDlg->GetGeometry();
	SetGeometry(re.x+(re.width-200)/2,re.y+(re.height-150)/2,200,150);
}


YMessageBox::~YMessageBox(void)
{

}

bool YMessageBox::OnEventOccoured(EventObject obj)
{
	return YDialog::OnEventOccoured(obj);
}


YMB_TYPE YMessageBox::Show(YUIObject*pParent)
{
	YMessageBox msgbox(pParent);
	msgbox.Modal();
	return YMB_OK;
}
