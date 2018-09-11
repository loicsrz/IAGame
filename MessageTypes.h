#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_ThiefInTheBank,
  Msg_GetBackToWork,
  Msg_HoldUp,
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case 1:
    
    return "HiHoneyImHome"; 

  case 2:
    
    return "StewReady";

  case 3:

	return "ThiefInTheBank";

  case 4:

	return "GetBackToWork";

  case 5:

	  return "HoldUp";

  default:
    return "Not recognized!";
  }
}

#endif