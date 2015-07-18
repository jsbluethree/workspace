// tests.cpp
// Chris Bowers

/**
 *	This contains various tests. This also contains, for now, the entry point.
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "SFML.h"
#include "SFMLUtility.h"
#include "QTSceneGraph.h"
#include "BasicEntity.h"



RenderWindow main_window;

void test_quad_tree(){
	srand(time(nullptr));
	Texture a_tex;
	if (!a_tex.loadFromFile("a.png")) return;
	a_tex.setSmooth(true);
	BasicEntity a[20];
	QTSceneGraph qtree(FloatRect(0, 0, 800, 600));
	for (auto& s : a){
		s.setTexture(a_tex);
		s.scale(0.5f, 0.5f);
		s.setPosition(rand() % 660, rand() % 460);
		//std::cout << s.get_rect() << std::endl;
		qtree.add_node(s);
	}

	while (main_window.isOpen()){
		Event event;
		while (main_window.pollEvent(event)){
			if (event.type == Event::Closed){
				main_window.close();
			}
			else if (event.type == Event::MouseButtonPressed){
				std::cout << "clicked " << event.mouseButton.x << ' ' << event.mouseButton.y << std::endl;
				auto clicked = qtree.get_collision(event.mouseButton.x, event.mouseButton.y);
				std::cout << clicked.size() << std::endl;
				for (auto& c : clicked){
					auto sprite = dynamic_cast<Sprite*>(c);
					if (sprite) sprite->rotate(180);
				}
			}
		}
		main_window.clear();
		for (const auto& s : a) main_window.draw(s);
		main_window.display();
	}
}

int main(int argc, char** argv){

	main_window.create(VideoMode(800, 600), "Tests");
	
	test_quad_tree();
	

	while (main_window.isOpen()){
		Event event;
		while (main_window.pollEvent(event)){
			if (event.type == Event::Closed){
				main_window.close();
			}
		}
	}
	/**/
	return 0;
}
