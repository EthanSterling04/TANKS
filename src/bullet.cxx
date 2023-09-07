#include "bullet.hxx"

// Computes where the bullet should be when it is launched by the tank:
static Position
on_tank(Tank const& tank)
{
    ge211::geometry::Posn<double> p = tank.get_position();
    double angle = std::atan2(tank.get_direction().height,
                              tank.get_direction().width);
    double offset = 30; // Adjust this value as needed

    double dx = std::cos(angle) * offset;
    double dy = std::sin(angle) * offset;

    p += {dx, dy};
    return p.into<float>();
}

Bullet::Bullet(Tank const& tank)
        : radius(5),
          center(on_tank(tank)),
          velocity(tank.get_direction() * 100),
          lifespan(420)
{ }

Position
Bullet::top_left() const
{
    float x = center.x - radius;
    float y = center.y - radius;
    return {x, y};
}


Bullet
Bullet::next(double dt) const
{
    Bullet result(*this);
    result.center += result.velocity * dt;
    result.lifespan -= 1;
    return result;
}


bool
Bullet::hits_block(Block const& block) const
{
    int top = center.y - radius;
    int left = center.x - radius;
    int bottom = center.y + radius;
    int right = center.x + radius;

    if (block.top_right().x < left || right < block.top_left().x) {
        return false;
    }
    else if (bottom < block.top_right().y || block.bottom_left().y < top) {
        return false;
    }
    return true;
}

void
Bullet::reflect_vertical()
{
    velocity.height *= -1;
}

void
Bullet::reflect_horizontal()
{
    velocity.width *= -1;
}


bool
Bullet::hits_wall(std::vector<Block>& walls) const
{
    for (auto& wall : walls) {
        if (hits_block(wall)) {
            return true;
        }
    }
    return false;
}

bool
Bullet::break_wall(std::vector<Block>& walls) const
{
    for (auto& brick : walls) {
        if (hits_block(brick)) {
            Block temp = brick;
            brick = walls.back();
            walls.push_back(temp);
            return true;
        }
    }
    return false;
}

bool
operator==(Bullet const& a, Bullet const& b)
{
    return (a.center == b.center && a.radius == b.radius && a.velocity == b
    .velocity && a.lifespan == b.lifespan);
}

bool
operator!=(Bullet const& a, Bullet const& b)
{
    return !(a == b);
}

std::ostream&
operator<<(std::ostream& o, Bullet const& ball)
{
    o << "Ball{\n";
    o << "Center: " << ball.center << "\nRadius: " << ball.radius <<
    "\nVelocity: " << ball.velocity << "\nLifespan:" << ball.lifespan;
    return o << "\n}";
}
