#pragma once
#include "YUIObject.h"
#include "YButton.h"

class MainWindow :public YUIObject
{
public:
	MainWindow(void);
	~MainWindow(void);


	virtual void OnMouseLClicked();
private:
	YButton *m_btn;

	YButton *m_btn2;
};

