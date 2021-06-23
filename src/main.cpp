#include <iostream>
#include <wex/Engine.hpp>

class MyApp final : public wex::Game {
	void update([[maybe_unused]] double dt) override {}
	void draw(wex::GraphicsController&) override {}
};

int main() {
	wex::dryRun<MyApp>();
	return 0;
}
