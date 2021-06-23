#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <string>
#include <wex/common.hpp>

namespace wex {

class Driver {
  public:
	virtual void update(double dt) = 0;
	virtual void draw()			   = 0;
	virtual ~Driver()			   = default;
};

struct Config {
	const u32 winWidth		   = 800;
	const u32 winHeight		   = 600;
	const double fps		   = 0;
	const std::string winTitle = "Wex Game";
};

class Engine final {

	/// \brief Exit code for the game engine.
	enum class Status { ok };

  public:
	Engine()			  = delete;
	Engine(Engine&&)	  = delete;
	Engine(Engine const&) = delete;
	~Engine()			  = default;

	explicit Engine(std::unique_ptr<Driver>&& driver, Config&& config = Config())
		: mConfig(std::move(config)), mDriver(std::move(driver)){};

	/// \brief Intialize the window and start the game loop.
	/// \return The status code for the game. Returns Status::ok if the game starts and quits
	///			successfully.
	Status run();

  private:
	/// \brief The core game loop. calls `game.update` and `game.draw`
	void loop(sf::RenderWindow& window);
	void handleEvents(sf::RenderWindow& window);

  public:
	const Config mConfig;
	const sf::Vector2u mWindowDim{mConfig.winWidth, mConfig.winHeight};

  private:
	std::unique_ptr<Driver> mDriver;
};

/// \brief Do a quick run of a game with the default configurations (Window dimensions, Window title
/// etc)
template <typename T, typename... Args>
void dryRun(Args&&... args) {
	static_assert(!std::is_abstract_v<T> and std::is_base_of_v<Driver, T>,
				  "T must be a concrete class deriving from wex::Driver.");
	auto driver_ptr = std::make_unique<T>(std::forward<Args>(args)...);
	Engine engine(std::move(driver_ptr));
	engine.run();
}

} // namespace wex
