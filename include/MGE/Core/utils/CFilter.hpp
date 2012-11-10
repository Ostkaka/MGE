#ifndef CFILTER_HPP
	#define CFILTER_HPP
 
#include <SFML\System\Clock.hpp>
#include <SFML\Graphics.hpp>

#define COLOR sf::Uint8(255)
namespace MGEUtil
{

	class Filter{
 
			private :
 
			sf::Sprite m_Filter;
			sf::Clock m_clockCFilter;
			float m_FilterDelay; //The delay bewteen two alpha removing
			float m_alphaChanger; //Number of alpha decrease or increase at each frame (1 : Slow, 2.5 : Medium, 5 : Fast)
			float m_alphaColor; //Current Alpha color of the CFilter
			bool m_FilterIn; //To know if we have to do a fade out or a fade in
			bool m_runFade; //Activate the fade
 
 
			public :
 
			Filter();
			Filter::Filter(sf::Texture &textureFilter,float newAlphaChanger); //newAlphaChanger is the speed of the CFilter application
			~Filter();
 
			void run(); //Do a fade out or a fade in using the CFilter
 
			sf::Sprite getFilterSprite()const; //Display the CFilter
			float getAlphaColor() const; //Return the current alpha color of the CFilter
			float getAlphaChanger() const; //Return the time between two alpha changing
 
			void setFilterDelay(float newDelay);
 
			void setFilterTexture(sf::Texture &newFilter); //Change the CFilter
			void setAlphaColor(float newAlphaColor); //Change manually alpha color if you want a constent CFilter
			void setAlphaChanger(float newAlphaChanger); //To change the rapidity of the fade in or the fade out
 
			void changeFade(bool fade); //Change a fade in to a fade out or a fade out to a fade in
 
	};
}
#endif // CFilter_H_INCLUDED

