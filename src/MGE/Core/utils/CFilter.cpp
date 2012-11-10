#include <MGE/Core/utils/CFilter.hpp>
 
namespace MGEUtil
{

	Filter::Filter()
	{
	}
 
	Filter::Filter(sf::Texture &textureFilter,float newAlphaChanger)
	{
			m_Filter.setTexture(textureFilter);
			m_FilterDelay=0.01;
			m_alphaChanger=newAlphaChanger;
			m_runFade=false;
			m_alphaColor=0;
			m_Filter.setColor(sf::Color(COLOR,COLOR,COLOR,m_alphaColor));
	}
 
	Filter::~Filter()
	{
 
	}
 
	void Filter::run()
	{
			if((m_FilterIn) && (m_runFade))
			{
			if((m_alphaColor<=COLOR) && (m_clockCFilter.getElapsedTime().asMilliseconds() > m_FilterDelay))
					{
							m_Filter.setColor(sf::Color(COLOR,COLOR,COLOR,m_alphaColor+=m_alphaChanger));
				m_clockCFilter.restart();
					}
 
					if(m_alphaColor>COLOR)
					{
							m_Filter.setColor(sf::Color(COLOR,COLOR,COLOR,m_alphaColor=COLOR));
							m_runFade=false;
					}
			}
			else if((!m_FilterIn) && (m_runFade))
			{
			if((m_alphaColor>=0) && (m_clockCFilter.getElapsedTime().asMilliseconds() > m_FilterDelay))
					{
							m_Filter.setColor(sf::Color(COLOR,COLOR,COLOR,m_alphaColor-=m_alphaChanger));
							m_clockCFilter.restart();
					}
 
					if(m_alphaColor<0)
					{
							m_Filter.setColor(sf::Color(COLOR,COLOR,COLOR,m_alphaColor=0));
							m_runFade=false;
					}
			}
	}
 
 
	sf::Sprite Filter::getFilterSprite()const
	{
			return m_Filter;
	}
 
	float Filter::getAlphaColor() const
	{
			return m_alphaColor;
	}
 
	float Filter::getAlphaChanger() const
	{
			return m_alphaChanger;
	}
 
 
 
	void Filter::setFilterDelay(float newDelay)
	{
			m_FilterDelay=newDelay;
	}
 
	void Filter::setFilterTexture(sf::Texture &newFilter)
	{
		m_Filter.setTexture(newFilter);
	}
 
	void Filter::setAlphaColor(float newAlphaColor)
	{
			m_Filter.setColor(sf::Color(COLOR,COLOR,COLOR,newAlphaColor));
	}
 
	void Filter::setAlphaChanger(float newAlphaChanger)
	{
			m_alphaChanger=newAlphaChanger;
	}
 
	void Filter::changeFade(bool fade)
	{
			m_runFade=true;
 
			if(fade)
			{
					m_alphaColor=0;
					m_Filter.setColor(sf::Color(COLOR,COLOR,COLOR,m_alphaColor));
					m_FilterIn=true;
			}
			else
			{
					m_alphaColor=COLOR;
					m_Filter.setColor(sf::Color(COLOR,COLOR,COLOR,m_alphaColor));
					m_FilterIn=false;
			}
	}

}