#include "player.h"
#include "sgg/graphics.h"
#include "defines.h"
#include <cmath>
void Player::draw()
{

	graphics::Brush br;
	float h = 1.0f * m_highlighted;
	if (this->getTeam())
	{
		SETCOLOR(br.fill_color, 0.5f, h, h);
	}
	else
	{
		SETCOLOR(br.fill_color, h, h,0.5f);
	}

	br.outline_opacity = 1.0f*m_active;
	graphics::drawDisk(m_pos[0], m_pos[1], PLAYER_SIZE * 0.46f, br);

	SETCOLOR(br.fill_color, m_color[0]-0.5 + 0.5f * h, m_color[1] - 0.5f + 0.5f*h, m_color[2] -0.5f + 0.5f * h);
	br.outline_opacity = 0.0f;
	
	br.texture = ASSET_PATH + image;
	graphics::drawRect(m_pos[0], m_pos[1],PLAYER_SIZE,PLAYER_SIZE,br);
	graphics::resetPose();

	br.outline_opacity = 0.0f;
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.7f;
	br.fill_color[2] = 0.0f;
	br.texture = "";
	if (remainingHp / hp < 0.3f) {
		br.fill_color[0] = 0.7f;
		br.fill_color[1] = 0.0f;
		br.fill_color[2] = 0.0f;
	}

	graphics::drawRect(m_pos[0]-((1.0f-remainingHp/hp)*PLAYER_SIZE/2), m_pos[1]-0.8f, PLAYER_SIZE * remainingHp/hp, 0.1f, br);

	br.outline_opacity = 1.0f;
	br.fill_opacity = 0.0f;
	graphics::drawRect(m_pos[0], m_pos[1] - 0.8f, PLAYER_SIZE, 0.1f, br);

}

Player::Player()
{
	SETCOLOR(m_color, 1, 1, 1);

}
bool Player::isOnSameTeam(Player* tgt)
{
	return this->getTeam() == tgt->getTeam();
}

bool Player::contains(float x, float y)
{
	return distance(x, y, m_pos[0], m_pos[1]) < PLAYER_SIZE * 0.4f;
}

bool Player::intersect(Player* tgt)
{
	return distance(m_pos[0], m_pos[1], tgt->m_pos[0], tgt->m_pos[1])<PLAYER_SIZE*2.0f*0.46f;
}

//the attack of archer constists of rolling the dice to try to damage the enemy  and returning an event that prints what he rolled and if he hit or not
std::vector<Event*> Archer::attack(Player* tgt)
{
	int dice = rollDice(tgt);
	
	vector<Event*> actions;
	
	actions.push_back(new PrintActionEvent(CANVAS_WIDTH / 3 + 2, 1, 0.0f, "You rolled " + std::to_string(dice) +result));
	actions.push_back(nullptr);
	return actions;
}
//the attack of soldier consists of rolling the dice and also moving to the closest tile next to the target and returning one event that prints the result of the attack and a movement event that moves the player next to the target
std::vector<Event*>  Soldier::attack(Player* tgt)
{
	int dice = rollDice(tgt);
	vector<Event*> actions;

	actions.push_back(new PrintActionEvent(CANVAS_WIDTH / 3 + 2, 1, 0.0f, "You rolled " + std::to_string(dice) + result));

	int* pos = moveClosest(tgt->getPosX(), tgt->getPosY());

	float posx=PLAYER_SIZE * (0.5f + (int)((tgt->getPosX()+pos[0]) / PLAYER_SIZE));
	float posy = PLAYER_SIZE * (0.5f + (int)((tgt->getPosY()+pos[1]) / PLAYER_SIZE));

	actions.push_back(new PlayerMotionEvent(getPosX(), getPosY(), posx, posy, this,1.0f));
	return actions;
}

//the attack of healer constists of rolling the dice to try to damage the enemy  and returning an event that prints what he rolled and if he hit or not
std::vector<Event*>  Healer::attack(Player* tgt)
{
	int dice = rollDice(tgt);
	
	vector<Event*> actions;

	actions.push_back(new PrintActionEvent(CANVAS_WIDTH / 3 + 2, 1, 0.0f, "You rolled " + std::to_string(dice) + result));
	actions.push_back(nullptr);
	return actions;
}

//the attack of soldier consists of rolling the dice and also moving to the closest tile next to the target and returning one print event and a movement event 
std::vector<Event*>  Cavalyrman::attack(Player* tgt)
{
	int dice = rollDice(tgt);
	
	vector<Event*> actions;

	actions.push_back(new PrintActionEvent(CANVAS_WIDTH / 3 + 2, 1, 0.0f, "You rolled " + std::to_string(dice) + result));

	int* pos = moveClosest(tgt->getPosX(), tgt->getPosY());

	float posx = PLAYER_SIZE * (0.5f + (int)((tgt->getPosX() + pos[0]) / PLAYER_SIZE));
	float posy = PLAYER_SIZE * (0.5f + (int)((tgt->getPosY() + pos[1]) / PLAYER_SIZE));

	actions.push_back(new PlayerMotionEvent(getPosX(), getPosY(), posx, posy, this,1.0f));

	return actions;
}

//initializations of variables for all player classes
Archer::Archer()
{
	motion_range = PLAYER_MOTION_RANGE / 1.35f;
	attack_range = PLAYER_ATTACK_RANGE * 2.0f;
	hp = 10.0f;
	ac = 11.0f;
	maxdamage = 6.0f;
	remainingHp = hp;
}



Soldier::Soldier()
{
	
	motion_range = PLAYER_MOTION_RANGE;
	attack_range = PLAYER_ATTACK_RANGE;
	hp = 16.0f;
	ac = 14.0f;
	maxdamage = 7.0f;
	remainingHp = hp;
}



Healer::Healer()
{
	motion_range = PLAYER_MOTION_RANGE;
	attack_range = PLAYER_ATTACK_RANGE;
	hp = 10.0f;
	ac = 12.0f;
	maxdamage = 2.0f;
	maxheal = 3.0f;
	remainingHp = hp;
	healingabilities = true;
	healingRange = 5.0f;
}

Cavalyrman::Cavalyrman()
{
	motion_range = PLAYER_MOTION_RANGE * 2.0f;
	attack_range = PLAYER_ATTACK_RANGE * 2.0f;
	hp = 12.0f;
	ac = 13.0f;
	maxdamage = 5.0f;
	remainingHp = hp;
}

//heal function
void Healer::heal(Player* pl)
{
	pl->addhp(maxheal);
}

//function that finds which tile next to the enemy is closest to the player
int* Player::moveClosest(float enemy_x, float enemy_y)
{
	int x = -1;
	int y = -1;
	float min = distance(getPosX(), getPosY(), enemy_x - 1, enemy_y - 1);

	if (distance(getPosX(), getPosY(), enemy_x - 1, enemy_y ) <= min) { min = distance(getPosX(), getPosY(), enemy_x - 1, enemy_y); x = -1;y = 0; };
	if (distance(getPosX(), getPosY(), enemy_x - 1, enemy_y + 1) <= min) { min = distance(getPosX(), getPosY(), enemy_x - 1, enemy_y + 1); x = -1;y = 1; };
	if (distance(getPosX(), getPosY(), enemy_x, enemy_y - 1) <= min) { min = distance(getPosX(), getPosY(), enemy_x, enemy_y - 1); x = 0;y = -1; };
	if (distance(getPosX(), getPosY(), enemy_x, enemy_y + 1) <= min) { min = distance(getPosX(), getPosY(), enemy_x, enemy_y + 1); x = 0;y = 1; };
	if (distance(getPosX(), getPosY(), enemy_x + 1, enemy_y - 1) <= min) { min = distance(getPosX(), getPosY(), enemy_x + 1, enemy_y - 1); x = 1;y = -1; };
	if (distance(getPosX(), getPosY(), enemy_x + 1, enemy_y) <= min) { min = distance(getPosX(), getPosY(), enemy_x + 1, enemy_y); x = 1;y = 0; };
	if (distance(getPosX(), getPosY(), enemy_x + 1, enemy_y + 1) <= min) { min = distance(getPosX(), getPosY(), enemy_x + 1, enemy_y + 1); x = 1;y = 1; };
	int pos[2];
	pos[0] = x;
	pos[1] = y;
	return pos;
}

//function that rolls the dice and damages the player if the roll was over their ac 
float Player::rollDice(Player* tgt)
{
	float dice = 1.0f + trunc(RAND0TO1() * 20.0f);
	result = ".You missed";
	hit = false;
	if (dice >= tgt->getAc()) {
		result = ".You hit";
		hit = true;
		if(dice==20.0f)
			tgt->damagePlayer(maxdamage*2);
		else
			tgt->damagePlayer(maxdamage);
	}
	return dice;
}
