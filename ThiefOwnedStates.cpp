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
		cout << "\n" << GetNameOfEntity(pThief->ID()) << ": " << "Walkin' to the bank";

		pThief->ChangeLocation(bank);
	}
	if (!pThief->Stealing())
	{
		cout << "\n" << GetNameOfEntity(pThief->ID()) << ": EveryBody calm down, it's a robbery !";

		//send a delayed message myself so that I know when to take the stew
		//out of the oven
		Dispatch->DispatchMessage(1.5,  //time delay
			pThief->ID(),           //sender ID
			pThief->ID(),           //receiver ID
			Msg_ThiefInTheBank,        // Type of message
			NO_ADDITIONAL_INFO);

		pThief->SetStealing(true);
	}
}

void EnterBankAndStealTheNugget::Execute(Thief* pThief)
{
	//Now the miner is at the goldmine he digs for gold until he
	//is carrying in excess of MaxNuggets. If he gets thirsty during
	//his digging he packs up work for a while and changes state to
	//gp to the saloon for a whiskey.
	pThief->AddToGoldCarried(1);

	cout << "\n" << GetNameOfEntity(pThief->ID()) << ": " << "Steal a nugget";

	//if enough gold mined, go and put it in the bank
	if (pThief->PocketsFull())
	{
		pThief->GetFSM()->ChangeState(GoBackToHouseWithNugget::Instance());
	}
}

void EnterBankAndStealTheNugget::Exit(Thief* pThief)
{
	cout << "\n" << GetNameOfEntity(pThief->ID()) << ": "
		<< "Leaving the bank";
	pThief->SetStealing(FALSE);
}

bool EnterBankAndStealTheNugget::OnMessage(Thief* pThief, const Telegram& msg)
{
	{
		SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		switch (msg.Msg)
		{
		case Msg_ThiefInTheBank:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pThief->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "\n" << GetNameOfEntity(pThief->ID()) << ": Time to get out of the bank";

			//let hubby know the stew is ready
			Dispatch->DispatchMessage(3,
				pThief->ID(),
				pThief->ID(),
				Msg_GetBackToWork,
				NO_ADDITIONAL_INFO);

			pThief->SetStealing(false);

			pThief->GetFSM()->ChangeState(GoBackToHouseWithNugget::Instance());
		}
		case Msg_HoldUp:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pThief->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "\n" << GetNameOfEntity(pThief->ID()) << ": No, i surrender, don't kill me !";

			pThief->SetStealing(false);

			pThief->GetFSM()->ChangeState(GoToPrisonWithMiner::Instance());
		}
		return true;
	}//end switch
	return false;
}

//------------------------------------------------------------------------methods for GoBackToHouseWithNugget

GoBackToHouseWithNugget* GoBackToHouseWithNugget::Instance()
{
	static GoBackToHouseWithNugget instance;

	return &instance;
}

void GoBackToHouseWithNugget::Enter(Thief* pThief)
{
	//if the miner is not already located at the goldmine, he must
	//change location to the gold mine
	if (pThief->Location() != thief_house)
	{
		cout << "\n" << GetNameOfEntity(pThief->ID()) << ": " << "Walkin' to my house";

		pThief->ChangeLocation(thief_house);
	}
}

