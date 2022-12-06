#ifndef UI_H_
#define UI_H_
#include "Drawable.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Track.h"
#include <string>

class UI : public Drawable
{
	public:
		UI();
		void drawElement(sf::RenderTarget& w);
		void update(float dt) override;
		void getRaceTimer(float timer);
		void getTrackSpeed(float Trackspeed);
		void getCurrentLap(int lapNumber);


	private:
		std::stringstream ss;
		sf::Font textFont;
		sf::Text speedText;
		sf::Text lapText;
		sf::Text timerText;

		float speed;
		int lap;
		int timer;

};


#endif 