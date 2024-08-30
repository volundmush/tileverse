#include "tileverse/Prelude.hpp"

Chunk::Chunk(int size) : size(size), tiles(size, std::vector<Tile>(size)) {

}

Tile* Chunk::getTile(int x, int y) {
    if (x < 0 || x >= size || y < 0 || y >= size) {
        return nullptr;
    }
    return &tiles[y][x];
}

int Chunk::getChunkSize() const {
    return size;
}