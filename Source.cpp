#include "ParticleSystem.h"
#include "ParticleSystem2.h"
#include <iostream>

ParticleSystem ps;
ParticleSystem2 ps2;
void update(double delta)
{
	ps.update(delta);
	ps2.update(delta);
}
void draw(RenderWindow &w)
{
	ps.draw(w);
	ps2.draw(w);
}
int main()
{
	RenderWindow window(VideoMode(1200, 800), "SFML works!");
	Clock clock;
	Time time;
	int timer = 0;
	int modVal = 150;
	Vector2i psPos = Vector2i(300, 500);
	Vector2i ps2Pos = Vector2i(900, 500);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			/*if (event.type == Event::MouseButtonPressed)
			{
				if (Mouse::isButtonPressed(Mouse::Left)) {
					psPos = Mouse::getPosition(window);
				}
			}*/
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				modVal = 10;
			}
			else
			{
				modVal = 150;
			}
		}
		
		timer++;
		if (timer % modVal == 0)
		{
			timer = 0;
			//Vector2i mouse = Mouse::getPosition(window);
			ps.spawnParticle(window.mapPixelToCoords(psPos).x, window.mapPixelToCoords(psPos).y);
			ps2.spawnParticle(window.mapPixelToCoords(ps2Pos).x, window.mapPixelToCoords(ps2Pos).y);
		}

		window.clear();
		double delta = clock.restart().asSeconds();
		update(delta);
		draw(window);
		window.display();
	}

	return 0;
}

