#include "game.h"
#include <sgg/graphics.h>
#include <random>

void Game::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
	graphics::setFont(ASSET_PATH + std::string("nicefont.ttf"));
	if (m_state == STATE_INIT)
	{
		graphics::drawText(CANVAS_WIDTH / 2.5f, CANVAS_HEIGHT / 2.0f, 1.0f, "   Loading assets...", br);
		m_state = STATE_LOADING;
		return;
	}
	
	if (m_state == STATE_MENU)
	{
		//if the user is ont the starting menu draw the menu backround and print what he needs to press to continue
		if (menu_state == START) {
			br.outline_opacity = 0.0f;
			br.texture = ASSET_PATH + std::string("menu.png");
			SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
			graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

			br.outline_opacity = 1.0f;
			SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
			graphics::drawText(CANVAS_WIDTH / 3.0f, CANVAS_HEIGHT / 2.2f, 1.0f, "Press  Enter  to  start...", br);
			graphics::drawText(CANVAS_WIDTH / 3.0f, CANVAS_HEIGHT / 1.7f, 1.0f, "If you need help press 'H'", br);

		}
		//if the user needs pressed the h button the draw the help menu which includes all characters' stats
		if (menu_state == HELP) {
			br.outline_opacity = 0.0f;
			br.texture = ASSET_PATH + std::string("help_menu.png");
			SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
			graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
			br.outline_opacity = 1.0f;
			SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
			graphics::drawText(CANVAS_WIDTH / 4.0f, 2, 1.0f, "character stats for each character", br);
			SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
			graphics::drawText(CANVAS_WIDTH / 6.0f, 4.0f, 0.6f, "soldier has 16 hp  7 damage  14 ac  a  normal attack and moving range", br);
			graphics::drawText(CANVAS_WIDTH / 6.0f, 6.0f, 0.6f, "archer has 10 hp  6 damage  11 ac  double attack range and smaller moving range", br);
			graphics::drawText(CANVAS_WIDTH / 6.0f, 8.0f, 0.6f, "cavalyrman has 12 hp  5 damage  13 ac   double attack and moving range", br);
			graphics::drawText(CANVAS_WIDTH / 6.0f, 9.5f, 0.55f, "healer has 10 hp  2 damage  12 ac  a  normal attack and moving range and can heal teammates for 3 hp", br);
			graphics::drawText(2.0f, 11.0f, 0.5f, "When you try to attack someone you roll a dice from 1 to 20 and you have to roll a number bigger than their ac to damage them", br);
			graphics::drawText(CANVAS_WIDTH / 3.0f, 14, 1.0f, "Press  Enter  to  play...", br);
			SETCOLOR(br.fill_color, 1.0f, 0.0f, 0.0f);
			graphics::drawText(8.0f, 12.0f, 0.6f, "if you roll a 20 you will hit them for double the damage", br);
			br.outline_opacity = 0.0f;
			SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
			br.texture = ASSET_PATH + std::string("soldier.png");
			graphics::drawRect(4, 4.0f, PLAYER_SIZE, PLAYER_SIZE, br);
			br.texture = ASSET_PATH + std::string("archer.png");
			graphics::drawRect(4, 6.0f, PLAYER_SIZE, PLAYER_SIZE, br);
			br.texture = ASSET_PATH + std::string("cavalyrman.png");
			graphics::drawRect(4, 8.0f, PLAYER_SIZE, PLAYER_SIZE, br);
			br.texture = ASSET_PATH + std::string("healer.png");
			graphics::drawRect(4, 9.5f, PLAYER_SIZE, PLAYER_SIZE, br);
		}
		
	}
	//if the game is over draw the game over menu
	if (m_state == STATE_GAME_OVER) {
		br.outline_opacity = 0.0f;
		SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
		br.texture = ASSET_PATH + std::string("menu.png");
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
		br.outline_opacity = 1.0f;
		SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
		graphics::drawText(CANVAS_WIDTH / 3.0f, CANVAS_HEIGHT / 2.2f, 1.0f, "press  'R'  to  restart the game", br);
		graphics::drawText(CANVAS_WIDTH / 3.0f, CANVAS_HEIGHT / 1.7f, 1.0f, "press 'escape' to close the game", br);
	}

	//if the game is being played then draw the backround , the players and their moving and attack range
	if (m_state == STATE_PLAYING )
	{
		//draw backround
		br.outline_opacity = 0.0f;
		br.texture = ASSET_PATH + std::string("pediomaxis.png");
		SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
		graphics::Brush sq;
		sq.outline_opacity = 0.3f;
		sq.fill_opacity = 0.0f;
		for (int i = 0;i < CANVAS_WIDTH / PLAYER_SIZE;i++)
			for (int j = 0;j < CANVAS_HEIGHT / PLAYER_SIZE;j++)
			{
				float x = (i + 0.5f) * PLAYER_SIZE;
				float y = (j + 0.5f) * PLAYER_SIZE;
				if (play_state == STATE_ACTION && distance(x, y, m_init_pos_x, m_init_pos_y) < m_active_player->getMotionRange())
				{
					SETCOLOR(sq.fill_color, 0.0f, 1.0f, 0.0f);
					sq.fill_opacity = 0.2f;
				}
				else
				{
					sq.fill_opacity = 0.0f;
				}
				graphics::drawRect((i + 0.5f) * PLAYER_SIZE, (j + 0.5f) * PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE, sq);
			}
		graphics::Brush reticle;

		//draw attack range of active player if there is one
		if (play_state == STATE_ACTION)
		{		
			SETCOLOR(reticle.fill_color, 1.0f, 0.0f, 0.0f);
			reticle.fill_opacity = 0.2f;
			reticle.outline_opacity = 0.7f;
			SETCOLOR(reticle.outline_color, 1.0f, 0.0f, 0.0f);
			graphics::drawDisk(m_init_pos_x, m_init_pos_y, m_active_player->getAttackRange(), reticle);
		}
		//draw moving range of active player if there is one
		if (play_state == STATE_ACTION )
		{
			reticle.fill_opacity = 1.0f;
			reticle.outline_width = 2.0f;
			graphics::drawDisk(m_init_pos_x, m_init_pos_y, 0.1f, reticle);
			graphics::drawLine(m_init_pos_x, m_init_pos_y, m_active_player->getPosX(), m_active_player->getPosY(), reticle);
		}
		br.outline_opacity = 0.5f;
		SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);

		graphics::setFont(ASSET_PATH + std::string("nicefont.ttf"));
		//if the game isn't over print whose round it is
		if (team1Round && !gameover)
		{
			graphics::drawText(4, 1, 0.7f, "Red team's round", br);
		}
		if (!team1Round && !gameover)
		{
			graphics::drawText(4, 1, 0.7f, "Blue team's round", br);
		}

		//if the game is over (and m_state is still state_playing) print over the battlefield backround the message game over and which team won (this will appear for about 10 seconds)
		if (gameover) {
			graphics::Brush br;
			br.outline_opacity = 0.0f;
			if (team1won)
			{
				SETCOLOR(br.fill_color, 1.0f, 0.0f, 0.0f);
				graphics::drawText(CANVAS_WIDTH / 4.0f -1.0f , CANVAS_HEIGHT/2, 1.5f, "GAME OVER. RED TEAM WON", br);				
			}
			if (!team1won)
			{				
				SETCOLOR(br.fill_color, 0.0f, 0.0f, 1.0f);
				graphics::drawText(CANVAS_WIDTH / 4.0f -1.0f, CANVAS_HEIGHT / 2, 1.5f, "GAME OVER. BLUE TEAM WON", br);
			}
		}
		//draw players
		for (auto player : m_players)
		{
			player->draw();
		}
		//draw events
		for (auto ev : m_events)
		{
			ev->draw();
		}
	}
}

void Game::update()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	if (m_state == STATE_INIT) {
		return;
	}

	if (m_state == STATE_LOADING) {
		init();
		m_state = STATE_MENU;
		return;
	}
	//if the user presses enter then change the m_state to STATE_PLAYING if he presses 'h' then go to help menu
	if (m_state == STATE_MENU)
	{
		if (graphics::getKeyState(graphics::SCANCODE_RETURN))
		{
			m_state = STATE_PLAYING;
		}
		if (graphics::getKeyState(graphics::SCANCODE_H))
		{
			menu_state = HELP;
		}
		return;
	}

	processEvents();
	//if the game is over go to the game over menu
	if (gameover) {
		time_since_game_over += graphics::getDeltaTime() / 1000.0f;
		if (time_since_game_over > 10.0f)
		{
			if (graphics::getKeyState(graphics::SCANCODE_R))
			{
				playAgain = true;
			}
			if (graphics::getKeyState(graphics::SCANCODE_ESCAPE))
			{
				timeToClose = true;
			}
			m_state = STATE_GAME_OVER;
		}
	}

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);

	mx = PLAYER_SIZE * (0.5f + (int)(mx / PLAYER_SIZE));
	my = PLAYER_SIZE * (0.5f + (int)(my / PLAYER_SIZE));

	


	Player* cur_player = nullptr;
	for (auto player : m_players)
	{
		//check if both teams are alive
		if (player->getTeam() == true)
		{
			team1alive = true;
		}
		
		if (player->getTeam() == false)
		{
			team2alive = true;
		}
		
		//if the mouse is over over a make make that player the cur_player and highlight him
		if (player->contains(mx, my))
		{
			player->setHighlight(true);
			cur_player = player;
		}
		else
			player->setHighlight(false);

		//check if there is any collision between the players if there is then move the player who previously acted 
		if (m_previously_active_player!=nullptr && player->contains(m_previously_active_player->getPosX(), m_previously_active_player->getPosY()) && player!= m_previously_active_player) {
			int* pos = m_previously_active_player->moveClosest(m_previously_active_player->getPosX(), m_previously_active_player->getPosY());
			float posx = PLAYER_SIZE * (0.5f + (int)((m_previously_active_player->getPosX() + pos[0]) / PLAYER_SIZE));
			float posy = PLAYER_SIZE * (0.5f + (int)((m_previously_active_player->getPosY() + pos[1]) / PLAYER_SIZE));
			m_previously_active_player->setPosX(posx);
			m_previously_active_player->setPosY(posy);

		}

	}
	//if all of team red players are dead game is over
	if (team1alive == false) {
		gameover = true;
		team1won = false;
	}
	//if all of team blue players are dead game is over
	if (team2alive == false) {
		gameover = true;
		team1won = true;
	}

	team1alive = false;
	team2alive = false;

	//activate player
	if (ms.button_left_pressed && cur_player && eligibleToPlay(cur_player) && m_active_player==nullptr)  
	{
		makeActive(cur_player);

	}
	if (ms.button_left_released && m_active_player)
	{
		time_for_action = true;
	}

	if (time_for_action= true && m_active_player)
	{
		play_state = STATE_ACTION;
		if (ms.button_left_pressed && cur_player)
		{
			m_target_player = cur_player;

			//if you click on an enemy player the if he is inside the attacking range then call active player's attack and manage the returning events
			if (!m_active_player->isOnSameTeam(m_target_player))
			{
				if (m_target_player != nullptr && distance(m_target_player->getPosX(), m_target_player->getPosY(),
					m_init_pos_x, m_init_pos_y) < m_active_player->getAttackRange() ) 
				{
					std::vector<Event *> acts = m_active_player->attack(m_target_player);
					addPrintEvent(acts[0]);
					if (acts[1]!=nullptr) {
						addEvent(acts[1]);
					}
					acts.clear();
				
					//if target's hp is 0 or belows then delete the player 
					if (m_target_player->getRemainingHp() <= 0)
					{
						
						Player* tgt = m_target_player;
						m_players.remove_if([tgt](Player* pl) {return pl == tgt;});
						delete m_target_player;
						//death_occured = true;
						addPrintEvent(new PrintActionEvent(CANVAS_WIDTH/3+2, 1,0.0f,"Player has been slain"));
						std::string sound = ASSET_PATH + std::string("enemySlain.mp3");
						graphics::playSound(sound, 0.8f);
					}
					m_valid_action = true;
				}
				
			}
			//if you click on a teammate if the active player is the healer then heal the player(if he is inside the healing range) else make the other player active
			else if (m_active_player->isOnSameTeam(m_target_player) && m_active_player!=m_target_player)  
			{
				if (m_active_player->hasheals() &&
					m_target_player != nullptr && distance(m_target_player->getPosX(), m_target_player->getPosY(),	m_init_pos_x, m_init_pos_y) < m_active_player->getHealingRange())
				{
					m_active_player->heal(m_target_player);
					graphics::playSound(ASSET_PATH + std::string("healing.mp3"), 0.8f);
					m_valid_action = true;
					addEvent(new HealEvent(m_target_player->getPosX(), m_target_player->getPosY()));
				}
				else
				{
					makeActive(m_target_player);
				}

			}


		}

		//
		else if (ms.button_left_pressed)
		{
			if (distance(m_init_pos_x, m_init_pos_y, mx, my) < m_active_player->getMotionRange())
			{
				mx = PLAYER_SIZE * (0.5f + (int)(mx / PLAYER_SIZE));
				my = PLAYER_SIZE * (0.5f + (int)(my / PLAYER_SIZE));

				m_active_player->setPosX(mx);
				m_active_player->setPosY(my);

				if (mx != m_init_pos_x || my != m_init_pos_y)
				{
					m_valid_action = true;
				}
			}
		}

		//if the player makes an action change the round and reset the needed variables 
		if (m_valid_action)
		{
			play_state = STATE_IDLE;
			time_for_action = false;
			changeRound();
			m_previously_active_player = m_active_player;
			m_target_player = nullptr;
			m_active_player->setActive(false);
			m_active_player = nullptr;
			m_valid_action = false;
		}
	}

}

//spawn players
void Game::init()
{
	
	for (int i = 0; i < 4;i++)
	{
		for (int j = 0; j < 2;j++)
		{
			float posx;
			float posy;
			posx = CANVAS_WIDTH / 4.0f + 20 * j - 3.0f;
			posy = CANVAS_HEIGHT / 5.0f + 3 * i + 0.75f;

			Player* p;
			if (i == 0){
				p = new Soldier();
				p->setImage("soldier.png");
			}
			else if (i == 1)
			{
				p = new Archer();
				p->setImage("archer.png");
			}
			else if (i == 2)
			{
				p = new Healer();
				p->setImage("healer.png");
			}
			else
			{
				p = new Cavalyrman();
				p->setImage("cavalyrman.png");
			}

			m_players.push_front(p);

			p->setPosX(PLAYER_SIZE * (0.5f + (int)(posx / PLAYER_SIZE)));
			p->setPosY(PLAYER_SIZE * (0.5f + (int)(posy / PLAYER_SIZE)));	
			
			if (j == 0)
			{
				p->setTeam(true);
			}
			else
				p->setTeam(false);
		}
	}
	

	graphics::preloadBitmaps(ASSET_PATH);

	//Randomly decide which team"s turn it is
	srand(time(NULL));
	v = rand() % 10 + 1;

	if (v <= 5) {
		team1Round = false;
	}
	else
	{
		team1Round = true;
	}

}

//destructor
Game::~Game()
{
	for (auto p : m_players)
	{
		delete p;
	}
	m_players.clear();
}

Game* Game::getInstance()
{
	if (!m_instance)
		m_instance = new Game();
	return m_instance;
}

//update the events and delete them when they are not active anymore
void Game::processEvents()
{
	for (auto e : m_events)
	{
		e->update();
	}
	m_events.remove_if([](Event* ev) {return !ev->active();});
}

void Game::addEvent(Event* evt)
{
	m_events.push_front(evt);
}

//add a new print event and set an extra delay on it so it doesn't overwrite the previous events
void Game::addPrintEvent(Event* evt)
{
	float d = 0.0f;
	for (auto e : m_events)
	{
		d += e->getRemainingDuration();
	}
	evt->setDelay(d);
	m_events.push_front(evt);
}

//make player pl active and inactivate all the other players and set the initial position of the player
void Game::makeActive(Player* pl)
{
	m_active_player = pl;
	m_active_player->setActive(true);
	for (auto player : m_players)
	{
		if (player != m_active_player)
			player->setActive(false);
	}
	m_init_pos_x = m_active_player->getPosX();
	m_init_pos_y = m_active_player->getPosY();
}

Game* Game::m_instance = nullptr;