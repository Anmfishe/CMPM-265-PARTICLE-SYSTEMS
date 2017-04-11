#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>
using namespace sf;
using namespace std;
class ParticleSystem2
{
public:
	ParticleSystem2();
	~ParticleSystem2();
	
	void update(float delta)
	{
		for (vector<Particle>::iterator p = liveParticles->begin(); p != liveParticles->end();++p)
		{
			p->velocity += p->accel * delta;
			p->setPosition(p->getPosition() + p->velocity * delta);
			//Color c = p->circle.getFillColor();
			p->lifetime -= delta;
			//c.a = 255 * p->lifetime / 4;
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
				
				p->circle.setRadius(p->radius * p->lifetime / p->lifetime_save);

			}
		}
	};
	void draw(RenderWindow &w)
	{
		for (vector<Particle>::iterator p = liveParticles->begin(); p != liveParticles->end(); ++p)
		{
			w.draw(p->circle);
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
			Particle p(xPos, yPos, t);
			
			liveParticles->push_back(p);
		}
	};
private:
	Texture t;
	
	struct Particle
	{
		float lifetime = rand() % 3 + 2;
		float lifetime_save = lifetime;
		float speedX = rand() % 75 + 150;
		float speedY = rand() % 150 + 250;
		Vector2f velocity;
		Vector2f accel;
		CircleShape circle;
		float radius = rand() % 40 + 20;
		
		//t->loadFromFile("Art/FIRE.png");
		Particle(float xPos, float yPos, Texture &t)
		{
			circle.setRadius(radius);
			
			circle.setTexture(&t);
			circle.setOrigin(Vector2f(circle.getRadius() / 2, circle.getRadius() / 2));
			circle.setPosition(Vector2f(xPos, yPos));


			//circle.setOutlineThickness(0);

			float angle = (rand() % (135 - 45) + 45) * 3.14 / 180;
			accel.x = rand() % 100 - 50;
			accel.y = rand() % 200 - 150 * -1;
			velocity = Vector2f(cos(angle) * speedX, sin(angle) * speedY * -1);
		}
		void reset(float xPos, float yPos)
		{
			lifetime = rand() % 3 + 2;
			lifetime_save = lifetime;
			circle.setRadius(radius);
			//circle.setOrigin(Vector2f(circle.getRadius() / 2, circle.getRadius() / 2));
			circle.setPosition(Vector2f(xPos, yPos));
			//circle.setSize(Vector2f(20, 20));
			float angle = (rand() % (135 - 45) + 45) * 3.14 / 180;
			accel.x = rand() % 200 - 100;
			accel.y = rand() % 200 - 150 * -1;
			velocity = Vector2f(cos(angle) * speedX, sin(angle) * speedY * -1);
		}
		void setPosition(Vector2f newPos)
		{
			circle.setPosition(newPos);
		}
		Vector2f getPosition()
		{
			return circle.getPosition();
		}
	};
		

	
	vector<Particle> *liveParticles = new vector<Particle>;
	vector<Particle> *deadParticles = new vector<Particle>;

};

