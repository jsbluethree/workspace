// CeleryManStates.h
// Chris Bowers

#ifndef __CELERYMANSTATES_H__
#define __CELERYMANSTATES_H__

#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <direct.h>
#include <iostream>
#include <string>
#include <thread>
#include "SFML\Graphics.hpp"
#include "SFML\System.hpp"
#include "SFML\Window.hpp"
#include "AnimatedSprite.h"
#include "AssetManager.h"
#include "Dispatcher.h"
#include "IState.h"
#include "StateMachine.h"

struct CMStartState : IState{
	void enter() { events().tick(0); }
	void run();
	Dispatcher& events() { return m_events; }

private:
	Dispatcher m_events;
};

struct CMCeleryManState : IState{
	CMCeleryManState(AssetManager& am);
	void enter() { events().tick(0); }
	void run();
	void play_windows();
	Dispatcher& events() { return m_events; }

private:
	Dispatcher m_events;
	AssetManager& assets;
	bool close_windows;
};

struct CMOysterState : IState{
	CMOysterState(AssetManager& am);
	void enter() { events().tick(0); }
	void run();
	void play_windows();
	Dispatcher& events() { return m_events; }

private:
	Dispatcher m_events;
	AssetManager& assets;
	bool close_windows;
};

struct CMTayneState : IState{
	CMTayneState(AssetManager& am);
	void enter() { events().tick(0); }
	void run();
	void play_windows();
	Dispatcher& events() { return m_events; }

private:
	Dispatcher m_events;
	AssetManager& assets;
	bool close_windows;
};

struct CMEndState : IState{
	void enter() { events().tick(0); }
	void run() {}
	Dispatcher& events() { return m_events; }

private:
	Dispatcher m_events;
};

struct CMQuitEvent : IEvent{};

#endif

/**/