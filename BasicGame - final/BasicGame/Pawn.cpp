#include "Pawn.h"

#include "DisplayConsts.h"
#include "Behaviors.h"

#include "DrawFunction.h"


Pawn::Pawn(Vec2 pos, int health, int maxHP)
	:m_pos(pos)
	, m_health(health)
	, m_equipedArmor(nullptr)
	, m_equipedWeapon(nullptr)
	, m_pBehavior(nullptr)
{
	if (maxHP <= health)
		m_maxHP = m_health;
	else
		m_maxHP = maxHP;
}


Pawn* Pawn::RandAiFactory(Vec2 pos, Pawn* pTarget)
{
	int select = rand() % 3;

	switch (select)
	{
	case 0:
		return AiFactory(pos, pTarget, g_kCircleAi);

	case 1:
		return AiFactory(pos, pTarget, g_kWonderAi);

	case 2:
		return AiFactory(pos, pTarget, g_kChaseAi);

	default:
		break;
	}

	return nullptr;
}
Pawn* Pawn::AiFactory(Vec2 pos, Pawn* pTarget, char type)
{
	Pawn* ai = nullptr;

	if (type == g_kCircleAi)
	{
		ai = new Pawn(pos, 10, 10);
		ai->m_equipedWeapon = Pickup::PickupFac("long");
		ai->m_equipedArmor = Pickup::PickupFac("armor");
		ai->m_pBehavior = new CircleMove();
	}

	if (type == g_kWonderAi)
	{
		ai = new Pawn(pos, 10, 10);
		ai->m_equipedWeapon = Pickup::PickupFac("sword");
		ai->m_pBehavior = new RandomMove();
	}

	if (type == g_kChaseAi)
	{
		ai = new SwitchAI(pTarget, pos, 10, 10, 4, new RandomMove());
		ai->m_pBehavior = new ChaseMove(ai, pTarget);//set the secondary state
		ai->m_equipedWeapon = Pickup::PickupFac("sword");
	}

	return ai;
}

Pawn::~Pawn()
{
	delete m_equipedWeapon;
	delete m_equipedArmor;

	delete m_pBehavior;
}


/////////////////////////
//return the value from equiped item
//if no item return 1
///////////////////////////
int Pawn::GetAttack() const
{
	if (m_equipedWeapon)
		return m_equipedWeapon->GetValue();
	else
		return 1;//default damage
}

//////////////////////////////////
//returns location player wants to go to
//////////////////////////////////////
Vec2 Pawn::GetNewPos()
{
	Vec2 result(0, 0);
	
	if (m_pBehavior)
	{
		Vec2 input = m_pBehavior->Input();
		result = (input + GetLocation());
	}

	return result;
}

//////////////////////////////////
//returns current location
//////////////////////////////////
Vec2 Pawn::GetLocation() const
{
	return m_pos;
}


//////////////////////////////////
//take damage adjusted by armor value
//////////////////////////////////////
void Pawn::TakeDamage(int damage)
{
	if (damage < 0)
		AddHP(damage * -1);

	int dmg = 0;

	if (m_equipedArmor)
		dmg = damage - m_equipedArmor->GetValue();
	else
		dmg = damage;

	if (dmg < 0)
		dmg = 0;

	m_health -= dmg;
}

///////////////////////////////////
//add hp but cannot go over maxHP
///////////////////////////////////
void Pawn::AddHP(int amount)
{
	m_health += amount;

	if (m_health > m_maxHP)
		m_health = m_maxHP;
}

/////////////////////////////////
//check if current hp is < 25% of max
////////////////////////////////////
bool Pawn::LowHealth() const
{
	float hp = static_cast<float>(m_health);
	float maxHp = static_cast<float>(m_maxHP);
	if (hp <= (maxHp * 0.25f))
		return true;
	else
		return false;
}

bool Pawn::IsDead() const
{
	if (m_health <= 0)
		return true;
	else
		return false;
}


/////////////////////////////////////
//User functions
/////////////////////////////////////


User::User(Vec2 pos)
	:Pawn(pos, 25, 35)
{
	m_pBehavior = new UserMove();
}

User::~User()
{
}

Pickup* User::PickUpWeapon(Pickup* item)
{
	if (m_equipedWeapon)//if player has a weapon already
	{
		//save old, set current to new one, return old
		Pickup* temp = m_equipedWeapon;
		m_equipedWeapon = item;
		return temp;
	}
	else
	{
		m_equipedWeapon = item;
		return nullptr;
	}
}

Pickup* User::PickUpArmor(Pickup* item)
{
	if (m_equipedArmor)//if player has a weapon already
	{
		//save old, set current to new one, return old
		Pickup* temp = m_equipedArmor;
		m_equipedArmor = item;
		return temp;
	}
	else
	{
		m_equipedArmor = item;
		return nullptr;
	}
}

////////////////////////
//determins what pawn does with item
//swaps new item with carried one and returns carried 
///////////////////////////
Pickup* User::PickUpItem(Pickup* item)
{
	if (item)
	{
		Pickup* drop = nullptr;

		//if item is hp
		if (item->GetType() == Pickup::Type::k_HP)
			AddHP(item->GetValue());

		if (item->GetType() == Pickup::Type::k_Key)
			m_keys += item->GetValue();

		//if the pickup is a weapon
		if (item->GetType() == Pickup::Type::k_Weapon)
			drop = PickUpWeapon(item);

		//armor
		if (item->GetType() == Pickup::Type::k_Armor)
			drop = PickUpArmor(item);

		return drop;
	}

	return nullptr;
}

////////////////////////////////////////
//returns true if pawn has keys 
//removes keys if true
///////////////////////////////////
bool User::TakeKeys(unsigned int keys)
{
	if (m_keys > 0)
	{
		if (m_keys >= keys)
		{
			m_keys -= keys;
			return true;
		}
	}

	return false;
}

///////////////////////////////////
//print stats reletive to pos
//////////////////////////////////
void User::PrintStats(int x, int y)
{
	Draw print;

	print("HP: ", x, y);
	print("  ", x + 4, y);//clear spots
	print(m_health, x + 4, y);

	print("Keys: ", x + 8, y);
	print("  ", x + 14, y);
	print((int)m_keys, x + 14, y);

	print("Weapon: ", x, y + 1);
	if (m_equipedWeapon)
	{
		print("               ", x + 8, y + 1);
		print(m_equipedWeapon->GetName(), x + 8, y + 1);
		print(" - ");
		print(m_equipedWeapon->GetValue());
	}
	else
		print("No Weapon");

	print("Armor: ", x, y + 2);
	if (m_equipedArmor)
	{
		print("               ", x + 7, y + 2);
		print(m_equipedArmor->GetName(), x + 7, y + 2);
		print(" - ");
		print(m_equipedArmor->GetValue());
	}
	else
		print("No Armor");
}


////////////////////////////////////
//chaseAI functions
///////////////////////////////////////


SwitchAI::SwitchAI(Pawn* pTarget, Vec2 pos, int health, int maxHP, int viewDist, PawnBehavior* defaultState)
	:Pawn(pos, health, maxHP)
	,m_pTarget(pTarget)
	,m_viewDist(viewDist)
	,m_agro(false)
	,m_pDefaultState(defaultState)
{
	m_pBehavior = defaultState;
}

SwitchAI::SwitchAI(Pawn* pTarget, Vec2 pos, int health, int maxHP, int viewDist, PawnBehavior* defaultState, PawnBehavior* agroState)
	:Pawn(pos, health, maxHP)
	, m_pTarget(pTarget)
	, m_viewDist(viewDist)
	, m_agro(false)
	, m_pDefaultState(defaultState)
{
	m_pBehavior = agroState;
}


SwitchAI::~SwitchAI()
{
	delete m_pDefaultState;
}

//////////////////////////////////
//changes input function if target is close
/////////////////////////////////////
Vec2 SwitchAI::GetNewPos()
{
	Vec2 result(0, 0);

	if (m_pTarget && m_viewDist >= GetDistance())//in range
	{
		if (m_pBehavior)
			result = m_pBehavior->Input();

		m_agro = true;
	}
	else//default move
	{
		if (m_pDefaultState)
			result = m_pDefaultState->Input();

		m_agro = false;
	}

	result += GetLocation();
	return result;
}

////////////////////////////////////
//check distancd between target and self
//////////////////////////////////
int SwitchAI::GetDistance()
{
	double x = (GetLocation().m_x - m_pTarget->GetLocation().m_x);
	x *= x;

	double y = (GetLocation().m_y - m_pTarget->GetLocation().m_y);
	y *= y;

	return (int)(std::sqrt(x + y));
}


char SwitchAI::GetDisplay() const
{
	if (m_agro)
		return m_pBehavior->GetDisplay();
	else
		return m_pDefaultState->GetDisplay();
}