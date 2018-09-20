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
	//if the thief is not in the bank, he moves to the bank.
	if (pThief->Location() != bank)
	{
		cout << "\n" << GetNameOfEntity(pThief->ID()) << ": " << "Walkin' to the bank";

		pThief->ChangeLocation(bank);
	}
	if (!pThief->Stealing())
	{
		cout << "\n" << GetNameOfEntity(pThief->ID()) << ": EveryBody calm down, it's a heist !";

		//send a delayed message myself so that I know when to get ou of the bank.
		Dispatch->DispatchMessage(1,  //time delay
			pThief->ID(),           //sender ID
			pThief->ID(),           //receiver ID
			Msg_ThiefInTheBank,        // Type of message
			NO_ADDITIONAL_INFO);

		pThief->SetStealing(true);
	}
}

void EnterBankAndStealTheNugget::Execute(Thief* pThief)
{
	//Now the thief is in the bank and he stealing gold nuggets.
	pThief->AddToGoldCarried(1);

	cout << "\n" << GetNameOfEntity(pThief->ID()) << ": " << "Steal a nugget";

	//if the thief is full of gold nuggets, he go back to his house.
	if (pThief->PocketsFull())
	{
		pThief->GetFSM()->ChangeState(GoBackToHouseWithNugget::Instance());
	}
}

void EnterBankAndStealTheNugget::Exit(Thief* pThief)
{
	cout << "\n" << GetNameOfEntity(pThief->ID()) << ": "
		<< "Leaving the bank";
	pThief->SetStealing(false);
}

bool EnterBankAndStealTheNugget::OnMessage(Thief* pThief, const Telegram& msg)
{
	{
		SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		switch (msg.Msg)
		{
		// When he receives this message, he go back to his house.
		case Msg_ThiefInTheBank:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pThief->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			cout << "\n" << GetNameOfEntity(pThief->ID()) << ": Time to get out of the bank";

			pThief->SetStealing(false);

			pThief->GetFSM()->ChangeState(GoBackToHouseWithNugget::Instance());
		}
		// When he receives this message, it means that bob is in the bank and 
		// he surrenders
		case Msg_HoldUp:
		{
			cout << "\nMessage received by " << GetNameOfEntity(pThief->ID()) <<
				" at time: " << Clock->GetCurrentTime();

			SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			cout << "\n" << GetNameOfEntity(pThief->ID()) << ": No, i surrender, don't kill me !";

			pThief->SetStealing(false);

			pThief->GetFSM()->ChangeState(GoToPrisonWithMiner::Instance());
		}
		return true;
		}//end switch
		return false;
	}
}

//------------------------------------------------------------------------methods for GoBackToHouseWithNugget

GoBackToHouseWithNugget* GoBackToHouseWithNugget::Instance()
{
	static GoBackToHouseWithNugget instance;

	return &instance;
}

void GoBackToHouseWithNugget::Enter(Thief* pThief)
{
	//if the thief is not already located at his house, he must
	//change location to his house
	if (pThief->Location() != thief_house)
	{
		cout << "\n" << GetNameOfEntity(pThief->ID()) << ": " << "Yeepee Yo yeepee yeah goin' home with pockets full of gold !";

		pThief->ChangeLocation(thief_house);
	}
}

void GoBackToHouseWithNugget::Execute(Thief* pThief)
{
	//Now the Thief is at his home and he stores the gold he stole 
	//and looks to his treasure to determine if he stays at home or
	//go back to the bank to steal other gold nuggets
	pThief->AddToTreasure(pThief->GoldCarried());
	pThief->SetGoldCarried(0);

	cout << "\n" << GetNameOfEntity(pThief->ID()) << ": " << "Store his stolen nuggets";

	if (pThief->Treasure() < ComfortLevelLupin) 
	{
		pThief->GetFSM()->ChangeState(EnterBankAndStealTheNugget::Instance());
	}

}

void GoBackToHouseWithNugget::Exit(Thief* pThief)
{
	cout << "\n" << GetNameOfEntity(pThief->ID()) << ": "
		<< "Leaving his house";
}

bool GoBackToHouseWithNugget::OnMessage(Thief* pThief, const Telegram& msg)
{
	return false;
}

//------------------------------------------------------------------------methods for GoToPrisonWithMiner

GoToPrisonWithMiner* GoToPrisonWithMiner::Instance()
{
	static GoToPrisonWithMiner instance;

	return &instance;
}

void GoToPrisonWithMiner::Enter(Thief* pThief)
{
	//if the thief is not already in prison, he goes to the prison.
	if (pThief->Location() != prison)
	{
		cout << "\n" << GetNameOfEntity(pThief->ID()) << ": " << "Walkin' to the prison with Bob";

		pThief->ChangeLocation(prison);

	}
	if (!pThief->InPrison())
	{
		// Send a message to myself to know when i can be free.
		Dispatch->DispatchMessage(5,  //time delay
			pThief->ID(),           //sender ID
			pThief->ID(),           //receiver ID
			Msg_FreeToGo,        // Type of message
			NO_ADDITIONAL_INFO);

		pThief->SetInPrison(true);
	}
}

void GoToPrisonWithMiner::Execute(Thief* pThief)
{
	//Now the thief is in prison. He will be free in a certain period of time when he will receive a message

	cout << "\n" << GetNameOfEntity(pThief->ID()) << ": " << "i'm in prison now... what a shame";

}

void GoToPrisonWithMiner::Exit(Thief* pThief)
{

}

bool GoToPrisonWithMiner::OnMessage(Thief* pThief, const Telegram& msg)
{
	{
		SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		switch (msg.Msg)
		{
			// When he receives this message, he go back to his house.
			case Msg_FreeToGo:
			{
				cout << "\nMessage received by " << GetNameOfEntity(pThief->ID()) <<
					" at time: " << Clock->GetCurrentTime();

				SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << "\n" << GetNameOfEntity(pThief->ID()) << ": Yeah ! Free to go !";

				pThief->SetInPrison(false);

				pThief->GetFSM()->ChangeState(GoBackToHouseWithNugget::Instance());
			}
			return true;
		}
		return false;
	}
}