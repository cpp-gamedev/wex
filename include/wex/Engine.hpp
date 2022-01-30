#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <memory>
#include <string>

#include "Common.hpp"
#include "GraphicsController.hpp"
#include "Input.hpp"
#include "util.hpp"


namespace wex {

class Game {
	friend Engine;

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
	virtual void draw() = 0;

	virtual ~Game() = default;

	inline void setGraphicsController(GraphicsController& controller) noexcept {
		this->g = &controller;
	}

	[[nodiscard]] inline GraphicsController const& graphicsController() const noexcept {
		assert(this->g != nullptr);
		return *this->g;
	}

	inline void setEngine(Engine& engine) noexcept {
		this->engine = &engine;
	}

  protected:
	/// \brief An observing pointer to the Engine's GraphicsController that can be used to draw to
	/// the window.
	GraphicsController* g = nullptr;
	Engine* engine		  = nullptr;
};

struct Config {
	WindowConfig window;
};

/// \brief The engine owns a game (wex::Game) and exposes necessary functionality like input, graphics etc.
/// to the game.
class Engine final : util::Pinned {

	/// \brief Exit code for the game engine.
	enum class Status { ok };

  public:
	Engine()  = delete;
	~Engine() = default;

	explicit Engine(std::unique_ptr<Game>&& game, Config const& config = Config())
		: mConfig(std::move(config)), mGame(std::move(game)) {
		mGame->setGraphicsController(mGraphics);
		mGame->setEngine(*this);
	}

	/// \brief Intialize the window and start the game loop.
	/// \return The status code for the game. Returns Status::ok if the game starts and quits
	///			successfully.
	Status run();

	inline InputState const& inputState() const noexcept {
		return mInputState;
	}

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
	InputState mInputState;
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
