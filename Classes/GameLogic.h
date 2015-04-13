#pragma once

#include <deque>
#include <map>
#include "Player.h"
#include "cocos2d.h"
#include "Bonus.h"

class GameScene;

class GameLogic
{
public:
    GameLogic(cocos2d::CCSize const & gameSize);
    ~GameLogic();
    
    void setOnDeadCallback(GameScene* gs);
    
    int addPlayer();
    void movePlayerLeft(float dt, int id = -1);
    void movePlayerRight(float dt, int id = -1);
    void update(float dt);
    std::deque<Player*>& getPlayers();
	inline std::list<Bonus*>& getBonus() { return _bonus; }
    bool hasGameEnd();
    void nextGame();
    void reset();
    Player* getWinner();
    Player* finalWinner();

    static uint16_t AngleTurn;
    static uint16_t SizePoint;
    static uint16_t Speed;
private:
    
    cocos2d::CCSize _gameSize;
    int _idPlayer;
    std::deque<Player*> _players;
    int _nbPlayerAlive;
    Player* _winner;

	Bonus *	createGoodSpeed();
	Bonus *	createBadSpeed();
	Bonus * createGoodSize();
	Bonus * createBadSize();
	void	createNewBonus();

	bool collision(const MyPoint &, const MyPoint &);

    GameScene* _gs;
    
    void incScore();
    
    static const uint16_t GridX = 20;
    static const uint16_t GridY = 10;

    std::map<int, bool> _grid;
    std::deque<MyPoint> _points;

	static const uint16_t TimeBonus = 10;

	double	_timeBonus;
	typedef Bonus * (GameLogic::*ptr)();
	std::vector<ptr> _randomBonus;
	std::list<Bonus *> _bonus;
};
