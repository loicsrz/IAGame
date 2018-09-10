#pragma once

#include "BaseGameEntity.h"
#include "StateMachine.h"
#include "Locations.h"
#include "ConsoleUtils.h"



class Thief : public BaseGameEntity
{
private:
	//an instance of the state machine class.
	StateMachine<Thief>* m_pStateMachine;

	location_type   m_Location;

	//is she presently stealing ?
	bool            m_bStealing;
public:
	Thief(int id):m_Location(thief_house),
						m_bStealing(false),
						BaseGameEntity(id)
	{
		//set up state machine
		m_pStateMachine = new StateMachine<Thief>(this);

		//m_pStateMachine->SetCurrentState(GoHomeAndSleepTilRested::Instance());

	}
	~Thief() { delete m_pStateMachine;}

	//this must be implemented
	void          Update();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);

	StateMachine<Thief>* GetFSM()const { return m_pStateMachine; }


	//----------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }

	bool          Cooking()const { return m_bStealing; }
	void          SetCooking(bool val) { m_bStealing = val; }
};

