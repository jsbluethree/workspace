// CeleryManStates.cpp
// Chris Bowers

#include "CeleryManStates.h"

void CMStartState::run(){
	std::cout << "Good morning, Paul.\nWhat will your first sequence of the day be?\n" << std::endl;
	std::string input;
	for (;;){
		std::getline(std::cin, input);
		for (auto& c : input) c = tolower(c);
		if (strstr(input.c_str(), "celery")){
			std::cout << "Yes, Paul.\nLoading Celery Man.\n" << std::endl;
			events().dispatch(new StateEvent("celery"));
			break;
		}
		else if (strstr(input.c_str(), "quit")){
			std::cout << "Yes, Paul. Goodbye, Paul.\n" << std::endl;
			events().dispatch(new CMQuitEvent);
			break;
		}
		else{
			std::cout << "I'm sorry, I didn't understand that.\nWhat will your first sequence of the day be?\n" << std::endl;
		}
	}
}

CMCeleryManState::CMCeleryManState(AssetManager& am) : assets{ am }, close_windows{ false } {}

void CMCeleryManState::run(){
	std::thread window_thread(&CMCeleryManState::play_windows, this);
	std::string input;
	for (;;){
		std::getline(std::cin, input);
		for (auto& c : input) c = tolower(c);
		if (strstr(input.c_str(), "add") || strstr(input.c_str(), "oyster")){
			std::cout << "Adding sequence: Oyster.\n" << std::endl;
			events().dispatch(new StateEvent("oyster"));
			break;
		}
		else if (strstr(input.c_str(), "quit")){
			std::cout << "Yes, Paul. Goodbye, Paul.\n" << std::endl;
			events().dispatch(new CMQuitEvent);
			break;
		}
	}
	close_windows = true;
	window_thread.join();
}

void CMCeleryManState::play_windows(){
	AnimatedSprite celery[4];
	sf::RenderWindow celerywin[4];
	for (int i = 0; i < 4; ++i){
		celery[i].play(assets.get_animation("celery" + std::to_string(i + 1)));
		celerywin[i].create(sf::VideoMode(celery[i].getTextureRect().width, celery[i].getTextureRect().height), "Celery Man");
	}
	celerywin[0].setPosition({ 0, 0 });
	celerywin[1].setPosition({ 200, 200 });
	celerywin[2].setPosition({ 400, 400 });
	celerywin[3].setPosition({ 600, 600 });
	sf::Clock update_clock;
	sf::Time last_time = sf::Time::Zero;
	while (!close_windows){
		for (int i = 0; i < 4; ++i){
			celery[i].update(update_clock.getElapsedTime() - last_time);
			celerywin[i].clear();
			celerywin[i].draw(celery[i]);
			celerywin[i].display();
		}
		last_time = update_clock.getElapsedTime();
	}
}

CMOysterState::CMOysterState(AssetManager& am) : assets{ am }, close_windows{ false } {}

void CMOysterState::run(){
	std::thread window_thread(&CMOysterState::play_windows, this);
	std::string input;
	for (;;){
		std::getline(std::cin, input);
		for (auto& c : input) c = tolower(c);
		if (strstr(input.c_str(), "print")){
			std::cout << "Okay.\n" << std::endl;
			char* dir = _getcwd(nullptr, FILENAME_MAX);
			std::string command("mspaint /pt ");
			command += dir;
			command += "\\oyster_smiling.png";
			system(command.c_str());
			free(dir);
		}
		else if (strstr(input.c_str(), "new") || strstr(input.c_str(), "tayne") || strstr(input.c_str(), "beta")){
			std::cout << "I have a new beta sequence for you, Paul.\nNow loading...\n" << std::endl;
			events().dispatch(new StateEvent("tayne"));
			break;
		}
		else if (strstr(input.c_str(), "quit")){
			std::cout << "Yes, Paul. Goodbye, Paul.\n" << std::endl;
			events().dispatch(new CMQuitEvent);
			break;
		}
	}
	close_windows = true;
	window_thread.join();
}

void CMOysterState::play_windows(){
	AnimatedSprite oyster[3];
	sf::RenderWindow oysterwin[3];
	for (int i = 0; i < 3; ++i){
		oyster[i].play(assets.get_animation("oyster" + std::to_string(i + 1)));
		oysterwin[i].create(sf::VideoMode(oyster[i].getTextureRect().width, oyster[i].getTextureRect().height), "Oyster");
	}
	sf::Clock update_clock;
	sf::Time last_time = sf::Time::Zero;
	while (!close_windows){
		for (int i = 0; i < 3; ++i){
			oyster[i].update(update_clock.getElapsedTime() - last_time);
			oysterwin[i].clear();
			oysterwin[i].draw(oyster[i]);
			oysterwin[i].display();
		}
		last_time = update_clock.getElapsedTime();
	}
}

CMTayneState::CMTayneState(AssetManager& am) : assets{ am }, close_windows{ false } {}

void CMTayneState::run(){
	std::thread window_thread(&CMTayneState::play_windows, this);
	std::string input;
	for (;;){
		std::getline(std::cin, input);
		for (auto& c : input) tolower(c);
		if (strstr(input.c_str(), "quit")){
			std::cout << "Yes, Paul. Goodbye, Paul.\n" << std::endl;
			events().dispatch(new CMQuitEvent);
			break;
		}
	}
	close_windows = true;
	window_thread.join();
}

void CMTayneState::play_windows(){
	AnimatedSprite tayne[6];
	sf::RenderWindow taynewin[6];
	for (int i = 0; i < 6; ++i){
		tayne[i].play(assets.get_animation("tayne" + std::to_string(i + 1)));
		taynewin[i].create(sf::VideoMode(tayne[i].getTextureRect().width, tayne[i].getTextureRect().height), "TAYNE");
	}
	sf::Clock update_clock;
	sf::Time last_time = sf::Time::Zero;
	while (!close_windows){
		for (int i = 0; i < 6; ++i){
			tayne[i].update(update_clock.getElapsedTime() - last_time);
			taynewin[i].clear();
			taynewin[i].draw(tayne[i]);
			taynewin[i].display();
		}
		last_time = update_clock.getElapsedTime();
	}
}

/**/