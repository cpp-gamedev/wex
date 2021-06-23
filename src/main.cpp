#include <iostream>
#include <wex/Engine.hpp>


class MyApp final : public wex::Driver {
	void update([[maybe_unused]] double dt) override{};
	void draw() override{};
};

int main() {
	wex::dryRun<MyApp>();
	return 0;
}
