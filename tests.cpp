// tests.cpp
// Chris Bowers

/**
 *	This contains various tests. This also contains, for now, the entry point.
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "SFML.h"
#include "Quadtree.h"
#include "BasicEntity.h"



RenderWindow main_window;

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector2<T>& vec){
	os << '(' << vec.x << ' ' << vec.y << ')';
	return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Rect<T>& rect){
	os << '(' << rect.left << ' ' << rect.top << ' ' << rect.width << ' ' << rect.height << ')';
	return os;
}

void test_quad_tree(){
	srand(time(nullptr));
	Texture a_tex;
	if (!a_tex.loadFromFile("a.png")) return;
	BasicEntity a[20];
	Quadtree qtree(0, FloatRect(0, 0, 800, 600));
	for (auto& s : a){
		s.setTexture(a_tex);
		s.scale(0.1f, 0.1f);
		s.setPosition(rand() % 770, rand() % 570);
		std::cout << s.get_rect() << std::endl;
		qtree.insert(&s);
	}
	int size = 0;
	for (const auto& p : qtree.retrieve(0.0f, 0.0f)){
		std::cout << p << std::endl;
		size++;
	}
	std::cout << size;
	while (main_window.isOpen()){
		Event event;
		while (main_window.pollEvent(event)){
			if (event.type == Event::Closed){
				main_window.close();
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
