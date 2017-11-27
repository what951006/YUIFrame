#pragma once
#include "YUIObject.h"
#include "YButton.h"

class MainWindow :public YUIObject
{
public:
	MainWindow(void);
	~MainWindow(void);
	
private:
	YButton m_btn;
};

