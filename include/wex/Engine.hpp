#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <string>

#include "GraphicsController.hpp"
#include "common.hpp"
#include "util.hpp"

namespace wex {

class Game {
  public:
	/// \brief Intialize the game state. This function is called once
	/// before the core game loop is started. By default, it does nothing
	/// and needs to be overriden by the user for providing meaningful
	/// behavior.
	virtual void init() {}

	/// \brief The update function runs several times a second and is called in a way
	/// such that it's independ of the frame rate. This function is ideal for updating
	/// the state of the game every tick.
	virtual void update(double dt) = 0;

	/// \brief The draw function is resposible for rendering everything that is visible
	/// on the screen.
	/// \param graphics A Graphics Controller that belongs to the engine. the controller contains
	///	       member functions that can help draw shapes, lines and images to the screen.
	virtual void draw(GraphicsController& graphics) = 0;

	virtual ~Game() = default;
};

struct Config {
	WindowConfig window;
	Config() = default;
};

class Engine final : util::Pinned {

	/// \brief Exit code for the game engine.
	enum class Status { ok };

  public:
	~Engine() = default;

	explicit Engine(std::unique_ptr<Game>&& game, Config const& config = Config())
		: mConfig(std::move(config)), mGame(std::move(game)) {}

	/// \brief Intialize the window and start the game loop.
	/// \return The status code for the game. Returns Status::ok if the game starts and quits
	///			successfully.
	Status run();

  private:
	/// \brief The core game loop. calls `game.update` and `game.draw`
	void loop();

	/// \brief polls events from the window until none are left and then
	/// registers those events.
	void handleEvents(sf::RenderWindow& window);

  public:
	Config mConfig;

  private:
	std::unique_ptr<Game> mGame;
	GraphicsController mGraphics{mConfig.window};
};

/// \brief Do a quick run of a game with the default configurations
///        (Window dimensions, Window title etc)
template <typename T, typename... Args>
void dryRun(Args&&... args) {
	static_assert(!std::is_abstract_v<T> and std::is_base_of_v<Game, T>,
				  "T must be a concrete class deriving from wex::Driver.");
	auto driver_ptr = std::make_unique<T>(std::forward<Args>(args)...);
	Engine engine(std::move(driver_ptr));
	engine.run();
}

} // namespace wex