// tests.cpp
// Chris Bowers

/**
 *	This contains various tests. This also contains, for now, the entry point.
 */

#include "SFML.h"
#include "Quadtree.h"

RenderWindow main_window;

void test_quad_tree(){
	Texture tex_am;
	if (!tex_am.loadFromFile("amethyst.png")) return;
	Sprite spr_am;
	spr_am.setTexture(tex_am);

	while (main_window.isOpen()){
		Event event;
		while (main_window.pollEvent(event)){
			if (event.type == Event::Closed){
				main_window.close();
			}
			else if (event.type == Event::KeyPressed){
				if (event.key.code == Keyboard::Return){
					return;
				}
			}
		}
		main_window.clear();
		main_window.draw(spr_am);
		main_window.display();
	}
}

int main(int argc, char** argv){
	main_window.create(VideoMode(800, 600), "Tests");
	
	test_quad_tree();
	/**/

	while (main_window.isOpen()){
		Event event;
		while (main_window.pollEvent(event)){
			if (event.type == Event::Closed){
				main_window.close();
			}
		}
	}

	return 0;
}
