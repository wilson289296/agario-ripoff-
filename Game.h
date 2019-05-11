#ifndef Game_hpp
#define Game_hpp

#include "AppComponent.h"
#include "AnimatedRect.h"
#include "Timer.h"
#include "Player.h"
#include "Circle.h"
#include "Ai.h"
#include <vector>

class Game: public AppComponent, private Timer{

public:
	
	std::vector<Circle*> *orbs;

	Player *test;
	Player *player2;
	Ai *bitch;
	int eaten;
	
	bool oneDead;
	bool twoDead;

    Game();
    
    void draw() const ;
    void handleKeyDown(unsigned char, float, float);
	void handleSpecialKeyDown(int, float, float);
	
	//void handleKeyUp(unsigned char, float, float);
	void createOrbs();
    
    void action();
	
	friend void timer(int);

    ~Game();

};

#endif 
