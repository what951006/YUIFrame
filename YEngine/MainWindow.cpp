#include "stdafx.h"
#include "MainWindow.h"


MainWindow::MainWindow(void)
	:m_btn(this)
{
	m_btn.SetGeometry(0,80,20,20);


	//YPoint pos=YPoint::MapFromMain(&m_btn);
	//char buf[128]={0};
	//sprintf(buf,"x:%d , y:%d",pos.x,pos.y);
	//
	//MessageBoxA(NULL,buf,"Hello",NULL);
}


MainWindow::~MainWindow(void)
{
}
