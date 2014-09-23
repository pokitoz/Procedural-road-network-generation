#ifndef TILE_H
#define TILE_H

/**
 * @brief The Tile class
 * Represents a cell of the map array
 */
class Tile
{
public:
    Tile();

    double density;
    double height;
    bool is_accessible;
    bool is_road;

};

#endif // TILE_H
