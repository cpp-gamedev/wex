#include "SFML/System/Vector2.hpp"
#include <iostream>
#include <wex/Engine.hpp>
#include <wex/presets/GameObject.hpp>

template <typename T>
struct Shape : wex::Component {
	T shape;
	Shape(T&& shape_) : shape(shape_) {
		static_assert(std::is_base_of_v<sf::Shape, T>);
	}
};

using CCircleShape = Shape<wex::Circle>;

class Ball : public wex::GameObject {
  public:
	Ball() {
		this->give<wex::CVelocity>(1, 1);
		auto circle = wex::Circle(50);
		circle.setPosition(0, 0);
		this->give<CCircleShape>(std::move(circle));
	}

	void onUpdate(double) override {
		sf::Vector2f const& vel = this->get<wex::CVelocity>()->vel;
		auto& shape				= this->get<CCircleShape>()->shape;
		shape.setPosition(shape.getPosition() + vel);
	}
};

class MyApp final : public wex::Game {
  private:
	Ball ball;

  public:
	void init() override {}

	void update([[maybe_unused]] double dt) override {
		ball.onUpdate(dt);
	}

	void draw() override {
		g->draw(ball.get<CCircleShape>()->shape);
	}
};

int main() {
	wex::dryRun<MyApp>();
	return 0;
}
