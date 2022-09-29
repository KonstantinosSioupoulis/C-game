#pragma once
#include "event.h"
#include <vector>
//#include "game.h"
class Player
{
protected:
	float motion_range=0;				//range where the player can move
	float attack_range=0;				//range where the player can attack
	float ac=0;							//number enemies have to roll over to damage this player
	float hp=0;							//player's starting health
	float maxdamage=0;					//the damage of this player
	float remainingHp=0;				//player's health left
	
	float m_pos[2] = { 0,0 };						//player's position
	float m_color[3];

	std::string image;					//player's image has a string of the name of the asset 
	bool m_highlighted = false;			//true when the mouse is over the player 
	bool m_active = false;				//true if he is chosen to act
	bool isOnTeam1 = false;				//player's team
	bool healingabilities = false;		//true only for the healer
public:
	void draw();
	Player();
	virtual std::vector<Event*> attack(Player* tgt) { std::vector<Event*> l; return l; };			//attack function different virtual cause it is different for each type of character
	virtual void heal(Player* pl) {};																//heal function only implemented in healer class
	void setImage(std::string s) { image = s; }														//set the image of the player
	float getAc() { return ac; }																	
	float setAc(float a) { ac = a; }
	float getHp() { return hp; }
	void setHp(float h) { hp = h; }
	float getRemainingHp() { return remainingHp; }
	void damagePlayer(float d) { remainingHp -= d; }												//if the attacker rolls over the player's ac damage the player
	void addhp(float d) { if (remainingHp + d <= hp) remainingHp += d; else remainingHp = hp; }		//heal the player
	float getPosX() { return m_pos[0]; }
	float getPosY() { return m_pos[1]; }
	void setPosX(float x) { m_pos[0] = x; }
	void setPosY(float y) { m_pos[1] = y; }															//set and get functions for ac,hp,damage, positions x y team
	void setTeam(bool t) { isOnTeam1 = t; }
	bool getTeam() { return isOnTeam1; }
	void setHighlight(bool h) { m_highlighted = h; }
	void setActive(bool a) { m_active = a; }
	float getMotionRange() { return motion_range; }
	float getAttackRange() { return attack_range; }
	bool hasheals() { return healingabilities; }												//return if thr player is a healer
	
	bool isOnSameTeam(Player* tgt);																//return if a player is on the same team
	bool contains(float x, float y);															//return if the player is inside a position
	bool hit=false;
	std::string result;																		//string containing "You hit" or "You missed" depending on the roll
	float rollDice(Player* tgt);															//roll a dice and damage the target if you roll over their ac
	virtual float getHealingRange() { return 0.0f; }										//virtul function return the healing range of the player implemented only by the healer class
	bool intersect(Player* tgt);															//return if there is collision between two players
	int * moveClosest(float enemy_x, float enemy_y);										//move to the closest tile when  soldier or cavalyrman attacks


};

class Archer : public Player
{
public:
	std::vector<Event *> attack(Player * tgt) override;
	Archer();
};

class Soldier : public Player
{
public:
	std::vector<Event*> attack(Player* tgt) override;
	Soldier();
};

class Healer : public Player
{
	float maxheal;
public:
	std::vector<Event*> attack(Player* tgt) override;
	Healer();
	void heal(Player* pl);
	float healingRange;
	float getHealingRange() { return healingRange; }
};

class Cavalyrman : public Player
{
public:
	std::vector<Event*> attack(Player* tgt) override;
	Cavalyrman();
};