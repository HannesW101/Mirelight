#ifndef ANIMATIONS_ANIMATION_MANAGER
#define ANIMATIONS_ANIMATION_MANAGER

// ===========================================================================
// Includes
// ---------------------------------------------------------------------------

#include "animations/animation_defs.h"

// ===========================================================================
// Namespaces
// ---------------------------------------------------------------------------

namespace mirelight::animations {

// ===========================================================================
// Class Animation_manager
// ---------------------------------------------------------------------------

class Animation_manager final {

public:
    static Animation_manager const& get_instance();

    ~Animation_manager          (                        ) = default;
    Animation_manager           (Animation_manager const&) = delete;
    Animation_manager& operator=(Animation_manager const&) = delete;
    Animation_manager           (Animation_manager&&     ) = delete;
    Animation_manager& operator=(Animation_manager&&     ) = delete;

private:

    bool _is_init;
};

} // namespace mirelight::animations

#endif
