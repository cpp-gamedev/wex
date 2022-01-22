#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Mouse.hpp"
#include "wex/Forward.hpp"
#include "wex/Input.hpp"
#include <cstdint>
#include <iostream>
#include <wex/Engine.hpp>
#include <wex/presets/GameObject.hpp>

using Vec2 = sf::Vector2f;

template <typename T>
struct Shape : wex::Component {
	T shape;

	Shape(T const& shape_) : shape(shape_) {
		static_assert(std::is_base_of_v<sf::Shape, T>);
	}

	void setPosition(Vec2 const& pos) noexcept {
		shape.setPosition(pos);
	}

	Vec2 const& getPosition() const noexcept {
		return shape.getPosition();
	}

	float x() const noexcept {
		return shape.getPosition().x;
	}

	float y() const noexcept {
		return shape.getPosition().y;
	}

	void move(float dx, float dy) {
		shape.move(dx, dy);
	}
};

using CCircleShape = Shape<wex::Circle>;
using CRectShape   = Shape<sf::RectangleShape>;

class Ball : public wex::GameObject {
  public:
	static constexpr size_t Radius = 30;

	Ball() {
		this->give<wex::CVelocity>(0.17f, 0.1f);

		// wex.circle(0, 0, Radius)
		wex::Circle circle(Radius);
		circle.setPosition(0, 0);
		circle.setOrigin(Radius, Radius);
		this->give<CCircleShape>(circle);
	}

	void onUpdate(double dt) override {
		Vec2 const& vel		= this->get<wex::CVelocity>().vel * float(dt);
		CCircleShape& shape = this->get<CCircleShape>();
		Vec2 const& pos		= shape.getPosition();
		shape.setPosition(pos + vel);
	}

	void onDraw(wex::GraphicsController& g) {
		g.draw(this->get<CCircleShape>().shape);
	}

	void moveTo(float x, float y) noexcept {
		this->get<CCircleShape>().setPosition({x, y});
	}
};

class Paddle : public wex::GameObject {
  public:
	static constexpr float Width  = 30;
	static constexpr float Height = 150;
	static constexpr float YSpeed = 5.5;

	Paddle() = delete;

	Paddle(Vec2 const& pos) {
		Vec2 size{Width, Height};
		sf::RectangleShape rect{size};
		auto* rectShape = this->give<CRectShape>(rect);
		rectShape->setPosition(pos);
	}

	void onDraw(wex::GraphicsController& g) {
		g.draw(this->get<CRectShape>().shape);
	}

	void moveHorx(float const dy) {
		CRectShape& shape = this->get<CRectShape>();
		shape.move(0, dy);
	}
};

constexpr auto WinWidth	 = wex::WindowConfig::DefaultWidth;
constexpr auto WinHeight = wex::WindowConfig::DefaultHeight;

class MyApp final : public wex::Game {
  private:
	Ball ball;
	Paddle leftPaddle{{0, WinHeight / 2.0f}};
	Paddle rightPaddle{{WinWidth - Paddle::Width, WinHeight / 2.0f}};
	wex::InputState const* mInput = nullptr;

  public:
	void init() override {
		float winWidth	= g->mWindowDims.x;
		float winHeight = g->mWindowDims.y;
		ball.moveTo(winWidth / 2, winHeight / 2);
		mInput = &engine->inputState();
	}

	void update(double dt) override {
		ball.onUpdate(dt);

		if (mInput->isKeyHeld(wex::Kbd::W))
			leftPaddle.moveHorx(-Paddle::YSpeed);
		if (mInput->isKeyHeld(wex::Kbd::S))
			leftPaddle.moveHorx(Paddle::YSpeed);

		if (mInput->isKeyHeld(wex::Kbd::Up))
			rightPaddle.moveHorx(-Paddle::YSpeed);
		if (mInput->isKeyHeld(wex::Kbd::Down))
			rightPaddle.moveHorx(Paddle::YSpeed);

		auto const& bShape = ball.get<CCircleShape>().shape;
		auto const& lShape = leftPaddle.get<CRectShape>().shape;
		auto const& rShape = rightPaddle.get<CRectShape>().shape;

		Vec2 const& bPos = bShape.getPosition();
		Vec2& bVel		 = ball.get<wex::CVelocity>().vel;
		if (bPos.x <= Ball::Radius or bPos.x >= WinWidth - Ball::Radius) {
			bVel.x *= -1;
		}

		if (bPos.y <= Ball::Radius or bPos.y >= WinHeight - Ball::Radius) {
			bVel.y *= -1;
		}

		if (bShape.getGlobalBounds().intersects(lShape.getGlobalBounds()) or
			bShape.getGlobalBounds().intersects(rShape.getGlobalBounds())) {
			bVel.x *= -1;
			bVel.y *= -1;
		}
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
