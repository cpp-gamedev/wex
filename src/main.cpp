#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "wex/Forward.hpp"
#include <cstdint>
#include <iostream>
#include <wex/Engine.hpp>
#include <wex/presets/GameObject.hpp>

using Vec2 = sf::Vector2f;

template <typename T>
struct Shape : wex::Component {
	T shape;
	Shape(T&& shape_) : shape(std::move(shape_)) {
		static_assert(std::is_base_of_v<sf::Shape, T>);
	}

	void setPosition(Vec2 const& pos) noexcept {
		shape.setPosition(pos);
	}
};

using CCircleShape = Shape<wex::Circle>;
using CRectShape   = Shape<sf::RectangleShape>;

class Ball : public wex::GameObject {
  public:
	Ball() {
		this->give<wex::CVelocity>(0.17f, 0.0f);
		auto circle = wex::Circle(30);
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

	void moveTo(float x, float y) noexcept {
		this->get<CCircleShape>()->setPosition({x, y});
	}
};

class Paddle : wex::GameObject {
  public:
	static constexpr float Width  = 30;
	static constexpr float Height = 150;

	Paddle() = delete;

	Paddle(Vec2 const& pos) {
		Vec2 size{Width, Height};
		sf::RectangleShape rect{size};
		auto* rectShape = this->give<CRectShape>(rect);
		rectShape->setPosition(pos);
	}

	void onDraw(wex::GraphicsController& g) {
		g.draw(this->get<CRectShape>()->shape);
	}
};

constexpr auto WinWidth	 = wex::WindowConfig::DefaultWidth;
constexpr auto WinHeight = wex::WindowConfig::DefaultHeight;

class MyApp final : public wex::Game {
  private:
	Ball ball;
	Paddle leftPaddle{{0, WinHeight / 2.0f}};
	Paddle rightPaddle{{WinWidth - Paddle::Width, WinHeight / 2.0f}};

  public:
	void init() override {
		float winWidth	= g->mWindowDims.x;
		float winHeight = g->mWindowDims.y;
		ball.moveTo(winWidth / 2, winHeight / 2);
	}

	void update(double dt) override {
		ball.onUpdate(dt);
	}

	void draw() override {
		ball.onDraw(*g);
		leftPaddle.onDraw(*g);
		rightPaddle.onDraw(*g);
	}
};

int main() {
	wex::dryRun<MyApp>();
	return 0;
}
