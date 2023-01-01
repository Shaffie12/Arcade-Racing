#ifndef PROPS_H_
#define _PROPS_H_
#include "Drawable.h"
#include "GameGlobals.h"
#include "Track.h"
#include <memory>
#include<list>

class Background :public Drawable
{
public:
	Background();
	virtual void drawElement(sf::RenderTarget& w) override;
	void scroll(float amount);
	void setBackground(int bgNum);
	void update(const float& dt) override;

private:
	sf::Texture bgTex; 
	std::vector<sf::Sprite> bg_list;
	sf::Sprite* selected_bg;

	class ScrollingBackground
	{
	public:
		
		ScrollingBackground(sf::Sprite& image) 
		{
			imgs.push_back(ImagePart(image, -image.getGlobalBounds().width, 0)); //0
			imgs.push_back(ImagePart(image));
			imgs.push_back(ImagePart(image, image.getGlobalBounds().width, 0)); 
			

			
			
		}
			
		

		struct ImagePart
		{
			
			ImagePart(sf::Sprite& s)
			{
				sprite = s;
				sprite.setPosition(sf::Vector2f(0, 0));
			}
			ImagePart(sf::Sprite& s, float x, float y)
			{
				sprite = s;
				sprite.setPosition(sf::Vector2f(x, y));
			}

			sf::Sprite sprite;
			bool onScreen()
			{
				return sprite.getPosition().x <= 0 && sprite.getPosition().x + sprite.getGlobalBounds().width <= GameGlobals::GAME_W + 100;
				
			}

			

		};

		std::vector<ImagePart> imgs;
		

	};
	ScrollingBackground* gameBG;



};


#endif 
