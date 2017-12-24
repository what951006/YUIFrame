#pragma once
#include "YUIObject.h"
#include "YButton.h"
#include "YEvent.h"

class MainWindow :public YUIObject
{
public:
	MainWindow(void);
	~MainWindow(void);


	virtual void OnMouseLClicked();

	virtual bool OnEventOccoured(EventObject &obj);

	virtual void OnTimerEvent(unsigned int nTimerID);
private:
	YButton *m_btn;

	YButton *m_btn2;
};

