#include "DungeonGenerator.h"
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

DungeonGenerator::DungeonGenerator(int width, int height, int minRoom, int maxRoom, int depth)
    : mapWidth(width), mapHeight(height),
    minRoomSize(minRoom), maxRoomSize(maxRoom), maxDepth(depth) {
}

void DungeonGenerator::generateDungeon() {
    vector<vector<TileType>> map(mapHeight, vector<TileType>(mapWidth, WALL));
    mt19937 rng(static_cast<unsigned int>(9));//34an el seed

    BSPNode::minRoomSize = minRoomSize;
    BSPNode::maxRoomSize = maxRoomSize;
    BSPNode::mapWidth = mapWidth;
    BSPNode::mapHeight = mapHeight;

    BSPNode root(0, 0, mapWidth, mapHeight);

    vector<BSPNode*> nodes;
    nodes.push_back(&root);

    for (int i = 0; i < maxDepth; ++i) {
        vector<BSPNode*> newNodes;
        for (auto node : nodes) {
            if (node->split(rng)) {
                newNodes.push_back(node->left);
                newNodes.push_back(node->right);
            }
        }
        if (newNodes.empty()) break;
        nodes = newNodes;
    }

    root.createRooms(rng);

    for (auto node : nodes) {
        if (node->isLeaf()) {
            carveRoom(map, node->room);
        }
    }

    root.connectRooms(map, rng);

    for (const auto& row : map) {
        for (const auto& tile : row) {
            cout << (tile == WALL ? '#' : '.');
        }
        cout << '\n';
    }
}

void DungeonGenerator::carveRoom(vector<vector<TileType>>& map, const Rect& room) {
    for (int y = room.y; y < room.y + room.height; ++y) {
        for (int x = room.x; x < room.x + room.width; ++x) {
            if (y >= 0 && y < mapHeight && x >= 0 && x < mapWidth) {
                map[y][x] = FLOOR;
            }
        }
    }
}