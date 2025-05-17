#ifndef DUNGEON_H
#define DUNGEON_H

class BSPNode;

class Dungeon {
public:
    virtual void generateDungeon() = 0;
    virtual ~Dungeon() = default;
};

#endif
