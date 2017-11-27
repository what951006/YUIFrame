#pragma once
#include "YUIObject.h"
#include "YButton.h"

class MainWindow :public YUIObject
{
public:
	MainWindow(void);
	~MainWindow(void);
	
	virtual void OnMouseDown(const YPoint) override;
private:
	YButton m_btn;
};

