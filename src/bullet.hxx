// Defines a struct for modeling the bullet.

#pragma once

#include <ge211.hxx>

#include <iostream>

#include "tank.hxx"


///
///   struct Position
///   {
///       float x;   // pixel distance from left edge of window
///       float y;   // pixel distance from top edge of window
///   };
using Position = ge211::Posn<float>;


///
///   struct Velocity
///   {
///       float width;   // horizontal rate of change (px/s)
///       float height;  // vertical rate of change (px/s)
///   };
using Velocity = ge211::Dims<float>;


///
///   struct Block
///   {
///       int x;       // x coordinate of left side of rectangle
///       int y;       // y coordinate of top side of rectangle
///       int width;
///       int height;
///   };
using Block = ge211::Rect<int>;



struct Bullet
{
    //
    // CONSTRUCTOR
    //
    Bullet(Tank const& tank);

    //
    // MEMBER FUNCTIONS
    //

    Position top_left() const;


    Bullet next(double dt) const;

    bool hits_block(Block const&) const;

    bool hits_wall(std::vector<Block>& walls) const;

    bool break_wall(std::vector<Block>& walls) const;

    void reflect_vertical();

    void reflect_horizontal();

    //
    // MEMBER VARIABLES
    //

    /// The radius of the bullet.
    int radius;

    /// The position of the center of the bullet.
    Position center;

    /// The velocity of the bullet in pixels per tick.
    Velocity velocity;

    /// Ticks remaining
    int lifespan;
};


bool
operator==(Bullet const&, Bullet const&);


bool
operator!=(Bullet const&, Bullet const&);


std::ostream&
operator<<(std::ostream&, Bullet const&);
