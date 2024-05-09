/* Trevor Gerald */

struct Sim {
    double elapsed_time;
    void *mascots;
    void *coins;
};

struct Buckeye {
    double x_position;
    double y_position;
    double x_velocity;
    double y_velocity;
    double jump_velocity;
    int color;
    int loot;
    struct Sim *world;
};

struct Coin {
    int color;
    double x_position;
    double y_position;
};
