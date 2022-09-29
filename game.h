#pragma once
#include <list>
#include <vector>
#include "player.h"
#include "event.h"
#include "defines.h"
#include <ctime>

class Game
{
public:
	enum game_state_t{STATE_INIT,STATE_LOADING,STATE_PLAYING,STATE_MENU,STATE_GAME_OVER};
	enum menu_state_t{START,HELP,CHOOSE_MAP,CHOOSE_CHAR};
	enum playing_state_t{STATE_IDLE,STATE_ACTION};
protected:
	static Game* m_instance;

	std::list<Player*> m_players;													//list of players
	std::list<Event*> m_events;														//list of event
	Player* m_active_player = nullptr;												//pointer to the player that is active (selected to act)
	Player* m_previously_active_player = nullptr;									//pointer to the previous player that just acted
	Player* m_target_player = nullptr;												//pointer to the player that the action will done taken on
	float m_init_pos_x;																//position of active player
	float m_init_pos_y;
	bool m_valid_action = false;													//true if the player did a valid action attack or move for example 
	bool team1Round = false;;														//true if it's red team's round
	bool time_for_action = false;													//true if player has been activated and the left button has been released
	//bool death_occured = false;															
	//int round = 0;
	float v;																			
	bool gameover = false;														
	bool team1alive = false ;														//there are still players left on red team 
	bool team2alive = false;														//same for blue team
	bool team1won = false;															//true if red team won
	bool timeToClose = false;														//true if the game is over and the user doesn't wanna play again
	bool playAgain = false;															//true if the player wants to play again and we make another game instance in main
	float time_since_game_over = 0;													//how long the game has been over
	game_state_t m_state = STATE_INIT;
	menu_state_t menu_state = START;
	playing_state_t play_state = STATE_IDLE;
	


	Game() {}
public:
	void draw();
	void update();
	void init();

	~Game();
	
	static void releaseInstance() { if (m_instance) delete m_instance; m_instance = nullptr; }
	static Game* getInstance();

	void processEvents();
	void addEvent(Event * evt);														
	void addPrintEvent(Event* evt);
	void changeRound() { team1Round = !team1Round;  }													//change which team's round it is
	bool eligibleToPlay(Player* pl) { return pl->getTeam() == team1Round; }								//check if a player can play this round
	//int getRound() { return round; }
	void makeActive(Player* pl);																		//make a player active
	bool gameIsOver() { return gameover; }																//return true if the game is over				
	bool quit() { return timeToClose; }																	//returns true if the game is over and the user doen't wanna play again
	bool RestartGame() { return playAgain; }															//returns true if the game is over and the user(s) wanna play another game
};
