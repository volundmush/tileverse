#include "tileverse/Prelude.hpp"

static std::string_view defaultTerrainType;
static std::string_view defaultRoofType;
static std::string_view defaultFloorType;

Point::Point(int x, int y) : x(x), y(y) {

}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}

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

std::string_view Tile::getTerrainType() const {
    return terrainType;
}

std::string_view Tile::getRoofType() const {
    return roofType;
}

std::string_view Tile::getFloorType() const {
    return floorType;
}

void Tile::setTerrainType(std::string_view type) {
    terrainType = type;
}

void Tile::setRoofType(std::string_view type) {
    roofType = type;
}

void Tile::setFloorType(std::string_view type) {
    floorType = type;
}