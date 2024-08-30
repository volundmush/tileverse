#pragma once

// Global C++ std library includes
#include <string>
#include <string_view>

extern std::string_view intern(const std::string& str);


class Tile;
class Chunk;
class Field;

class Tile {
public:
    static void init();
    Tile();
    ~Tile();

    std::string_view getTerrainType() const;
    std::string_view getRoofType() const;
    std::string_view getFloorType() const;

    void setTerrainType(std::string_view type);
    void setRoofType(std::string_view type);
    void setFloorType(std::string_view type);
};

class Chunk {
public:
    Chunk(int size);
    ~Chunk();

    Tile* getTile(int x, int y);
    int getChunkSize() const;
};

class Field {
public:
    Field(std::string_view name, int chunkSize, int chunksWidth, int chunksHeight);
    ~Field();

    std::string_view getName() const;
    int getChunkSize() const;
    int getChunksWidth() const;
    int getChunksHeight() const;
    
    Chunk* getChunk(int x, int y);
    Tile* getTile(int x, int y, int chunkX, int chunkY);
};