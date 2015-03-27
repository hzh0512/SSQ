#include "ssq.h"


const struct GameInfo* s_gf;
struct s_double
{
	ElementType e;
	int index;
	friend bool operator <(const s_double& a,const s_double& b)
	{
		return a.e < b.e || a.index < b.index;
	}
};
int s_enbase_temp,s_mybase_temp;
map<int,int> s_attacking;
map<s_double, int> s_wait;
ret si_0temp,si_1temp;

#define si_myfor(r) si_0temp=s_my((ElementType)r);for (ret::iterator myit=si_0temp.begin();myit!=si_0temp.end();++myit)
#define si_enfor(r) si_1temp=s_en((ElementType)r);for (ret::iterator enit=si_1temp.begin();enit!=si_1temp.end();++enit)

ElementType s_gettype(int index)
{
	si_myfor(ALL)
	{
		if ((*myit)->index==index)
			return (*myit)->type;
	}
	si_enfor(ALL)
	{
		if ((*enit)->index==index)
			return (*enit)->type;
	}
	return (ElementType)-1;
}

int s_find(map<int,int> m,int index,ElementType e=(ElementType)-1)
{
	int i=0;
	map<int,int>::iterator temp;
	for ( temp=m.begin() ;temp!=m.end();++temp)
	{
		if (temp->second==index)
		{
			if (e==-1)
			{
				++i;
			}else if (s_gettype(temp->first)==e){
				++i;
			}
		}
	}
	return i;
}
// to be improved.... different level..
int s_len(int a,int b)
{
	//if (GetState(a)->pos.z!=GetState(b)->pos.z)
	//	return 10*kMaxMapSize;
	return abs(GetState(a)->pos.x-GetState(b)->pos.x)+abs(GetState(a)->pos.y-GetState(b)->pos.y);
}
ret s_my(ElementType e)
{
	ret s_temp;
	for (int i=0;i<s_gf->element_num;++i)
	{
		if (s_gf->elements[i]->team==myteam && e==ALL)
		{
			s_temp.push_back(s_gf->elements[i]);
		}
		if (s_gf->elements[i]->team==myteam && s_gf->elements[i]->type==e)
		{
			s_temp.push_back(s_gf->elements[i]);
		}
	}
	return s_temp;
}
ret s_en(ElementType e)
{
	ret s_temp;
	for (int i=0;i<s_gf->element_num;++i)
	{
		if (s_gf->elements[i]->team==1-myteam && e==ALL)
		{
			s_temp.push_back(s_gf->elements[i]);
		}
		if (s_gf->elements[i]->team==1-myteam && s_gf->elements[i]->type==e)
		{
			s_temp.push_back(s_gf->elements[i]);
		}
	}
	return s_temp;
}
Position s_bestattackplace(int a,int b)
{
	return GetState(b)->pos;
}
bool s_outofrange(int a,int b)
{
	if (s_len(a,b)>kProperty[GetState(a)->type].fire_ranges[kProperty[GetState(b)->type].level])
		return true;
	else 
		return false;
}
void s_update()
{
	s_gf=Info();
	if (s_gf->round==0)
	{
		for (int i=0;i<s_gf->element_num;++i)
		{
			if (s_gf->elements[i]->team==1-myteam && s_gf->elements[i]->type==BASE)
			{
				s_enbase_temp=s_gf->elements[i]->index;
			}
			if (s_gf->elements[i]->team==myteam && s_gf->elements[i]->type==BASE)
			{
				s_mybase_temp=s_gf->elements[i]->index;
			}
		}
	}
again:
	for (map<int,int>::iterator i=s_attacking.begin();i!=s_attacking.end();++i)
	{
		if (!s_isexist(i->first) || !s_isexist(i->second))
		{
			s_attacking.erase(i);
			goto again;
		}
	}

	for (map<int,int>::iterator i=s_attacking.begin();i!=s_attacking.end();++i)
	{
		if (s_outofrange(i->first,i->second))
		{
			ChangeDest(i->first,s_bestattackplace(i->first,i->second));
		}
		AttackUnit(i->first,i->second);
	}
	
}

int s_round()
{
	return s_gf->round;
}

const State* s_enbase()
{
	return GetState(s_enbase_temp);
}
const State* s_mybase()
{
	return GetState(s_mybase_temp);
}

bool s_destvalid(int index,Position p)
{
	return true;
}

void s_attack(ElementType e,int index,int num)
{
	int all=s_find(s_attacking,index,e),att=0,lenmin=2*kMaxMapSize,id;
	s_double temp;
	temp.e = e;
	temp.index = index;
	if (s_wait.find(temp)!=s_wait.end())
		if (s_round() <= s_wait[temp])
			return;
	if (all  >= num)
	{
		return;
	}
	num-=all;
again2:
	id=0;
	lenmin=2*kMaxMapSize;
	si_myfor(e)
	{
		if (s_attacking.find((*myit)->index)==s_attacking.end())
		{
			if (s_len((*myit)->index,index)<lenmin)
			{
				id=(*myit)->index;
				lenmin=s_len((*myit)->index,index);
			}
		}
	}
	if (id!=0)
	{
		ChangeDest(id,s_bestattackplace(id,index));
		AttackUnit(id,index);
		s_attacking[id]=index;
		num--;
		goto again2;
	}
	if (num <= 0)
	{
		return;
	}
	for (int i = 0; i<num ; ++i)
	{
		if (e == -1)
		{
			Produce(FIGHTER);
			s_wait[temp] = s_round() + kProperty[FIGHTER].build_round;
		}
		else
		{
			Produce(e);
			s_wait[temp] = s_round() + kProperty[e].build_round;
		}
			
	}
	
}

void s_attack(int my,int en,int num)
{

}


/*
template<class T> typename vector<T>::iterator s_find(vector<T> v,T value)
{
	typename vector<T>::iterator temp=v.begin();
	int i=0;
	while ( temp!=v.end() && (temp=find(temp,v.end(),value))!=v.end())
	{
		++temp;
		++i;
	}
	return i;
}
*/

bool s_isexist(int index)
{
	si_myfor (ALL)
	{
		if ((*myit)->index==index)
			return true;
	}
	si_enfor (ALL)
	{
		if ((*enit)->index==index)
			return true;
	}
	return false;
}