#ifndef THIEF_OWNED_STATES_H
#define THIEF_OWNED_STATES_H

#include "State.h"


class Thief;
struct Telegram;

class EnterBankAndStealTheNugget : public State<Thief>
{
private:

	EnterBankAndStealTheNugget() {}

	//copy ctor and assignment should be private
	EnterBankAndStealTheNugget(const EnterBankAndStealTheNugget&);
	EnterBankAndStealTheNugget& operator=(const EnterBankAndStealTheNugget&);

public:

	//this is a singleton
	static EnterBankAndStealTheNugget* Instance();

	virtual void Enter(Thief* miner);

	virtual void Execute(Thief* miner);

	virtual void Exit(Thief* miner);

	virtual bool OnMessage(Thief* agent, const Telegram& msg);

};

class GoBackToHouseWithNugget : public State<Thief>
{
private:

	GoBackToHouseWithNugget() {}

	//copy ctor and assignment should be private
	GoBackToHouseWithNugget(const GoBackToHouseWithNugget&);
	GoBackToHouseWithNugget& operator=(const GoBackToHouseWithNugget&);

public:

	//this is a singleton
	static GoBackToHouseWithNugget* Instance();

	virtual void Enter(Thief* miner);

	virtual void Execute(Thief* miner);

	virtual void Exit(Thief* miner);

	virtual bool OnMessage(Thief* agent, const Telegram& msg);

};

class GoToPrisonWithMiner : public State<Thief>
{
private:

	GoToPrisonWithMiner() {}

	//copy ctor and assignment should be private
	GoToPrisonWithMiner(const GoToPrisonWithMiner&);
	GoToPrisonWithMiner& operator=(const GoToPrisonWithMiner&);

public:

	//this is a singleton
	static GoToPrisonWithMiner* Instance();

	virtual void Enter(Thief* miner);

	virtual void Execute(Thief* miner);

	virtual void Exit(Thief* miner);

	virtual bool OnMessage(Thief* agent, const Telegram& msg);

};



#endif

