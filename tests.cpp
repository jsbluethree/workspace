// tests.cpp
// Chris Bowers

/**
 *	This contains various tests. This also contains, for now, the entry point.
 */
#include "CeleryManMain.h"
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
#include "PoolAllocator.h"
#include "Camera.h"
#include "stringf.h"

sf::RenderWindow main_window;
Camera main_cam({ 0, 0, 800, 600 });
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
		main_cam.render_scene(qtree, main_window);
		//for (const auto& s : a) main_window.draw(s);
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

struct TestEvent : IEvent{};

struct TestCB : ICallback{
	void operator()(const IEvent&) { std::cout << "event dispatched!\n"; }
};

void test_dispatcher(){
	TestCB testcb;
	Dispatcher events;
	events.add_listener<TestEvent>(testcb);
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
	void operator()(const IEvent&) { main_window.close(); }
};

struct JoyButtonCB : ICallback{
	void operator()(const IEvent& event){
		const auto& jbpe = static_cast<const JoystickButtonPressedEvent&>(event);
		std::cout << "pushed button " << jbpe.button << std::endl;
	}
};

void test_input_handler(){
	Input main_input(main_window);
	CloseCB closer;
	TestCB testcb;
	JoyButtonCB buttoncb;
	main_input.events.add_listener<ClosedEvent>(closer);
	main_input.events.add_listener<MouseButtonPressedEvent>(testcb);
	main_input.events.add_listener<KeyPressedEvent>(testcb);
	main_input.events.add_listener<JoystickButtonPressedEvent>(buttoncb);
	while (main_window.isOpen()){
		main_input.tick(0);
	}
}

struct TestObj{
	ENABLE_POOL_ALLOCATION(TestObj);
};

void test_pool_alloc(){
	auto obj = new TestObj;
	delete obj;
}

void test_stringf(){
	std::cout << stringf("no formatting\n");
	std::cout << stringf("a number: %%\n", 5);
	//std::cout << stringf("no operator defined for %%\n", TestObj()); does not compile
	std::cout << stringf("too many specifiers: %% %% %%\n", 5, 6);
	std::cout << stringf("not enough specifiers: && &&\n", 5, 6, 7);
}

int main(int argc, char** argv){
	/*
	test_pool_alloc();

	main_window.create({ 800, 600 }, "Tests");

	load_assets();
	
	test_quad_tree();
	
	test_animation();

	test_dispatcher();

	test_input_handler();

	CeleryManMain main;
	main.run();

	/**/

	test_stringf();

	return 0;
}
