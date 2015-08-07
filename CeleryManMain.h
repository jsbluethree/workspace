// CeleryManMain.h
// Chris Bowers

#ifndef __CELERYMANMAIN_H__
#define __CELERYMANMAIN_H__

#include <cstdlib>
#include "AssetManager.h"
#include "CeleryManStates.h"
#include "ICallback.h"
#include "Input.h"
#include "StateMachine.h"

struct CeleryManMain{
	CeleryManMain();
	~CeleryManMain();

	void run();

private:
	CMStartState start;
	CMCeleryManState celery_man;
	CMOysterState oyster;
	CMTayneState tayne;
	CMEndState end;

	StateMachine state_machine;
	AssetManager assets;

	bool end_flag;

	struct OnQuit : ICallback{
		OnQuit(CeleryManMain& m);
		void operator()(const IEvent&);
		CeleryManMain& main;
	} quit_listener;
};

#endif // __CELERYMANMAIN_H__

/**/