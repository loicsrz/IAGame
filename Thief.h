#pragma once

#include "BaseGameEntity.h"
#include "StateMachine.h"
#include "Locations.h"
#include "ConsoleUtils.h"
#include "ThiefOwnedStates.h"

struct Telegram;

//the amount of nuggets a thief can carry
const int MaxNuggetsLupin = 2;
//the amount of gold a thief must have before he feels his treasure is enought.
const int ComfortLevelLupin = 8;



class Thief : public BaseGameEntity
{
private:
	//an instance of the state machine class.
	StateMachine<Thief>* m_pStateMachine;

	location_type   m_Location;

	int                   m_iGoldCarried;
	int                   m_iMoneyInThiefHouse;

	//is he presently stealing ?
	bool            m_bStealing;

	// is he in prison ?
	bool			m_bInPrison;

public:
	Thief(int id):m_Location(thief_house),
						m_bStealing(false),
						m_bInPrison(false),
						BaseGameEntity(id)
	{
		//set up state machine
		m_pStateMachine = new StateMachine<Thief>(this);

		m_pStateMachine->SetCurrentState(EnterBankAndStealTheNugget::Instance());

	}
	~Thief() { delete m_pStateMachine;}

	void          Update();

	virtual bool  HandleMessage(const Telegram& msg);

	StateMachine<Thief>* GetFSM()const { return m_pStateMachine; }


	//----------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }

	bool          Stealing()const { return m_bStealing; }
	void          SetStealing(bool val) { m_bStealing = val; }

	bool          InPrison()const { return m_bInPrison; }
	void          SetInPrison(bool val) { m_bInPrison = val; }

	int           GoldCarried()const { return m_iGoldCarried; }
	void          SetGoldCarried(int val) { m_iGoldCarried = val; }
	void          AddToGoldCarried(int val);
	bool          PocketsFull()const { return m_iGoldCarried >= MaxNuggetsLupin; }

	int           Treasure()const { return m_iMoneyInThiefHouse; }
	void          SetTreasure(int val) { m_iMoneyInThiefHouse = val; }
	void          AddToTreasure(int val);
};

