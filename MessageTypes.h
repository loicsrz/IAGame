#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_ThiefInTheBank,
  Msg_HoldUp,
  Msg_FreeToGo,
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case 0:
	{
	  return "HiHoneyImHome";
	}

  case 1:
	{
	  return "StewReady";
	}
    
  case 2:
	{
	  return "ThiefInTheBank";
	}
	
  case 3:
	{
	  return "HoldUp";
	}
	
  case 4:
	{
	  return "FreeToGo";
	}
  default:
    return "Not recognized!";
  }
}

#endif