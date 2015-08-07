// CeleryManMain.cpp
// Chris Bowers

#include "CeleryManMain.h"

CeleryManMain::CeleryManMain() :
celery_man{ assets },
oyster{ assets },
tayne{ assets },
end_flag{ false },
quit_listener{ *this } {
	state_machine.add_state("start", start);
	state_machine.add_state("celery", celery_man);
	state_machine.add_state("oyster", oyster);
	state_machine.add_state("tayne", tayne);
	state_machine.add_state("end", end);
	start.events().add_listener<CMQuitEvent>(quit_listener);
	celery_man.events().add_listener<CMQuitEvent>(quit_listener);
	oyster.events().add_listener<CMQuitEvent>(quit_listener);
	tayne.events().add_listener<CMQuitEvent>(quit_listener);
	end.events().add_listener<CMQuitEvent>(quit_listener);
	state_machine.set_state("start");
}

CeleryManMain::~CeleryManMain(){
	auto state = state_machine.get_current_state();
	if (state) state->exit();
}

void CeleryManMain::run(){
	assets.load_textures("textures.json");
	assets.load_animations("animations.json");
	while (!end_flag)
		state_machine.get_current_state()->run();
}

CeleryManMain::OnQuit::OnQuit(CeleryManMain& m) : main{ m }{}

void CeleryManMain::OnQuit::operator()(const IEvent&) { main.end_flag = true; }

/**/