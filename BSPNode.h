#ifndef BSPNODE_H
#define BSPNODE_H

#include "dungeonV1.h"
#include <random>
#include "vector.hpp"
using namespace std;

enum TileType {
    WALL,
    FLOOR
};

class Rect {
public:
    int x, y, width, height;

    Rect(int x = 0, int y = 0, int width = 0, int height = 0);
    bool isValid() const;
};

class BSPNode {
public:
    static int minRoomSize;
    static int maxRoomSize;
    static int mapWidth;
    static int mapHeight;

    Rect region;
    Rect room;
    BSPNode* left;
    BSPNode* right;

    BSPNode(int x, int y, int width, int height);
    ~BSPNode();

    bool isLeaf() const;
    bool split(std::mt19937& rng);
    void createRooms(std::mt19937& rng);
    void connectRooms(std::vector<std::vector<TileType>>& map, std::mt19937& rng);
    Rect getRoom() const;

private:
    void carveHorizontalCorridor(std::vector<std::vector<TileType>>& map, int x1, int x2, int y);
    void carveVerticalCorridor(std::vector<std::vector<TileType>>& map, int y1, int y2, int x);
};

#endif