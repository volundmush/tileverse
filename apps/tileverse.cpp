#include "tileverse/Prelude.hpp"
#include "tileverse/Utils.hpp"
#include <boost/algorithm/string.hpp>
#include <iostream>

int main() {

    auto fieldName = intern("test field");
    Tile::init();
    Field field(fieldName, 15);
    
    auto tile = field.getTile(0, 0, true);
    tile->setTerrainType(intern("lava"));

    auto t2 = field.getTile(-1,-1, false);
    if(t2) {
        t2->setTerrainType(intern("water"));
    }

    auto tiles = field.getTiles(0,0,9,9);

    for(const auto row : printTileGrid(tiles)) {
        std::cout << row << std::endl;
    }

    return 0;
}