#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <time.h>
#include <cstdlib>

#include "Game.h"

Game *singleton;

Game::Game(){
    srand(time(NULL));
	players = new std::vector<Player*>;
	numPlayers = 2;
	for(int i = 0; i < numPlayers; i++){
		if(i == 0){
			players->push_back(new Player(-1.5, 1, 0.01f, 1, 0, 0, 0, 0));
		}
		if(i == 1){
			players->push_back(new Player(1.5, 1, 0.01f, 0, 1, 0, 0, 0));
		}
		if(i == 2){
			players->push_back(new Player(-1.5, -1, 0.01f, 0, 0, 1, 0, 0));
		}
		if(i == 3){
			players->push_back(new Player(1.5, -1, 0.01f, 1, 1, 0, 0, 0));
		}
	}
	for(int i = 4 - numPlayers; i < 4; i++){
		if(i == 0){
			players->push_back(new Ai(-1.5, 1, 0.01f, 1, 0, 0, 0, 0));
		}
		if(i == 1){
			players->push_back(new Ai(1.5, 1, 0.01f, 0, 1, 0, 0, 0));
		}
		if(i == 2){
			players->push_back(new Ai(-1.5, -1, 0.01f, 0, 0, 1, 0, 0));
		}
		if(i == 3){
			players->push_back(new Ai(1.5, -1, 0.01f, 1, 1, 0, 0, 0));
		}
	}
	
	
	
	
	/*
	for(int i = 0; i < numPlayers; i++){
		players->push_back(new Player(-1.5+i*3, 1, 0.01f, 1, 0, 0, 0, 0));
	}
	for(int i = 0; i < 4-numPlayers; i++){
		players->puch_back(new Ai(-1.5+i*3
	}
	*/
	/*
	test = new Player(1.0f, 1.0f, 0.01f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	player2 = new Player(-1.0f, -1.0f, 0.01f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	bitch = new Ai(0, 0, 0.01f, 1, 1, 0, 0, 0);
	*/
	orbs = new std::vector<Circle*>;
	

    setRate(1);
	singleton = this;
    start();
}

void timer(int id){
    // This will get called every 16 milliseconds after
    // you call it once
	
    // If you want to manipulate the app in here
    // do it through the singleton pointer
	
	singleton->createOrbs();
	
    glutTimerFunc(200, timer, id);
}

void Game::action(){

	
	/*
	test->playerMove();
	player2->playerMove();
	bitch->playerMove();
	*/

	for(std::vector<Player*>::iterator it = players->begin(); it < players->end(); it++){
		(*it)->playerMove();
		for(std::vector<Player*>::iterator tit = 1 + it; tit < players->end(); tit++){
			if((*it)->getCircle()->contains((*tit)->getCircle()) && (*it)->isDead != true){
				if ((*tit)->getCircle()->getRad() > (*it)->getCircle()->getRad()){
					(*tit)->getCircle()->setRad((*tit)->getCircle()->getRad() + (*it)->getCircle()->getRad());
					(*it)->isDead = true;
					(*it)->getCircle()->setRad(0);
					break;
				} else {
					(*it)->getCircle()->setRad((*it)->getCircle()->getRad() + (*tit)->getCircle()->getRad());
					(*tit)->isDead = true;
					(*tit)->getCircle()->setRad(0);
					break;
				}
			}
		}
	}
	
	for(std::vector<Circle*>::iterator it = orbs->begin(); it < orbs->end(); ++it) {
		for(std::vector<Player*>::iterator tit = players->begin(); tit < players->end(); tit++){
			if((*it)->contains((*tit)->getCircle())){
				(*tit)->getCircle()->setRad((*tit)->getCircle()->getRad() + (*it)->getRad()/3);
				//delete *it;
				orbs->erase(it);
				goto beef;
			}
		}
	}	
	beef:;
	
		/*
	for(std::vector<Circle*>::iterator it = orbs->begin(); it != orbs->end(); ++it) {
		if((*it)->contains(test->getCircle())) {
			//std::cout << "we insidie" << std::endl;
			test->getCircle()->setRad(test->getCircle()->getRad() + (*it)->getRad()/3);
			//delete orbs->at(*it);
			orbs->erase(it);
			break;
		}
		else if((*it)->contains(player2->getCircle())) {
			//std::cout << "we insidie" << std::endl;
			player2->getCircle()->setRad(player2->getCircle()->getRad() + (*it)->getRad()/3);
			//delete orbs->at(*it);
			orbs->erase(it);
			break;
		}
	}
	*/
	/*
	if(test->getCircle()->contains(player2->getCircle()) && !oneDead)
	{
		player2->getCircle()->setRad(player2->getCircle()->getRad() + test->getCircle()->getRad());
		test->getCircle()->setRad(0);
		oneDead = true;
	}
	if(player2->getCircle()->contains(test->getCircle()) && !twoDead) {
		test->getCircle()->setRad(test->getCircle()->getRad() + player2->getCircle()->getRad());
		player2->getCircle()->setRad(0);
		twoDead = true;
	}
	*/
}

void Game::draw() const {
	for(std::vector<Player*>::iterator it = players->begin(); it < players->end(); it++){
		if(!(*it)->isDead){
			(*it)->draw();
		}
	}
	
	/*
	if(!oneDead)
		test->draw();
	if(!twoDead)
		player2->draw();
	bitch->draw();
	*/
	for(std::vector<Circle*>::iterator it = orbs->begin(); it < orbs->end(); ++it) {
		(*it)->draw();
	}
	
	
}

void Game::handleKeyDown(unsigned char key, float x, float y){

    if (key == ' '){
		timer(0);
    }
    if (key == 'w'){
		(players->at(0))->moveUp();
		if(numPlayers > 0){
			(players->at(3))->moveUp();
			if (numPlayers > 1){
				(players->at(2))->moveUp();
				if(numPlayers > 2){
					(players->at(1))->moveUp();
				}
			}
		}
		//*(players->at(0))->moveUp();
		return;
    }
    if (key == 's'){
		(players->at(0))->moveDown();
		if(numPlayers > 0){
			(players->at(3))->moveDown();
			if (numPlayers > 1){
				(players->at(2))->moveDown();
				if(numPlayers > 2){
					(players->at(1))->moveDown();
				}
			}
		}
		return;
    }
	if (key == 'd'){
		(players->at(0))->moveRight();
		if(numPlayers > 0){
			(players->at(3))->moveRight();
			if (numPlayers > 1){
				(players->at(2))->moveRight();
				if(numPlayers > 2){
					(players->at(1))->moveRight();
				}
			}
		}
		return;
    }
    if (key == 'a'){
		(players->at(0))->moveLeft();
		if(numPlayers > 0){
			(players->at(3))->moveLeft();
			if (numPlayers > 1){
				(players->at(2))->moveLeft();
				if(numPlayers > 2){
					(players->at(1))->moveLeft();
				}
			}
		}
		return;
    }
}

void Game::handleSpecialKeyDown(int key, float x, float y) {
	//if(numPlayers >= 2){
	if (key == GLUT_KEY_UP){
		(players->at(1))->moveUp();
		if(numPlayers > 0){
			(players->at(3))->moveUp();
			if (numPlayers > 1){
				(players->at(2))->moveUp();
				if(numPlayers > 2){
					(players->at(1))->moveUp();
				}
			}
		}
		return;
	}
	if (key == GLUT_KEY_DOWN){
		(players->at(1))->moveDown();
		if(numPlayers > 0){
			(players->at(3))->moveDown();
			if (numPlayers > 1){
				(players->at(2))->moveDown();
				if(numPlayers > 2){
					(players->at(1))->moveDown();
				}
			}
		}
		return;
	}
	if (key == GLUT_KEY_RIGHT){
		(players->at(1))->moveRight();
		if(numPlayers > 0){
			(players->at(3))->moveRight();
			if (numPlayers > 1){
				(players->at(2))->moveRight();
				if(numPlayers > 2){
					(players->at(1))->moveRight();
				}
			}
		}
		return;
	}
	if (key == GLUT_KEY_LEFT){
		(players->at(1))->moveLeft();
		if(numPlayers > 0){
			(players->at(3))->moveLeft();
			if (numPlayers > 1){
				(players->at(2))->moveLeft();
				if(numPlayers > 2){
					(players->at(1))->moveLeft();
				}
			}
		}
		return;
	}
	
}

void Game::createOrbs() {
	try{
		//if(orbs->size() < 2)
		//{
			float randX = (((float)rand() / (float) RAND_MAX) * 3.5) - 2;
			float randY = (((float)rand() / (float) RAND_MAX) * 2.0) - 1;
			//std::cout << "Orb created at (" << randX << ", " << randY << ")." << std::endl;
			Circle *temp = new Circle(randX, randY);
			orbs->push_back(temp);
		//}
	}
	catch(int e) {
		std::cout << e << std::endl;
	}	
}

Game::~Game(){
	delete orbs;
	delete players;
    stop();
}
