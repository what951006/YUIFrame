#include "stdafx.h"
#include "MainWindow.h"
#include "YButton.h"
#include "YMessageBox.h"

MainWindow::MainWindow(void)
{
//	YUIObject *pObj=new YUIObject(this);
//	pObj->SetGeometry(200,100,800,900);

	m_btn=new YButton("��½",this);
	m_btn->SetGeometry(80,80,250,24);
	//pObj->Show(false);

	m_btn2=new YButton("ȷ��",this);
	m_btn2->SetGeometry(15,15,250,30);
}


MainWindow::~MainWindow(void)
{
}

void MainWindow::OnMouseLClicked()
{
	YMessageBox::Show(this);
}
