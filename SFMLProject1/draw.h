//
//	draw.h
//
//	Finn Le Var
//
#pragma once

#include <SFML/Graphics.hpp>

#include <functional>

#include "priority.h"

// the number type that we're using for our priority in our priority vec
// putting it here in case we want to change it or test out other types
using num_type_t = char;

//
// draw list to allow us to draw items in a certain order
//
// basically a wrapper for a priority vector with a slightly different push function
//
class draw_list_t
{
private:

	// our draw list
	TPriority<std::pair<sf::Drawable*, std::function<void(sf::Drawable&)>>, num_type_t> m_list;

public:

	draw_list_t()	= default;
	~draw_list_t()	= default;

	//
	// draws all the items in our list
	//
	void draw(sf::RenderWindow& _window)
	{
		// get our item and it's updater
		for (auto [item, updater] : m_list)
		{
			// update our item
			updater(*item);

			// then draw it
			_window.draw(*item);
		}
	}

	//
	// pushes the given drawable item to our list at the given z index, also allows us to pass a
	// lambda to update the item we're passing
	//
	template<typename drawable_t, typename updater_t>
	void push(drawable_t* _item, num_type_t _z, updater_t&& _update)
	{
		// wrap our updater lambda so that we can store it for when we actually draw our object so that
		// each item updates with its correct data since we're reusing the same base drawables
		auto wrapped = [update = std::forward<updater_t>(_update)](sf::Drawable& _item)
		{
			update(static_cast<drawable_t&>(_item));
		};

		// push the item to our list
		m_list.push({ _item, wrapped }, _z);
	}

	void		pop()	{ m_list.pop();			}
	void		clear()	{ m_list.clear();		}
	std::size_t size()	{ return m_list.size(); }
	bool		empty()	{ return m_list.empty();}
};

// our main draw list
extern draw_list_t g_draw;

// including at the end as its not used in this class, only including it here
// because we include draw.h where we need our draw list(s), and shapes.h is also needed
// for our draw list to work
#include "shapes.h"
