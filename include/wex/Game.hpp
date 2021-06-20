#pragma once
#include <SFML/System/Vector2.hpp>
#include <string>
#include <wex/common.hpp>

namespace wex {

class Driver {
  public:
	virtual void update(double dt) = 0;
	virtual void draw()			   = 0;
};

class Game final {
  public:
	Game()			  = delete;
	Game(Game&&)	  = delete;
	Game(Game const&) = delete;
	Game(Game&)		  = delete;
	~Game()			  = default;

	explicit Game(std::unique_ptr<Driver>&& driver) : mDriver(std::move(driver)){};

	void run();

  private:
	void loop();

  public:
	static constexpr size_t DefaultWinWidth	  = 800;
	static constexpr size_t DefaultWinHeight  = 600;
	static constexpr double DefaultFPS		  = 60.0f;
	static constexpr const char* DefaultTitle = "Wex Game";

	const float mFps = DefaultFPS;
	const std::string mWindowTitle{DefaultTitle};
	const sf::Vector2u mWindowDim{DefaultWinWidth, DefaultWinHeight};

  private:
	std::unique_ptr<Driver> mDriver;
};

template <typename T, typename... Args> void dryRun(Args&&... args) {
	static_assert(!std::is_abstract_v<T> and std::is_base_of_v<Driver, T>,
				  "T must be a concrete class deriving from wex::Driver.");
	auto driver_ptr = std::unique_ptr<T>(std::forward<Args>(args)...);
	Game game(std::move(driver_ptr));
	game.run();
}

} // namespace wex
