#include "../Common.hpp"
#include "../Engine.hpp"
#include "../util.hpp"
#include "Component.hpp"
#include <cstddef>
#include <vector>

namespace wex {

/// \brief The game game object class. A game object is a bag of components with an
/// `onUpdate` method that is called once per iteration of the game loop.
class GameObject {
	std::vector<std::unique_ptr<Component>> mComponents;

  public:
	GameObject() = default;

	/// \brief called on every 'update' call to the parent engine
	virtual void onUpdate([[maybe_unused]] double dt) {}

	template <typename T>
	[[nodiscard]] T* find() const noexcept {
		static_assert(std::is_base_of_v<Component, T>);
		/// TODO: optimize this O(n) lookup
		for (auto const& compPtr : mComponents) {
			auto comp = dynamic_cast<T*>(compPtr.get());
			if (comp != nullptr) return comp;
		}
		return nullptr;
	}

	template <typename T>
	[[nodiscard]] T& get() const {
		T* const comp_ptr = find<T>();
		assert(comp_ptr != nullptr);
		return *comp_ptr;
	}

	template <typename T, typename... Args>
	T* give(Args&&... args) {
		static_assert(std::is_base_of_v<Component, T>, "T does not derive from wex::Component");
		auto compPtr = std::make_unique<T>(std::forward<Args>(args)...);
		mComponents.push_back(std::move(compPtr));
		return static_cast<T*>(mComponents.back().get());
	}

	virtual ~GameObject() = default;
};

} // namespace wex
