#pragma once

// Global C++ std library includes
#include <string>
#include <string_view>
#include <functional>
#include <stdexcept>

extern std::string_view intern(const std::string& str);

class Point {
public:
    Point(int x, int y);

    int getX() const;
    int getY() const;

    bool operator==(const Point& other) const;
private:
    int x;
    int y;
};

namespace std {
    template <>
    struct hash<Point> {
        std::size_t operator()(const Point& point) const noexcept {
            std::size_t h1 = std::hash<int>{}(point.getX());
            std::size_t h2 = std::hash<int>{}(point.getY());
            return h1 ^ (h2 << 1);
        }
    };
}


class Tile;
class Chunk;
class Field;

class Tile {
public:
    static void init();
    Tile();

    std::string_view getTerrainType() const;
    std::string_view getRoofType() const;
    std::string_view getFloorType() const;

    void setTerrainType(std::string_view type);
    void setRoofType(std::string_view type);
    void setFloorType(std::string_view type);
private:
    std::string_view terrainType;
    std::string_view roofType;
    std::string_view floorType;
};


class Chunk {
public:
    Chunk(int size);

    Tile* getTile(int x, int y);
    int getChunkSize() const;
protected:
    int size; // size MUST be odd.
    std::vector<std::vector<Tile>> tiles;
};


class Field {
public:
    Field(std::string_view name, int chunkSize);

    std::string_view getName() const;
    int getChunkSize() const;
    int getChunksWidth() const;
    int getChunksHeight() const;
    
    Chunk* getChunk(int x, int y, bool create = false);
    Tile* getTile(int x, int y, bool create = false);

    std::vector<std::vector<Tile*>> getTiles(int x, int y, int width, int height);

private:
    std::string_view name;
    int chunkSize;
    std::unordered_map<Point, Chunk> chunks;
};