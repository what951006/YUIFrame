#include "stdafx.h"
#include "YMessageBox.h"
#include "YUIObject.h"
#include "YWin32Application.h"
#include "YDialog.h"
YMessageBox::YMessageBox(YUIObject *pParent)
	:YDialog(pParent->GetHwnd())
{

	DWORD   dwStyle   =   GetWindowLong(GetHwnd(),   GWL_STYLE);    
	//dwStyle &=   ~(WS_SIZEBOX|WS_MAXIMIZEBOX|WS_MINIMIZEBOX|WS_SYSMENU);    
	dwStyle = WS_SYSMENU|WS_CAPTION;
	//dwStyle &= 
	SetWindowLong(GetHwnd(),   GWL_STYLE,   dwStyle); 

	SetWindowTitle("YMessageBox:Warning");
	YUIObject *pMainDlg=YWin32Application::GetUIObjectByHWND(GetHwnd());
	YRect &&re=pMainDlg->GetGeometry();
	SetGeometry(re.x+(re.width-300)/2,re.y+(re.height-200)/2,300,200);
}


YMessageBox::~YMessageBox(void)
{

}

bool YMessageBox::OnEventOccoured(EventObject obj)
{
	return YUIObject::OnEventOccoured(obj);
}


YMB_TYPE YMessageBox::Show(YUIObject*pParent)
{
	YMessageBox msgbox(pParent);
	msgbox.Modal();
	return YMB_OK;
}
