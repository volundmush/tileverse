#include "tileverse/Utils.hpp"

std::vector<std::string> printTileGrid(const std::vector<std::vector<Tile*>> tiles) {
    std::vector<std::string> result;
    result.reserve(tiles.size());
    for (auto row : tiles) {
        std::string rowString;
        rowString.reserve(row.size());
        for (auto tile : row) {
            if(tile) {
                auto ter = tile->getTerrainType();
                if(ter.size() > 0) {
                    rowString += ter.at(0);
                }
                else {
                    rowString += "T";
                }
            }
            else {
                rowString += " ";
                continue;
            }
        }
        result.push_back(rowString);
    }
    return result;
}