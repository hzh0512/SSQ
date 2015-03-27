#include "basic.h"
#include "ssq.h"
// Remove this line if you konw C++, and don't want a dirty namespace
using namespace teamstyle16;
ret s_0temp,s_1temp;

const char * GetTeamName()
{
    return "ssq";  // Name of your team
}

void AIMain()
{
	s_update();
	s_attack(FIGHTER,s_enbase()->index,3);

}