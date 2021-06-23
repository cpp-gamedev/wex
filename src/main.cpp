#include <iostream>
#include <wex/Engine.hpp>

class MyApp final : public wex::Game {
	private:
	wex::Circle mCircle;

	public:
	void init() override {
		mCircle = g->circle(100, 100, 30);
		mCircle.setFillColor(sf::Color::Blue);
	}

	void update([[maybe_unused]] double dt) override {}

	void draw() override {
		g->draw(mCircle);
	}
};

int main() {
	wex::dryRun<MyApp>();
	return 0;
}
