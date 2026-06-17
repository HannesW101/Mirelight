#pragma once

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Class Walkable_provider
// ----------------------------------------------------------------------------

class Walkable_provider {

public:
    virtual ~Walkable_provider() = default;

    virtual bool is_walkable(int world_tx, int world_ty) const = 0;
};

} // namespace mirelight
