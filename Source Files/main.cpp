#include "DungeonGenerator.h"
#include <iostream>

using namespace std;

int main() {
    cout << "Welcome to the Dungeon Generator!" << endl;

    int mapWidth, mapHeight, minRoomSize, maxRoomSize, maxDepth;

    cout << "Enter map width: ";
    cin >> mapWidth;

    cout << "Enter map height: ";
    cin >> mapHeight;

    cout << "Enter min room size: ";
    cin >> minRoomSize;

    cout << "Enter max room size: ";
    cin >> maxRoomSize;

    cout << "Enter max BSP tree depth: ";
    cin >> maxDepth;

    DungeonGenerator generator(mapWidth, mapHeight, minRoomSize, maxRoomSize, maxDepth);
    generator.generateDungeon();

    return 0;
}