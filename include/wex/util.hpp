#pragma once
#include "Common.hpp"
#include <cstddef>

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

#define WEX_ENSURE(cond) ((cond) ? (void(0)) : std::terminate())

/// \brief An observing pointer that holds a resource and ensures that the pointer it holds
/// is never `nullptr`.
template <typename T>
class NotNullPtr {
  public:
	NotNullPtr()				   = delete;
	NotNullPtr(std::nullptr_t ptr) = delete;

	constexpr NotNullPtr(T* ptr) : mPtr(ptr) {
		WEX_ENSURE(ptr != nullptr);
	}

	// NotNullPtrs can be constructed from other NotNullPtrs

	NotNullPtr<T>& operator=(NotNullPtr<T> const&) = default;
	NotNullPtr<T>& operator=(NotNullPtr<T>&&) = default;

	NotNullPtr(NotNullPtr<T> const&) = default;
	NotNullPtr(NotNullPtr<T>&&)		 = default;

	/// \brief Get a raw pointer to the resource held by this NotNullPtr
	constexpr T* get() {
		return mPtr;
	}

	/// \brief Get a raw `const` pointer to the resource held by this NotNullPtr
	constexpr T const* get() const {
		return mPtr;
	}

	constexpr auto operator->() const {
		WEX_ENSURE(get() != nullptr);
		return get();
	}

	constexpr auto operator*() const {
		WEX_ENSURE(get() != nullptr);
		return *get();
	}

	NotNullPtr<T> operator=(T* ptr) {
		WEX_ENSURE(ptr != nullptr);
		mPtr = ptr;
		return *this;
	}

	NotNullPtr<T> operator=(std::nullptr_t ptr) = delete;

  private:
	T* mPtr;
};

} // namespace wex::util
