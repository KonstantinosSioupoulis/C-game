#pragma once
#include <string>
using namespace std;
#include "defines.h"

class Event
{
protected:
	float m_pos_x;
	float m_pos_y;

	float m_duration = 1.0f;													//duration of the event
	float m_delay = 0.0f;														//start event after a certain delay
	float m_elapsed_time = 0.0f;												//how long has the event been active
	float m_elapsed_delay = 0.0f;												//how long has the event been waiting to start


	bool m_active = true;
public:
	virtual void draw() {};																	//function that draws the event
	virtual void update();																	//function that updates the event
	Event(float x = 0.0f, float y = 0.0f, float dur = 2.0f, float del = 0.0f);				
	virtual ~Event() {};
	bool active() {	return m_active;}														//return if the event is still active or it's finished
	void disable() { m_active = false; }													
	bool waiting();																		//returns true if the event hasn't/shouln't start yet
	float getRemainingDuration(){ return m_duration-m_elapsed_time; }					//return how much time the event has left
	void setDelay(float d) { m_delay = d; }											//set a delay for the event
	//virtual int getEventRound() {};



};

class HealEvent : public Event
{
	float m_orientation;
	float m_scale;
public:
	void draw() override;
	HealEvent(float x, float y);
};
//event that slowly moves a player to a position
class PlayerMotionEvent : public Event
{
	class Player* m_player;																	//the player who will move
	float m_start_x;
	float m_start_y;																		//position where the play will start and position where he should end
	float m_stop_x;
	float m_stop_y;
public:
	void update() override;
	PlayerMotionEvent(float start_x, float start_y, float end_x, float end_y, class Player* p,float d);
};

//event that prints a string on the screen mostly used 
class PrintActionEvent : public Event
{
	string  m_string;																	//string that we want printed
public:
	void draw() override;
	PrintActionEvent(float x, float y,float d,string s);
	
};

