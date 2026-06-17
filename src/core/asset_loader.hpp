#pragma once

// ============================================================================
// Includes
// ----------------------------------------------------------------------------

#include <memory>
#include <string>
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

    void _load_fonts   (std::string const& dir);
    void _load_textures(std::string const& dir);
    void _load_anims   (std::string const& dir);
    void _load_sfx     (std::string const& dir);
    void _load_music   (std::string const& dir);

    void _tex(std::string const& dir, char const* key, char const* rel_path);

    void _anim(std::string const& dir, char const* key, char const* rel_path);
};

} // namespace mirelight
