#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_ThiefInTheBank,
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

  default:

    return "Not recognized!";
  }
}

#endif