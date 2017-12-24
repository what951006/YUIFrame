#include "stdafx.h"
#include "MainWindow.h"
#include "YButton.h"
#include "YMessageBox.h"
#include "YLayout.h"
MainWindow::MainWindow(void)
	:YUIObject()
{
	// default :create frameless windows

	/*DWORD dwStyle = ::GetWindowLong(m_hWnd, GWL_STYLE)
		| WS_MAXIMIZEBOX | WS_MINIMIZEBOX
		| WS_SYSMENU | WS_SIZEBOX | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	dwStyle &= ~(WS_CAPTION|WS_THICKFRAME);

	SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);
*/

	YUIObject *pObj=new YUIObject(this);
	pObj->SetGeometry(200,100,800,900);

	m_btn=new YButton("登陆",pObj);
	m_btn->SetGeometry(80,80,250,24);
	//pObj->Show(false);

	m_btn2=new YButton("确定",this);
	m_btn2->SetGeometry(45,15,50,30);

	
	YButton* m_btn3=new YButton("确定",this);
	m_btn3->SetGeometry(95,15,50,30);


	YButton*m_btn4=new YButton("确定",this);
	m_btn4->SetGeometry(165,15,50,30);


	YButton*m_btn5=new YButton("确定",this);
	m_btn5->SetGeometry(230,15,50,30);


	m_btn->AddEventObserver(YEVENT_MOUSE_CLICKED_L,this);
}


MainWindow::~MainWindow(void)
{
}

void MainWindow::OnMouseLClicked()
{
	YMessageBox::Show(this);
}

bool MainWindow::OnEventOccoured(EventObject &obj)
{
	if (obj.sender == m_btn)
	{
		if(YEVENT_MOUSE_CLICKED_L == obj.type)
		{
			HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE) ;
			YDEBUG("Clicked again");
			return true;
		}
	}
	return YUIObject::OnEventOccoured(obj);
}
