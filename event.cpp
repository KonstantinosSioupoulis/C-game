#include "event.h"
#include "sgg/graphics.h"
#include "defines.h"
#include "player.h"

void Event::update()
{
	if (!m_active)
		return;

	if (waiting())
	{
		m_elapsed_delay += graphics::getDeltaTime() / 1000.0f;
		return;
	}
	m_elapsed_time += graphics::getDeltaTime() / 1000.0f;
	if (m_elapsed_time > m_duration)
	{
		m_active = false;
	}

}

Event::Event(float x, float y, float dur, float del)
	:m_pos_x(x),m_pos_y(y),m_duration(dur),m_delay(del)
{
}

bool Event::waiting()
{
	return m_elapsed_delay < m_delay;
}

void HealEvent::draw()
{
	
	graphics::Brush br;

	float s = m_elapsed_time / m_duration;

	br.texture = ASSET_PATH + std::string("plus.png");
	br.outline_opacity = 0.0f;
	br.fill_opacity = 1.3f*(1.0f - s);
	graphics::setScale(m_scale + s/2.0f, m_scale + s/2.0f);
	//graphics::setOrientation(m_orientation + s*20.0f);
	
	graphics::drawRect(m_pos_x, m_pos_y, PLAYER_SIZE/3.0f, PLAYER_SIZE/3.0f, br);
	graphics::drawRect(m_pos_x-0.5f, m_pos_y-0.5f, PLAYER_SIZE / 3.0f, PLAYER_SIZE / 3.0f, br);
	graphics::drawRect(m_pos_x+0.5f, m_pos_y+0.5f, PLAYER_SIZE / 3.0f, PLAYER_SIZE / 3.0f, br);
	graphics::drawRect(m_pos_x-0.5f, m_pos_y+0.5f, PLAYER_SIZE / 3.0f, PLAYER_SIZE / 3.0f, br);
	graphics::drawRect(m_pos_x+0.5f, m_pos_y-0.5f, PLAYER_SIZE / 3.0f, PLAYER_SIZE / 3.0f, br);


	graphics::resetPose();
}

HealEvent::HealEvent(float x, float y)
	:Event(x,y,2.0f,0.0f)
{
	m_orientation = RAND0TO1() * 180.0f - 90.0f;
	m_scale = 0.8f + RAND0TO1() * 0.4f;
}

void PlayerMotionEvent::update()
{
	Event::update();
	if (!m_player)
	{
		m_active = false;
		return;
	}

	if (waiting())
		return;

	float s = m_elapsed_time / m_duration;
	float x= m_start_x * (1.0f-s) + m_stop_x * s ;
	float y= m_start_y * (1.0f-s) + m_stop_y * s ;

	m_player->setPosX(x);
	m_player->setPosY(y);
}

PlayerMotionEvent::PlayerMotionEvent(float start_x, float start_y, float end_x, float end_y, Player* p,float dur)
	:Event(0.0f, 0.0f, dur, 0.0f), m_start_x(start_x), m_stop_x(end_x), m_start_y(start_y), m_stop_y(end_y),
	m_player(p)
{

}

void PrintActionEvent::draw()
{
	if (!m_active)
		return;

	if (waiting())
	{
		m_elapsed_delay += graphics::getDeltaTime() / 1000.0f;
		return;
	}
	m_elapsed_time += graphics::getDeltaTime() / 1000.0f;
	if (m_elapsed_time > m_duration)
	{
		m_active = false;
	}

	float s = m_elapsed_time / m_duration;
	
	graphics::Brush br;
	br.outline_opacity = 0.5f;
	SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);

	graphics::setFont(ASSET_PATH + std::string("nicefont.ttf"));
	graphics::drawText(m_pos_x,  m_pos_y, 0.7f, m_string, br);
	
}

PrintActionEvent::PrintActionEvent(float canvas_x,float canvas_y,float d, string s)
	:Event(canvas_x,canvas_y,2.0f,d), m_string(s)//,round(r)
{

//	m_scale = 0.8f + RAND0TO1() * 0.4f;

}
