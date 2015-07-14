// tests.cpp
// Chris Bowers

/**
 *	This contains various tests. This also contains, for now, the entry point.
 */

#include "SFML.h"

int main(int argc, char** argv){
	Window main_window(VideoMode(800, 600), "Tests");

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
