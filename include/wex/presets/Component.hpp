#include "../Common.hpp"
#include <SFML/System/Vector2.hpp>

namespace wex {

/// \brief A component represents a bag of data.
/// A component by itself has no meaning, and is useful to describe properties or attributes
/// of a `wex::GameObject`.
/// Extend this class to use custom components.
struct Component {
  public:
	Component()					= default;
	Component(Component&&)		= default;
	Component(Component const&) = default;

	Component& operator=(Component&&) = default;
	Component& operator=(Component const&) = default;

	virtual ~Component() = default;
};

/// TODO: Since a component wrapping a vector2f struct can have lots of different uses,
/// it could be useful to give this a more general purpose name.
struct CVelocity : Component {
	CVelocity() = delete;
	CVelocity(float x, float y) : vel{x, y} {}
	sf::Vector2f vel;
};

}; // namespace wex
