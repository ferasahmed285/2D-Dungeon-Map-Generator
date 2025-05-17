#include "BSPNode.h"
using namespace std;

int BSPNode::minRoomSize;
int BSPNode::maxRoomSize;
int BSPNode::mapWidth;
int BSPNode::mapHeight;

Rect::Rect(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height) {
}

bool Rect::isValid() const {
    return width > 0 && height > 0;
}

BSPNode::BSPNode(int x, int y, int width, int height)
    : region(x, y, width, height), left(nullptr), right(nullptr) {
}

BSPNode::~BSPNode() {
    delete left;
    delete right;
}

bool BSPNode::isLeaf() const {
    return left == nullptr && right == nullptr;
}

bool BSPNode::split(mt19937& rng) {
    if (!isLeaf()) return false;

    uniform_int_distribution<int> distSplit(0, 1);
    bool splitH = (distSplit(rng) == 0);

    if (splitH) {
        if (region.height < 2 * minRoomSize) {
            if (region.width < 2 * minRoomSize)
                return false;
            splitH = false;
        }
    }
    else {
        if (region.width < 2 * minRoomSize) {
            if (region.height < 2 * minRoomSize)
                return false;
            splitH = true;
        }
    }

    if (splitH) {
        uniform_int_distribution<int> dist(minRoomSize, region.height - minRoomSize);
        int splitY = dist(rng);
        left = new BSPNode(region.x, region.y, region.width, splitY);
        right = new BSPNode(region.x, region.y + splitY, region.width, region.height - splitY);
    }
    else {
        uniform_int_distribution<int> dist(minRoomSize, region.width - minRoomSize);
        int splitX = dist(rng);
        left = new BSPNode(region.x, region.y, splitX, region.height);
        right = new BSPNode(region.x + splitX, region.y, region.width - splitX, region.height);
    }

    return true;
}

void BSPNode::createRooms(mt19937& rng) {
    if (left || right) {
        if (left) left->createRooms(rng);
        if (right) right->createRooms(rng);
    }
    else {
        int maxRoomWidth = min(maxRoomSize, region.width);
        int maxRoomHeight = min(maxRoomSize, region.height);
        uniform_int_distribution<int> roomWidthDist(minRoomSize, maxRoomWidth);
        uniform_int_distribution<int> roomHeightDist(minRoomSize, maxRoomHeight);
        int roomWidth = roomWidthDist(rng);
        int roomHeight = roomHeightDist(rng);
        uniform_int_distribution<int> roomXDist(0, region.width - roomWidth);
        uniform_int_distribution<int> roomYDist(0, region.height - roomHeight);
        int roomX = region.x + roomXDist(rng);
        int roomY = region.y + roomYDist(rng);
        room = Rect(roomX, roomY, roomWidth, roomHeight);
    }
}

void BSPNode::connectRooms(vector<vector<TileType>>& map, mt19937& rng) {
    if (left && right) {
        left->connectRooms(map, rng);
        right->connectRooms(map, rng);
        Rect lRoom = left->getRoom();
        Rect rRoom = right->getRoom();
        int lCenterX = lRoom.x + lRoom.width / 2;
        int lCenterY = lRoom.y + lRoom.height / 2;
        int rCenterX = rRoom.x + rRoom.width / 2;
        int rCenterY = rRoom.y + rRoom.height / 2;

        uniform_int_distribution<int> dist(0, 1);
        if (dist(rng) == 0) {
            carveHorizontalCorridor(map, lCenterX, rCenterX, lCenterY);
            carveVerticalCorridor(map, lCenterY, rCenterY, rCenterX);
        }
        else {
            carveVerticalCorridor(map, lCenterY, rCenterY, lCenterX);
            carveHorizontalCorridor(map, lCenterX, rCenterX, rCenterY);
        }
    }
}

Rect BSPNode::getRoom() const {
    if (isLeaf()) return room;
    if (left) return left->getRoom();
    if (right) return right->getRoom();
    return Rect();
}

void BSPNode::carveHorizontalCorridor(vector<vector<TileType>>& map, int x1, int x2, int y) {
    int start = min(x1, x2);
    int end = max(x1, x2);
    for (int x = start; x <= end; ++x) {
        if (y >= 0 && y < mapHeight && x >= 0 && x < mapWidth) {
            map[y][x] = FLOOR;
        }
    }
}

void BSPNode::carveVerticalCorridor(vector<vector<TileType>>& map, int y1, int y2, int x) {
    int start = min(y1, y2);
    int end = max(y1, y2);
    for (int y = start; y <= end; ++y) {
        if (y >= 0 && y < mapHeight && x >= 0 && x < mapWidth) {
            map[y][x] = FLOOR;
        }
    }
}