#ifndef DUNGEONGENERATOR_H
#define DUNGEONGENERATOR_H

#include "dungeonV1.h"
#include "BSPNode.h"
#include "vector.hpp"
using namespace std;

class DungeonGenerator : public Dungeon {
public:
    DungeonGenerator(int width, int height, int minRoom, int maxRoom, int depth);
    void generateDungeon() override;

private:
    int mapWidth;
    int mapHeight;
    int minRoomSize;
    int maxRoomSize;
    int maxDepth;
    void carveRoom(std::vector<std::vector<TileType>>& map, const Rect& room);
};

#endif