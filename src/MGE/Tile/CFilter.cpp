#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
 
#include"CFilter.h"
 
CFilter::CFilter()
{
 
}
 
CFilter::CFilter(sf::Texture &textureFilter,float newAlphaChanger)
{
    m_Filter.setTexture(textureFilter);
    m_FilterDelay=0.01;
    m_alphaChanger=newAlphaChanger;
    m_runFade=false;
    m_alphaColor=0;
    m_Filter.setColor(sf::Color(COLOR,COLOR,COLOR,m_alphaColor));
}
 
CFilter::~CFilter()
{
 
}
 
 
 
void CFilter::runCFilter()
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
 
 
sf::Sprite CFilter::getCFilter()const
{
    return m_Filter;
}
 
float CFilter::getAlphaColor() const
{
    return m_alphaColor;
}
 
float CFilter::getAlphaChanger() const
{
    return m_alphaChanger;
}
 
 
 
void CFilter::setCFilterDelay(float newDelay)
{
    m_FilterDelay=newDelay;
}
 
void CFilter::setCFilter(sf::Texture &newFilter)
{
	m_Filter.setTexture(newFilter);
}
 
void CFilter::setAlphaColor(float newAlphaColor)
{
    m_Filter.setColor(sf::Color(COLOR,COLOR,COLOR,newAlphaColor));
}
 
void CFilter::setAlphaChanger(float newAlphaChanger)
{
    m_alphaChanger=newAlphaChanger;
}
 
void CFilter::changeFade(bool fade)
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

