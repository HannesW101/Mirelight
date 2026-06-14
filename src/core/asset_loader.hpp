#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include <memory>
#include <vector>

// ============================================================================
// Forward declarations
// ----------------------------------------------------------------------------

namespace titan::resources { class Resource_manager; }

// ============================================================================
// Namespaces
// ----------------------------------------------------------------------------

namespace mirelight {

// ============================================================================
// Class Asset_loader
// ----------------------------------------------------------------------------

class Asset_loader {

public:
    explicit Asset_loader(titan::resources::Resource_manager& resources);

    bool load_all();

private:
    titan::resources::Resource_manager& _resources;
    std::vector<std::shared_ptr<void>>  _handles;
};

} // namespace mirelight
