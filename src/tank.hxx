#pragma once

#include <ge211.hxx>

using Block = ge211::Rect<int>;

class Tank
{
private:
    ge211::Posn<double> pos_;
    ge211::Dims<double> dir_;
    int velocity_;
    int lives_;
public:
    Tank(ge211::Dims<double>, ge211::Dims<double>);
    Tank(ge211::Dims<double>, ge211::Dims<double>, int);
    void set_direction(double);
    void set_velocity(int v);
    int angular_velocity = 0;
    void set_lives(int l);
    void update_position(const std::vector<Block>& horizontal_walls,
                         const std::vector<Block>& vertical_walls,
                         const std::vector<Block>& vertical_breakable_walls,
                         const std::vector<Block>& horiztonal_breakable_walls,
                         const std::vector<Block>& vertical_broken_walls,
                         const std::vector<Block>& horizontal_broken_walls);
    ge211::Posn<double> const& get_position() const;
    ge211::Dims<double> const& get_direction() const;
    const int& get_lives() const;
    ge211::geometry::Rect<int> get_bounding_box();
    bool operator==(Tank const&);
    bool operator!=(Tank const&);
};
