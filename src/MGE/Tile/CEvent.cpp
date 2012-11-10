#include "CEvent.h"

CEvent::CEvent() {
}

CEvent::~CEvent() {
    //Do nothing
}

void CEvent::onEvent(sf::Event* event) {
    switch(event->type) {
		case sf::Event::Closed: {
			onExit();
			break;
		}

		case sf::Event::KeyPressed: {
			onKeyDown(&event->key);
            break;
        }

        case sf::Event::KeyReleased: {
			onKeyUp(&event->key);
            break;
        }

        default: {
            //OnUser(Event->user.type,Event->user.code,Event->user.data1,Event->user.data2);
            break;
        }
    }
}

void CEvent::onInputFocus() {
    //Pure virtual, do nothing
}

void CEvent::onInputBlur() {
    //Pure virtual, do nothing
}

void CEvent::onKeyDown(sf::Event::KeyEvent * event) {
    //Pure virtual, do nothing
}

void CEvent::onKeyUp(sf::Event::KeyEvent * event) {
    //Pure virtual, do nothing
}

void CEvent::onMouseFocus() {
    //Pure virtual, do nothing
}

void CEvent::onMouseBlur() {
    //Pure virtual, do nothing
}

void CEvent::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle) {
    //Pure virtual, do nothing
}

void CEvent::OnMouseWheel(bool Up, bool Down) {
    //Pure virtual, do nothing
}

void CEvent::OnLButtonDown(int mX, int mY) {
    //Pure virtual, do nothing
}

void CEvent::OnLButtonUp(int mX, int mY) {
    //Pure virtual, do nothing
}

void CEvent::OnRButtonDown(int mX, int mY) {
    //Pure virtual, do nothing
}

void CEvent::OnRButtonUp(int mX, int mY) {
    //Pure virtual, do nothing
}

void CEvent::OnMButtonDown(int mX, int mY) {
    //Pure virtual, do nothing
}

void CEvent::OnMButtonUp(int mX, int mY) {
    //Pure virtual, do nothing
}

void CEvent::OnMinimize() {
    //Pure virtual, do nothing
}

void CEvent::OnRestore() {
    //Pure virtual, do nothing
}

void CEvent::OnResize(int w,int h) {
    //Pure virtual, do nothing
}

void CEvent::OnExpose() {
    //Pure virtual, do nothing
}

void CEvent::onExit() {
    //Pure virtual, do nothing
}
