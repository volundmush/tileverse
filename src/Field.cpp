#include "tileverse/Prelude.hpp"


Field::Field(std::string_view name, int chunkSize) : name(name), chunkSize(chunkSize) {
    
}

Chunk* Field::getChunk(int x, int y, bool create) {
    auto p = Point(x, y);
    if (auto f = chunks.find(p); f != chunks.end()) {
        return &f->second;
    }
    if(!create) return nullptr;
    auto emplaced = chunks.emplace(p, chunkSize);
    return &emplaced.first->second;
}


Tile* Field::getTile(int x, int y, bool create) {
    // Calculate both the quotient (chunk coordinates) and remainder (tile coordinates within the chunk)
    auto divX = std::div(x, chunkSize);
    auto divY = std::div(y, chunkSize);

    int chunkX = divX.quot;  // chunkX is the quotient of x / chunkSize
    int chunkY = divY.quot;  // chunkY is the quotient of y / chunkSize

    if(auto chunk = getChunk(chunkX, chunkY, create); chunk) {
        int tileX = divX.rem;  // tileX is the remainder of x % chunkSize
        int tileY = divY.rem;  // tileY is the remainder of y % chunkSize

        // Calculate the center of the chunk in array coordinates
        int center = chunkSize / 2;

        // Convert Cartesian tile coordinates to array indices
        int idxX = tileX + center;
        int idxY = tileY + center;

        return chunk->getTile(idxX, idxY);
    }

    return nullptr;  // Return nullptr if the chunk doesn't exist
}


std::vector<std::vector<Tile*>> Field::getTiles(int x, int y, int width, int height) {
    // Ensure width and height are odd
    if (width % 2 == 0 || height % 2 == 0) {
        throw std::invalid_argument("Width and height must be odd.");
    }

    // Create the result vector with the given width and height
    std::vector<std::vector<Tile*>> result;
    result.reserve(height);

    // Calculate the top-left corner of the desired area
    int startX = x - width / 2;
    int startY = y + height / 2;  // Adjusted to start from the top
    int endX = startX + width;
    int endY = startY - height;   // Adjusted to correctly iterate downwards

    // Loop over the area and fill the result vector
    for (int curY = startY; curY > endY; curY--) {
        auto &row = result.emplace_back();
        row.reserve(width);
        for (int curX = startX; curX < endX; curX++) {
            auto tile = getTile(curX, curY);
            row.push_back(tile);
        }
    }

    return result;
}