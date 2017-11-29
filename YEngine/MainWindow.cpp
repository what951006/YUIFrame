#include "stdafx.h"
#include "MainWindow.h"
#include "YButton.h"

MainWindow::MainWindow(void)
{
	YUIObject *pObj=new YUIObject(this);
	pObj->SetGeometry(200,100,800,900);

	m_btn=new YButton(pObj);
	m_btn->SetGeometry(0,80,20,20);

	m_btn2=new YButton(pObj);
	m_btn2->SetGeometry(120,80,20,20);


	//YPoint pos=YPoint::MapFromMain(&m_btn);
	//char buf[128]={0};
	//sprintf(buf,"x:%d , y:%d",pos.x,pos.y);
	//
	//MessageBoxA(NULL,buf,"Hello",NULL);

}


MainWindow::~MainWindow(void)
{
}

void MainWindow::OnMouseDown(const YPoint pos)
{

	char buf[128]={0};
	sprintf_s(buf,"MainWindows :  x:%d , y:%d",pos.x,pos.y);
	
	MessageBoxA(NULL,buf,"Hello",NULL);
}

void MainWindow::OnMouseMove(const YPoint pos)
{
	char buf[128]={0};
	sprintf_s(buf,"MainWindows :  x:%d , y:%d  ",pos.x,pos.y);
	SetWindowTextA(this->GetHwnd(),buf);
}
