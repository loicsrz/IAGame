#ifndef THIEF_OWNED_STATES_H
#define THIEF_OWNED_STATES_H

#include "State.h"


class Thief;
struct Telegram;

//------------------------------------------------------------------------
//
//  In this state the thief will walk to the bank (location) and steal a nugget
//  of gold. If the thief already has his pockets full of nugget of gold
//  he'll change state to GoBackToHouseWithNugget. If the miner enters the bank
//  at the moment he is stealing gold, he'll get caught and sent to prison and 
//  will pass in the state GoToPrisonWithMiner.
//------------------------------------------------------------------------
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

//------------------------------------------------------------------------
//
//  In this state the thief will walk to his house (location) in order to deposit the gold he
//  stole into his treasure. If he estimates that he stole enough gold nuggets,
//  he will stay in this state until the end. But if he needs more gold nuggets,
//  he'll change his state to EnterBankAndStealTheNugget in order to get more gold
//------------------------------------------------------------------------
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

//------------------------------------------------------------------------
//
//  In this state the thief be brought to the location prison by the miner.
//  Later, the thief will evade and change his state to GoBackHouseWithNugget
//  in order to go back home and restart his activity
//------------------------------------------------------------------------
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

