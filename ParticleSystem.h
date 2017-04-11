#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
using namespace sf;
using namespace std;
class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();
	void update(float delta)
	{
		for(vector<Particle>::iterator p = liveParticles->begin(); p != liveParticles->end(); ++p)
		{
			p->velocity += gravity * delta;
			p->setPosition(p->getPosition() + p->velocity * delta);
			Color c = p->rect.getFillColor();
			p->lifetime -= delta;
			c.a = 255 * p->lifetime / 5;
			//c.a = rand() % 255;
			if (p->lifetime <= 0)
			{
				Particle temp = *p;
				liveParticles->erase(p);
				deadParticles->push_back(temp);
				break;
			}
			else
			{
				p->rect.setFillColor(c);
			}
		}
	};
	void draw(RenderWindow &w)
	{
		for (vector<Particle>::iterator p = liveParticles->begin(); p != liveParticles->end(); ++p)
		{
			w.draw(p->rect);
		}
	};
	void spawnParticle(float xPos, float yPos)
	{
		if (deadParticles->size() > 0)
		{
			Particle p = deadParticles->back();
			deadParticles->pop_back();
			p.reset(xPos, yPos);
			liveParticles->push_back(p);
		}
		else
		{
			Particle p(xPos, yPos);
			liveParticles->push_back(p);
		}
	};
private:
	struct Particle
	{
		float lifetime = 5;
		float speed = rand()% 75 + 150;
		Vector2f velocity;
		RectangleShape rect;
		Particle(float xPos, float yPos)
		{
			rect.setSize(Vector2f(10, 10));
			rect.setOutlineThickness(1);
			rect.setPosition(Vector2f(xPos, yPos));
			rect.setFillColor(Color(rand() % 255, rand() % 255, rand() % 255, 255));
			float angle = (rand() % (125 - 55) + 55) * 3.14/180;
			velocity = Vector2f(cos(angle) * speed, sin(angle) * speed * -1);
		};
		void reset(float xPos, float yPos)
		{
			lifetime = 5;
			rect.setPosition(Vector2f(xPos, yPos));
			rect.setFillColor(Color(rand() % 255, rand() % 255, rand() % 255, 255));
			float angle = (rand() % (125 - 55) + 55) * 3.14 / 180;
			velocity = Vector2f(cos(angle) * speed, sin(angle) * speed * -1);
		}
		void setPosition(Vector2f newPos)
		{
			rect.setPosition(newPos);
		}
		Vector2f getPosition()
		{
			return rect.getPosition();
		}

	};
	Vector2f gravity = Vector2f(0, 100);
	vector<Particle> *liveParticles = new vector<Particle>;
	vector<Particle> *deadParticles = new vector<Particle>;
	
};

