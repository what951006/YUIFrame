#include "stdafx.h"
#include "YMessageBox.h"
#include "YUIObject.h"
#include "YWin32Application.h"
#include "YDialog.h"
YMessageBox::YMessageBox(void)
{
}


YMessageBox::~YMessageBox(void)
{
}

YMB_TYPE YMessageBox::Show(YUIObject*pParent)
{
	YDialog dlg(pParent->GetHwnd());
	dlg.Modal();
	return YMB_OK;
}
