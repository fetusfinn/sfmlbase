//
//  Base project for a 2d SFML powered game
//

#include "draw.h"
#include "shapes.h"

/* TODO
 *
 * x draw list
 * - notifications
 * - keypress handler
 * - font map
 *
 * - saving system
 *   - json
 *
 * ? scripting
 * ? thread pool
 *
 * - print macros
 *
 *
 *
 * TODO LATER
 *
 * - decouple the update ticks and render frames
 * - render batching
 *	 - use sf::VertexArrays
 *
 */

// how many frames we're aiming for each second
constexpr float target_fps = 60.f;

// the duration of a tick
constexpr float time_step	 = 1.f / target_fps;

// our main draw list
draw_list_t g_draw;

//
//
//
int main()
{
	// Seed our RNG
	std::srand(std::time(nullptr));

	// Create the window with a set resolution:
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Base");

	// Set the frame rate limit
	window.setFramerateLimit(target_fps);

	// clock to track our delta time
	sf::Clock clock;

	// the delta time between ticks
	sf::Time delta;

	// what tick we're on
	float tick = 0;

	bool bnotif = false;

	//
	// For as long as the window's open
	//
	while (window.isOpen())
	{
		// get the delta and restart our clock
		delta = clock.restart();

		tick++;

		// clear our draw list for us to reuse this frame
		g_draw.clear();

		//
		// Event handling
		//
		{
			sf::Event rEvent;
			while (window.pollEvent(rEvent))
			{
				switch (rEvent.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				}
			}
		}

		//
		// Updating
		//
		{
			// draw what tick we're on
			g_draw.push(shape::text(), 0, [&tick](sf::Text& _t)
			{
				_t.setPosition(10, 100 + 30);
				_t.setFillColor(sf::Color::White);
				_t.setString("Frame : " + std::to_string((int)tick));
				_t.setCharacterSize(15);
			});

			// draw what tick we're on
			g_draw.push(shape::text(), 0, [&tick](sf::Text& _t)
			{
				_t.setPosition(10, 100 + 60);
				_t.setFillColor(sf::Color::Blue);
				_t.setString("Tick : " + std::to_string((int)tick));
				_t.setCharacterSize(15);
			});

			// draw what tick we're on
			g_draw.push(shape::text(), 0, [&tick](sf::Text& _t)
			{
				_t.setPosition(10, 100 + 90);
				_t.setFillColor(sf::Color::Red);
				_t.setString("Frame : " + std::to_string((int)tick));
				_t.setCharacterSize(15);
			});

			// draw what tick we're on
			g_draw.push(shape::text(), 0, [&tick](sf::Text& _t)
			{
				_t.setPosition(10, 100 + 120);
				_t.setFillColor(sf::Color::Green);
				_t.setString("Tick : " + std::to_string((int)tick));
				_t.setCharacterSize(15);
			});

			// draw what tick we're on
			g_draw.push(shape::text(), 0, [&tick](sf::Text& _t)
			{
				_t.setPosition(10, 100 + 150);
				_t.setFillColor(sf::Color::Yellow);
				_t.setString("Frame : " + std::to_string((int)tick));
				_t.setCharacterSize(15);
			});

		}

		//
		// Drawing
		//
		//window.clear(sf::Color::White);
		window.clear(sf::Color::Black);
		{
			g_draw.draw(window);
		}
		window.display();
	}

	return 0;
}