#include "tank.hxx"
#include <cmath>

Tank::Tank(ge211::Dims<double> pos, ge211::Dims<double> dir)
    :   pos_(pos),
        dir_(dir),
        velocity_(0),
        lives_(3)
{ }

Tank::Tank(ge211::Dims<double> pos, ge211::Dims<double> dir, int l)
        :   pos_(pos),
            dir_(dir),
            velocity_(0),
            lives_(l)
{ }

void
Tank::set_direction(double theta)
{
    double curr_angle = atan2(dir_.height, dir_.width);
    double new_angle = curr_angle + theta * (M_PI/180.0);
    double x = cos(new_angle);
    double y = sin(new_angle);
    double len = sqrt(x * x + y * y);
    x /= len;
    y /= len;

    dir_.width = x;
    dir_.height = y;
}

void
Tank::set_velocity(int v)
{
    velocity_ = v;
}

void
Tank::set_lives(int l)
{
    lives_ += l;
}

const ge211::Posn<double>&
Tank::get_position() const
{
    return pos_;
}

const ge211::Dims<double>&
Tank::get_direction() const
{
    return dir_;
}

const int&
Tank::get_lives() const
{
    return lives_;
}

void
Tank::update_position(const std::vector<Block>& horizontal_walls,
                      const std::vector<Block>& vertical_walls,
                      const std::vector<Block>& vertical_breakable_walls,
                      const std::vector<Block>& horiztonal_breakable_walls,
                      const std::vector<Block>& vertical_broken_walls,
                      const std::vector<Block>& horizontal_broken_walls)
{
    ge211::Posn<double> new_position = pos_ + dir_ * velocity_;

    // Check for collisions with horizontal walls
    for (const Block& wall : horizontal_walls) {
        if (new_position.y + 17 < wall.bottom_left().y || new_position.y - 17 >
        wall
        .top_right().y)
            continue; //Skip if the tank's vert position is outside the wall

        if (new_position.x - 8 < wall.top_right().x && new_position.x + 8 >
        wall
        .bottom_left().x) {
            // Collision detected, adjust tank's position
            return; // Do not update the tank's position
        }
    }
    for (const Block& wall : horiztonal_breakable_walls) {
        if (new_position.y + 17 < wall.bottom_left().y || new_position.y - 17 >
                                                          wall.top_right().y)
            continue; //Skip if the tank's vert position is outside the wall

        if (new_position.x - 8 < wall.top_right().x && new_position.x + 8 >
                                                       wall.bottom_left().x) {
            // Collision detected, adjust tank's position
            return; // Do not update the tank's position
        }
    }
    for (const Block& wall : horizontal_broken_walls) {
        if (new_position.y + 17 < wall.bottom_left().y || new_position.y - 17 >
                                                          wall.top_right().y)
            continue; //Skip if the tank's vert position is outside the wall

        if (new_position.x - 8 < wall.top_right().x && new_position.x + 8 >
                                                       wall.bottom_left().x) {
            // Collision detected, adjust tank's position
            return; // Do not update the tank's position
        }
    }

    // Check for collisions with vertical walls
    for (const Block& wall : vertical_walls) {
        if (new_position.x + 8 < wall.bottom_left().x || new_position.x - 8 >
        wall
        .top_right().x)
            continue; //Skip if the tank's horiz position is outside the wall

        if (new_position.y - 13 < wall.bottom_left().y && new_position.y + 13 >
                wall.top_right().y) {
            // Collision detected, adjust tank's position
            return; // Do not update the tank's position
        }
    }
    for (const Block& wall : vertical_breakable_walls) {
        if (new_position.x + 8 < wall.bottom_left().x || new_position.x - 8 >
                                                         wall
                                                                 .top_right().x)
            continue; //Skip if the tank's horiz position is outside the wall

        if (new_position.y - 13 < wall.bottom_left().y && new_position.y + 13 >
                                                          wall.top_right().y) {
            // Collision detected, adjust tank's position
            return; // Do not update the tank's position
        }
    }
    for (const Block& wall : vertical_broken_walls) {
        if (new_position.x + 8 < wall.bottom_left().x || new_position.x - 8 >
                                                         wall
                                                                 .top_right().x)
            continue; //Skip if the tank's horiz position is outside the wall

        if (new_position.y - 13 < wall.bottom_left().y && new_position.y + 13 >
                                                          wall.top_right().y) {
            // Collision detected, adjust tank's position
            return; // Do not update the tank's position
        }
    }

    // No collision detected, update tank's position
    pos_ = new_position;
}


ge211::geometry::Rect<int>
Tank::get_bounding_box()
{
    // Calculate the top-left position of the bounding box
    ge211::Posn<int> top_left(pos_.x - 15, pos_.y - 15);

    // Calculate the dimensions of the bounding box
    ge211::Dims<int> dimensions(30, 30);

    // Create and return the bounding box rectangle
    return ge211::geometry::Rect<int>(top_left.x, top_left.y,
                                      dimensions.width, dimensions.height);
}

bool
Tank::operator==(Tank const& other)
{
    return (this->get_position() == other.get_position() &&
    this->get_direction() == other.get_direction());
}

bool
Tank::operator!=(Tank const& other)
{
    return !(*this==other);
}
