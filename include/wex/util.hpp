#pragma once
#include "Common.hpp"
#include <cstddef>
#include <cassert>

namespace wex::util {

/// \brief A deriv-able base class that makes all deriving classes
/// non-movable and non-copyable.
class Pinned {
	Pinned(Pinned&&)	  = delete;
	Pinned(Pinned const&) = delete;
	Pinned(Pinned&)		  = delete;

	Pinned operator=(Pinned&&) = delete;
	Pinned operator=(Pinned const&) = delete;

  public:
	Pinned() = default;
};

/// \brief An observing pointer that holds a resource and ensures that the pointer it holds
/// is never `nullptr`. If the resource is `nullptr` while this pointer is in use, it will
/// terminate the application. Note that this only works in debug builds.
template <typename T>
class NotNullPtr {
  public:
	NotNullPtr()				   = delete;
	NotNullPtr(std::nullptr_t ptr) = delete;

	constexpr NotNullPtr(T* ptr) : mPtr(ptr) {
		assert(ptr != nullptr);
	}

	// NotNullPtrs can be constructed from other NotNullPtrs

	NotNullPtr<T>& operator=(NotNullPtr<T> const&) = default;
	NotNullPtr<T>& operator=(NotNullPtr<T>&&) = default;

	NotNullPtr(NotNullPtr<T> const&) = default;
	NotNullPtr(NotNullPtr<T>&&)		 = default;

	/// \brief Get a raw pointer to the resource held by this NotNullPtr
	[[nodiscard]] constexpr T* get() {
		assert(mPtr != nullptr);
		return mPtr;
	}

	/// \brief Get a raw `const` pointer to the resource held by this NotNullPtr
	[[nodiscard]] constexpr T const* get() const {
		assert(mPtr != nullptr);
		return mPtr;
	}

	[[nodiscard]] constexpr auto operator->() const {
		T* ptr = get();
		assert(ptr != nullptr);
		return ptr;
	}

	[[nodiscard]] constexpr auto operator*() const {
		T* ptr = get();
		assert(ptr != nullptr);
		return *ptr;
	}

	NotNullPtr<T> operator=(T* ptr) {
		assert(ptr != nullptr);
		mPtr = ptr;
		return *this;
	}

	NotNullPtr<T> operator=(std::nullptr_t ptr) = delete;

  private:
	T* mPtr;
};

} // namespace wex::util
