#include "SFML/System/Vector2.hpp"
#include "wex/Forward.hpp"
#include <iostream>
#include <wex/Engine.hpp>
#include <wex/presets/GameObject.hpp>

template <typename T>
struct Shape : wex::Component {
	T shape;
	Shape(T&& shape_) : shape(std::move(shape_)) {
		static_assert(std::is_base_of_v<sf::Shape, T>);
	}
};

using CCircleShape = Shape<wex::Circle>;

class Ball : public wex::GameObject {
  public:
	Ball() {
		this->give<wex::CVelocity>(0.17, 0.17);
		auto circle = wex::Circle(50);
		circle.setPosition(0, 0);
		this->give<CCircleShape>(std::move(circle));
	}

	void onUpdate(double dt) override {
		sf::Vector2f const& vel = this->get<wex::CVelocity>()->vel * float(dt);
		auto& shape				= this->get<CCircleShape>()->shape;
		shape.setPosition(shape.getPosition() + vel);
	}

	void onDraw(wex::GraphicsController& g) {
		g.draw(this->get<CCircleShape>()->shape);
	}
};

class MyApp final : public wex::Game {
  private:
	Ball ball;

  public:
	void init() override {}

	void update(double dt) override {
		ball.onUpdate(dt);
	}

	void draw() override {
		ball.onDraw(*g);
	}
};

int main() {
	wex::dryRun<MyApp>();
	return 0;
}
