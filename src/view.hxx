#pragma once

#include "model.hxx"

class View
{
public:
    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);

private:
    Model const& model_;
    ge211::Rectangle_sprite background;
    ge211::Image_sprite tank_body1;
    ge211::Image_sprite tank_body2;
    ge211::Circle_sprite const bullet_sprite;
    ge211::Rectangle_sprite tank1_life;
    ge211::Rectangle_sprite tank2_life;
    ge211::Rectangle_sprite border_horizontal;
    ge211::Rectangle_sprite border_vertical;
    ge211::Rectangle_sprite wall_vertical;
    ge211::Rectangle_sprite wall_horizontal;
    ge211::Rectangle_sprite wall_vertical_breakable;
    ge211::Rectangle_sprite wall_horizontal_breakable;
    ge211::Rectangle_sprite wall_vertical_broken;
    ge211::Rectangle_sprite wall_horizontal_broken;
    ge211::Image_sprite cover;
    ge211::Rectangle_sprite white;



};
