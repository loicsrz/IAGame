#include "Thief.h"


bool Thief::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void Thief::Update()
{
	//set text color to blue
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	m_pStateMachine->Update();
}

void Thief::AddToGoldCarried(const int val)
{
	m_iGoldCarried += val;

	if (m_iGoldCarried < 0) m_iGoldCarried = 0;
}

void Thief::AddToTreasure(const int val)
{
	m_iMoneyInThiefHouse += val;

	if (m_iMoneyInThiefHouse < 0) m_iMoneyInThiefHouse = 0;
}