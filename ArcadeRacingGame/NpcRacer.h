#ifndef _NPC_RACER_H_
#define _NPC_RACER_H_
#include "Racer.h"
#include<algorithm>

class NpcRacer: public Racer
{
public:
	NpcRacer(Track& t, sf::Vector2f startPos, sf::Color color =sf::Color::White);
	void update(const float& dt) override;
	const float distanceFromCenter() const;
	friend bool operator<(const NpcRacer& a, const NpcRacer& b) { return a.trackPos > b.trackPos; }
	
private:
	sf::Clock clock;
	float moveInterval;
	float nextOffset = 0;
	float baseSpeed;
	float currentSpeed;
	sf::Color m_color;
	void recolorSprite();
	void scale();
	void position(const float& dt);
	int trackPos;
	void generateNextOffset();


	
};
#endif

