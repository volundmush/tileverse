#include "tileverse/Tile.hpp"

static std::string_view defaultTerrainType;
static std::string_view defaultRoofType;
static std::string_view defaultFloorType;


void Tile::init() {
    defaultTerrainType = intern("grass");
    defaultRoofType = intern("none");
    defaultFloorType = intern("none");
}


Tile::Tile() {
    terrainType = defaultTerrainType;
    roofType = defaultRoofType;
    floorType = defaultFloorType;
}