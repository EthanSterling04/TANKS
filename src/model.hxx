#pragma once

#include <ge211.hxx>
#include "tank.hxx"
#include "bullet.hxx"
#include <vector>


class Model
{
public:
    Tank player1;
    Tank player2;
    double elapsed_time;
    bool end_time_set1;
    bool end_time_set2;
    double end_time1;
    double end_time2;
    size_t map;
    Model();
    Model(size_t);
    void on_frame(double);
    bool can_shoot1;
    bool can_shoot2;
    std::vector<Bullet> player1_bullets;
    std::vector<Bullet> player2_bullets;
    void shoot(Tank player);
    std::vector<Block> vertical_walls;
    std::vector<Block> horizontal_walls;
    std::vector<Block> vertical_breakable_walls;
    std::vector<Block> horiztonal_breakable_walls;
    std::vector<Block> vertical_broken_walls;
    std::vector<Block> horizontal_broken_walls;
    ge211::geometry::Dims<double> start1;
    ge211::geometry::Dims<double> start2;
    bool game_start;
    std::string winner;
};