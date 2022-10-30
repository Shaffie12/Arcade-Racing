#include "Track.h"
#include<iostream>
#include <cmath>

float Track::road_w = 0.9f;
float Track::tile_w = 0.15;
float Track::minRoad = 0.01;
float Track::speed = 0;
float Track::dist = 0;
float Track::globalOffset = 0;
float Track::segmentAmt = 0;
std::vector<Track::Line> Track::lines = std::vector<Track::Line>(); 
Segment* Track::activeSeg = nullptr;

Track::Track(std::map<std::string,sf::Color> colors, std::vector<Segment> segments):baseSeg ( Segment(-1,0, 0))
{	
	for (int i = 1; i <=GameGlobals::GAME_H/2 ; i++)
		lines.push_back(Line(i));
	this->segments = segments;
	roadColors = colors;
	activeSeg = &this->segments.at(0);
	
	
}

void Track::drawElement(sf::RenderTarget& w)
{

	speed = Racing::Util::clamp(speed, 0, 1); //could move these
	dist += speed * 1.5;
	
	moveSegment();

	update();

	for (Line& l :lines)
	{
		w.draw(l.vertices, 10, sf::Lines);
	}
		
	//debug
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(0,activeSeg->screen_y),sf::Color::White),
		sf::Vertex(sf::Vector2f(GameGlobals::GAME_W, activeSeg->screen_y),sf::Color::White)
	};

	w.draw(line, 2, sf::Lines);

}

void Track::update()
{
	double dx = 0;
	double ddx = 0;
	double current_x = 0.5;
	
	float td = activeSeg->curvature;
	float bd = baseSeg.curvature; 

	rit = lines.rbegin();
	while(rit!=lines.rend())
	{
		
		Line& line = *rit;
		

		line.colours[0] = sinf(30 * pow(1 - line.perspective, 10) + dist * 0.1) > 0.0f ? roadColors.find("grassLight")->second : roadColors.find("grassDark")->second;
		line.colours[1] = sinf(50 * pow(1 - line.perspective, 5) + dist * 0.8) > 0.0f ? roadColors.find("rumble1")->second : roadColors.find("rumble2")->second;
		line.colours[2] = sinf(50 * pow(1 - line.perspective, 5) + dist * 0.8) > 0.0f ? roadColors.find("roadLight")->second: roadColors.find("roadDark")->second;

		if (line.screenY < activeSeg->screen_y)
			dx = td * ((1 - line.scaledY) *(1 - line.scaledY) / 6) * (((lines.at(lines.size()-1).scaledY) - line.scaledY) *2.5);
		else
			dx = bd * ((1 - line.scaledY) * (1 - line.scaledY) /6) * (((lines.at(lines.size() - 1).scaledY ) - line.scaledY) * 2.5);


		ddx += dx;
		current_x += ddx;
		line.middlePt = current_x + globalOffset;


		//grass left
		line.vertices[0] = sf::Vertex(sf::Vector2f(0, line.screenY), line.colours[0]);
		line.vertices[1] = sf::Vertex(sf::Vector2f((line.middlePt - line.perspective - line.tile_w) * GameGlobals::GAME_W, line.screenY), line.colours[0]);

		//road edge l
		line.vertices[2] = sf::Vertex(sf::Vector2f((line.middlePt - line.perspective - line.tile_w) * GameGlobals::GAME_W, line.screenY), line.colours[1]);
		line.vertices[3] = sf::Vertex(sf::Vector2f((line.middlePt - line.perspective) * GameGlobals::GAME_W, line.screenY), line.colours[1]);

		//road 
		line.vertices[4] = sf::Vertex(sf::Vector2f((line.middlePt - line.perspective) * GameGlobals::GAME_W, line.screenY), line.colours[2]);
		line.vertices[5] = sf::Vertex(sf::Vector2f((line.middlePt + line.perspective) * GameGlobals::GAME_W, line.screenY), line.colours[2]);//was roadLight

		//edge 2
		line.vertices[6] = sf::Vertex(sf::Vector2f((line.middlePt + line.perspective) * GameGlobals::GAME_W, line.screenY), line.colours[1]);
		line.vertices[7] = sf::Vertex(sf::Vector2f((line.middlePt + line.perspective + line.tile_w) * GameGlobals::GAME_W, line.screenY), line.colours[1]);

		//grass right
		line.vertices[8] = sf::Vertex(sf::Vector2f((line.middlePt + line.perspective + line.tile_w) * GameGlobals::GAME_W, line.screenY), line.colours[0]);
		line.vertices[9] = sf::Vertex(sf::Vector2f(GameGlobals::GAME_W, line.screenY), line.colours[0]);

		++rit;
	}
	

}

void Track::addPlayerOffset(float amount, bool add)
{
	if (add)
		globalOffset += amount;
	else
		globalOffset -= amount;
}

//move this to global space
void Track::addSpeed(float amount, bool add)
{ 
	
	if (add)speed += amount; else speed -= amount; 
}

void Track::addSegmentOffset()
{
	if (activeSeg->screen_y >= GameGlobals::GAME_H-80 )
	{
		globalOffset += (activeSeg->curvature * 8 * speed); 
		globalOffset = Racing::Util::clamp(globalOffset, -1.1f, 1.1f);
		segmentAmt = activeSeg->curvature; //we dont really need this since active segment is public static now (used in bg)
		
	}

}

void Track::nextSegment()
{

	
	if (activeSeg->screen_y>= GameGlobals::GAME_H)
	{
		
		baseSeg = *activeSeg; //copy
		activeSeg->screen_y = GameGlobals::GAME_H / 2;
		
		currentSeg = ++currentSeg % segments.size();
		
		activeSeg = &segments.at(currentSeg);
		
		
		
	}
	
}

void Track::moveSegment()
{
	activeSeg->screen_y += (0.7 * speed);
	addSegmentOffset();
	nextSegment();

		
}

