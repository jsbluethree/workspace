// tests.cpp
// Chris Bowers

/**
 *	This contains various tests. This also contains, for now, the entry point.
 */
#include "SFML\Graphics.hpp"
#include "SFML\System.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "SFMLUtility.h"
#include "QTSceneGraph.h"
#include "BasicEntity.h"
#include "AnimatedSprite.h"
#include "Dispatcher.h"
#include "Input.h"
#include "AssetManager.h"


sf::RenderWindow main_window;
AssetManager assets;

void load_assets(){
	assets.load_textures("textures.json");
	assets.load_animations("animations.json");
}

void test_quad_tree(){
	srand(time(nullptr));
	assets.get_texture("amethyst").setSmooth(true);
	BasicEntity a[20];
	QTSceneGraph qtree({ 0, 0, 800, 600 });
	for (auto& s : a){
		s.setTexture(assets.get_texture("amethyst"));
		s.scale(0.5f, 0.5f);
		s.setPosition(rand() % 660, rand() % 460);
		//std::cout << s.get_rect() << std::endl;
		qtree.add_node(s);
	}

	while (main_window.isOpen()){
		sf::Event event;
		while (main_window.pollEvent(event)){
			if (event.type == sf::Event::Closed){
				main_window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed){
				std::cout << "clicked " << event.mouseButton.x << ' ' << event.mouseButton.y << std::endl;
				auto clicked = qtree.get_collision(event.mouseButton.x, event.mouseButton.y);
				std::cout << clicked.size() << std::endl;
				for (auto& c : clicked){
					auto sprite = dynamic_cast<sf::Sprite*>(c);
					if (sprite){
						sprite->rotate(180);
						qtree.update_node(*c);
					}
				}
			}
			else if (event.type == sf::Event::KeyPressed){
				return;
			}
		}
		main_window.clear();
		for (const auto& s : a) main_window.draw(s);
		main_window.display();
	}
}

void test_animation(){
	AnimatedSprite cat(2.0f * AnimatedSprite::default_frame_time);
	cat.set_animation(assets.get_animation("cat"));
	sf::Clock update_clock;
	sf::Time last_time = sf::Time::Zero;
	while (main_window.isOpen()){
		sf::Event event;
		while (main_window.pollEvent(event)){
			if (event.type == sf::Event::Closed){
				main_window.close();
			}
			else if (event.type == sf::Event::KeyPressed){
				return;
			}
		}
		cat.update(update_clock.getElapsedTime() - last_time);
		last_time = update_clock.getElapsedTime();
		main_window.clear();
		main_window.draw(cat);
		main_window.display();
	}
}

struct TestEvent : IEvent{
	EventType type() const { return EventType::INVALID; }
};

struct TestCB : ICallback{
	void operator()(IEvent* event) { std::cout << "event dispatched!\n"; }
};

void test_dispatcher(){
	TestCB testcb;
	Dispatcher events;
	events.add_listener(EventType::INVALID, testcb);
	events.tick(0);
	while (main_window.isOpen()){
		sf::Event event;
		while (main_window.pollEvent(event)){
			if (event.type == sf::Event::Closed){
				main_window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed){
				events.dispatch(new TestEvent);
			}
			else if (event.type == sf::Event::KeyPressed){
				return;
			}
		}
	}
}

struct CloseCB : ICallback{
	void operator()(IEvent* event) { main_window.close(); }
};

struct JoyButtonCB : ICallback{
	void operator()(IEvent* event){
		auto sfe = static_cast<SFMLEvent&>(*event);
		std::cout << "pushed button " << sfe.sf_event.joystickButton.button << std::endl;
	}
};

void test_input_handler(){
	Input main_input(main_window);
	CloseCB closer;
	TestCB testcb;
	JoyButtonCB buttoncb;
	main_input.events.add_listener(EventType::SF_CLOSED, closer);
	main_input.events.add_listener(EventType::SF_MOUSEBUTTONPRESSED, testcb);
	main_input.events.add_listener(EventType::SF_KEYPRESSED, testcb);
	main_input.events.add_listener(EventType::SF_JOYSTICKBUTTONPRESSED, buttoncb);
	while (main_window.isOpen()){
		main_input.tick(0);
	}
}

int main(int argc, char** argv){

	main_window.create({ 800, 600 }, "Tests");

	load_assets();
	
	test_quad_tree();
	
	test_animation();

	test_dispatcher();

	test_input_handler();

	return 0;
}
