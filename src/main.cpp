#include <wex/Game.hpp>

class MyApp final : public wex::Driver {
	void update([[maybe_unused]] double dt){};
	void draw([[maybe_unused]] sf::RenderWindow window){};
};

int main() {
	wex::dryRun<MyApp>();
	return 0;
}
