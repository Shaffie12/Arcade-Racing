#ifndef _WINSTATE_H_
#define _WINSTATE_H_
#include "State.h"
#include "Util.h"
#include<iostream>
#include <sstream>
#include <iomanip>

class WinState : public State
{
public:
	WinState(float& timer);
	void handleInput(sf::Event& e) override;
	void update(const float& dt) override;
	void drawToTexture(Renderer& renderer) override;
	void quit() override;
	int nextState() override;

private:
	sf::Text winText;
	sf::Text timerText;
	sf::Font textFont;
	sf::Color bgFill;
	sf::Color textFill;
	


};

#endif 

