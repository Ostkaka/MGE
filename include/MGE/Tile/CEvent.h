#ifndef _CEVENT_H_
    #define _CEVENT_H_

#include <SFML/Graphics.hpp>

class CEvent {
    public:

		//Changed to SFML
        CEvent();

        virtual ~CEvent();

        virtual void onEvent(sf::Event * event);

		virtual void onExit();

		//Not changed

        virtual void onInputFocus();

        virtual void onInputBlur();

		virtual void onKeyDown(sf::Event::KeyEvent * event);

        virtual void onKeyUp(sf::Event::KeyEvent * event);

        virtual void onMouseFocus();

        virtual void onMouseBlur();

        virtual void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);

        virtual void OnMouseWheel(bool Up, bool Down);  //Not implemented

        virtual void OnLButtonDown(int mX, int mY);

        virtual void OnLButtonUp(int mX, int mY);

        virtual void OnRButtonDown(int mX, int mY);

        virtual void OnRButtonUp(int mX, int mY);

        virtual void OnMButtonDown(int mX, int mY);

        virtual void OnMButtonUp(int mX, int mY);

        virtual void OnMinimize();

        virtual void OnRestore();

        virtual void OnResize(int w,int h);

        virtual void OnExpose();

};

#endif
