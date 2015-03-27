#ifndef SSQ_INCLUDE
#define SSQ_INCLUDE

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
#include "basic.h"

using namespace teamstyle16;
using namespace std;
typedef vector< const State* > ret;
const int myteam=0,ALL=-1;
ret s_en(ElementType e);
ret s_my(ElementType e);
#define s_myfor(r) s_0temp=s_my((ElementType)r);for (ret::iterator myit=s_0temp.begin();myit!=s_0temp.end();++myit)
#define s_enfor(r) s_1temp=s_en((ElementType)r);for (ret::iterator enit=s_1temp.begin();enit!=s_1temp.end();++enit)


void s_update();
int s_round();
const State* s_enbase();
const State* s_enbase();
bool s_destvalid(int index,Position p);
void s_attack(ElementType e,int index,int num);
void s_attack(int my,int en,int num);
bool s_isexist(int index);
//template<class T> typename vector<T>::iterator s_find(vector<T> v,T value);
//int s_find(map<int,int> m,int index,ElementType e);
#endif