##Lab 1: SFML Basic concepts##

**To be completed by:** Week 5 (Fri 14/10)

Learning Outcomes:

- Distinguish between the SFML game loop and event loop.
- Load a texture from an image file and create a sprite.
- Perform basic sprite operations (translate, rotate, set origin).

We will start by looking at the sample Visual Studio solution 'SFML Playground'. You should have cloned this project by now from github. If not, see [here](https://3cdf4b8c65bce13a1ec34bf338b0aad3a115db84.googledrive.com/host/0B6CcEO5JmSkdfmhYYlp6c3hSU2swVmN5dmxZVno2V3V6MnhuekNVYkdONkRNZThUSmNIRVk/0-Github.html).

**1.1 The SFML game loop**

Let's start inside the constructor function of class Game (game.cpp).

The first thing we do is create the SFML render window - the arguments include the screen resolution, colour depth (32 bits per pixel) and the window title:

    Game::Game()
    : m_window(sf::VideoMode(1440, 900, 32), "SFML Playground", sf::Style::Default)


Next, the `Game::run()` method encapsulates our game loop:

    void Game::run()
    {
    	sf::Clock clock;
    	sf::Int32 lag = 0;
    
    	while (m_window.isOpen())
    	{
    		sf::Time dt = clock.restart();
    
    		lag += dt.asMilliseconds();
    
    		processEvents();
    
    		while (lag > MS_PER_UPDATE)
    		{
    			update(MS_PER_UPDATE);
    			lag -= MS_PER_UPDATE;
    		}
    		update(MS_PER_UPDATE);
    
    		render();
    	}
    }

The above loop will continue while the game window has not been closed. Inside the loop,
we call `clock.restart()` which does two things - it resets the clock and returns the delta time (`dt`), which tells us how much time has passed since the last frame.
The delta time is accumulated into a variable called `lag`. 
We then process any key or mouse events by calling `processEvents()`.
The inner while loop references a constant called `MS_PER_UPDATE` - this is defined as 10ms and represents a notional amount of time we set aside for one update cycle. On a fast computer, this inner loop may not execute for a particular frame, because one update cycle is done in less than 10ms. In this scenario, we get exactly one update and one render (eventually lag will be > `MS_PER_UPDATE` as it accumulates the delta time).
On a slow computer, `lag` may well be > `MS_PER_UPDATE` most frames. In this scenario, we get multiple updates for each render operation.

**1.2 The SFML event loop**

The next member function is `Game::processEvents()`

    void Game::processEvents()
    {
    	sf::Event event;
    	while (m_window.pollEvent(event))
    	{
    		if (event.type == sf::Event::Closed)
    		{
    			m_window.close();
    		}
    		processGameEvents(event);
    	}
    }

Note that SFML stores events internally in a queue structure. The method:

    app.pollEvent(event)

pops (removes) the next event from the queue and stores it in the `event` variable. This method will return `false` when there are no more events available in the queue, thus causing the loop to exit. Events are identified by the `sf::Event::EventType` enum (enumeration). So, for example, `sf::Event::Closed` signifies a window closed event. Likewise, `sf::Event::KeyPressed` signifies a key pressed event. 
The above member function simply checks if we have a window close event (because the user clicked the close window button) and then passes any events to another member function `processGameEvents()`.

    void Game::processGameEvents(sf::Event& event)
    {
    	// check if the event is a a mouse button release
    	if (sf::Event::KeyPressed == event.type)
    	{
    		switch (event.key.code)
    		{
    		case sf::Keyboard::Escape:
    			m_window.close();
    			break;
    		case sf::Keyboard::Up:
    			// Up key was pressed...
    			break;
    		default:
    			break;
    		}
    	}
    }

This function is where we can handle all key and mouse input. Looking more closely at this:

    switch (event.key.code)

code is an enum of type `sf::Keyboard::Key`, and this enum is turn is defined inside a struct called `KeyEvent`, where `key` in an instance of `KeyEvent`.

Thus, the switch statement interrogates the code variable to determine which key was pressed (in this example, we exit if the Escape key is pressed). 

**1.3 Game updates and rendering**

The last two member functions are where we handle the game updates and the game rendering:


    void Game::update(double dt)
    {
    	
    }
    
    
    void Game::render()
    {
    	m_window.clear(sf::Color(0, 0, 0, 0));

    	// Draw sprites etc. here using m_window.draw()...

		// Now display on-screen everthing that has been rendered to the SFML window.

    	m_window.display();
    }


Note our render function clears the screen to black and displays the contents of whatever `draw()` calls we have made to the SFML window on-screen. We haven't drawn anything yet so the screen will stay black.

**Exercise 1 - Drawing a sprite.**

Open Game.h and add a member variable of type Sprite:

    sf::Sprite m_sprite;

In Game.cpp, inside the constructor function, add the following code:

	    sf::Texture myTexture;
    	if (!myTexture.loadFromFile("E-100.png"))
    	{
    		std::string s("Error loading texture");
    		throw std::exception(s.c_str());
    	}
    	
    	m_sprite.setTexture(myTexture);

Finally, don't forget to draw the sprite inside the `render()` function. 
What happens? Can you explain the result? Fix the problem before continuing to exercise 2.

**Exercise 2 - Setting the sprite origin.**

By default the origin of the sprite is set to the top left corner. Set the origin of the sprite to it's centre point. Where is the sprite now drawn? Can you explain why part of the sprite is missing?

**Exercise 3 - Rotating a sprite.**

Draw the sprite anywhere so it is fully visible (i.e. translate the sprite somewhere). Rotate the sprite by 90 degrees. Which direction has the tank rotated (clockwise or anti-clockwise)?
By default, in SFML, 0° corresponds to "right", i.e. along the positive x-axis. This means our tank sprite should face straight down the positive y-axis when rotated 90°. How can this be fixed?

Finally, be sure to read the SFML tutorial on Sprites [here](http://www.sfml-dev.org/tutorials/2.0/graphics-sprite.php) 

  








 


