#include "ThiefOwnedStates.h"
#include "Locations.h"
#include "Thief.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//------------------------------------------------------------------------methods for EnterBankAndStealTheNugget

EnterBankAndStealTheNugget* EnterBankAndStealTheNugget::Instance()
{
	static EnterBankAndStealTheNugget instance;

	return &instance;
}

void EnterBankAndStealTheNugget::Enter(Thief* pThief)
{
	//if the miner is not already located at the goldmine, he must
	//change location to the gold mine
	if (pThief->Location() != bank)
	{
		cout << "\n" << GetNameOfEntity(pThief->ID()) << ": " << "Walkin' to the goldmine";

		pThief->ChangeLocation(bank);
	}
}

void EnterBankAndStealTheNugget::Execute(Thief* pThief)
{
	//Now the miner is at the goldmine he digs for gold until he
	//is carrying in excess of MaxNuggets. If he gets thirsty during
	//his digging he packs up work for a while and changes state to
	//gp to the saloon for a whiskey.
	pThief->AddToGoldCarried(1);
	pThief->SetStealing(TRUE);

	cout << "\n" << GetNameOfEntity(pThief->ID()) << ": " << "Pickin' up a nugget";

	//if enough gold mined, go and put it in the bank
	if (pThief->PocketsFull())
	{
		pThief->GetFSM()->ChangeState(GoBackToHouseWithNugget::Instance());
	}
}

void EnterBankAndStealTheNugget::Exit(Thief* pThief)
{
	cout << "\n" << GetNameOfEntity(pThief->ID()) << ": "
		<< "Ah'm leavin' the goldmine with mah pockets full o' sweet gold";
	pThief->SetStealing(FALSE);
}

bool EnterBankAndStealTheNugget::OnMessage(Thief* pThief, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}

//------------------------------------------------------------------------methods for GoBackToHouseWithNugget

GoBackToHouseWithNugget* GoBackToHouseWithNugget::Instance()
{
	static GoBackToHouseWithNugget instance;

	return &instance;
}