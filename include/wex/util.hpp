#pragma once
#include "common.hpp"

namespace wex::util {

/// \brief A deriv-able base class that makes all deriving classes
/// non-movable and non-copyable.
class Pinned {
	Pinned(Pinned&&)	  = delete;
	Pinned(Pinned const&) = delete;
	Pinned(Pinned&)		  = delete;

  public:
	Pinned() = default;
};

} // namespace wex::util
