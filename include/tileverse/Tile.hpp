#pragma once

#include "Prelude.hpp"

class Tile {
    protected:
        std::string_view terrainType;
        std::string_view roofType;
        std::string_view floorType;
};