//
// Created by nono on 21/03/23.
//

struct vec2D{
    int x;
    int y;

    bool operator==(const vec2D& other) const{
        return x == other.x && y == other.y;
    }
};

// Define a hash function for the vec2D struct
struct DirectionHash {
    size_t operator()(const vec2D& direction) const {
        return std::hash<int>()(direction.x) ^ std::hash<int>()(direction.y);
    }
};