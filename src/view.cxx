#include "view.hxx"

const int TANK_SIZE = 30;

View::View(Model const& model)
        : model_(model),
          background({800,600}, {255,255,255}),
          tank_body1("Blue_Tank.jpeg"),
          tank_body2("Red_Tank.jpg"),
          bullet_sprite(5, {0, 0, 0}),
          tank1_life({10,10}, {0,191,255}),
          tank2_life({10,10}, {210, 4, 45}),
          border_horizontal({800,10}, {169,169,169}),
          border_vertical({10,600}, {169,169,169}),
          wall_vertical({10,100},{169,169,169}),
          wall_horizontal({100,10},{169,169,169}),
          wall_vertical_breakable({10,100},{250, 250, 51}),
          wall_horizontal_breakable({100,10},{250, 250, 51}),
          wall_vertical_broken({10,100},{255, 192, 0}),
          wall_horizontal_broken({100,10},{255, 192, 0}),
          cover("Tanks_Cover.jpeg"),
          white({200, 50})
{ }

void
View::draw(ge211::Sprite_set& set)
{
    //Draw background
    set.add_sprite(background, {0, 0}, -10);


    if (model_.game_start) {
        //Draw walls
        for (ge211::geometry::Rect<int> w: model_.vertical_walls) {
            set.add_sprite(wall_vertical, w.top_left());
        }

        for (ge211::geometry::Rect<int> w: model_.vertical_breakable_walls) {
            set.add_sprite(wall_vertical_breakable, w.top_left());
        }

        for (ge211::geometry::Rect<int> w: model_.vertical_broken_walls) {
            set.add_sprite(wall_vertical_broken, w.top_left());
        }

        for (ge211::geometry::Rect<int> w: model_.horizontal_walls) {
            set.add_sprite(wall_horizontal, w.top_left());
        }

        for (ge211::geometry::Rect<int> w: model_.horiztonal_breakable_walls) {
            set.add_sprite(wall_horizontal_breakable, w.top_left());
        }

        for (ge211::geometry::Rect<int> w: model_.horizontal_broken_walls) {
            set.add_sprite(wall_horizontal_broken, (w.top_left()));

        }


        //Player 1
        double
                rotation_angle1 =
                std::atan2(model_.player1.get_direction().height,
                           model_.player1.get_direction().width)
                * (180.0 / M_PI);

        ge211::Transform rotation_transform1 = ge211::Transform::rotation
                (rotation_angle1);

        ge211::geometry::Posn<int> tank1_center =
                model_.player1.get_position().into<int>();
        ge211::geometry::Posn<int> tank1_top_left =
                {tank1_center.x - TANK_SIZE / 2,
                 tank1_center.y - TANK_SIZE / 2};
        set.add_sprite(tank_body1, tank1_top_left, 5, rotation_transform1);

        //Player 2
        double
                rotation_angle2 =
                std::atan2(model_.player2.get_direction().height,
                           model_.player2.get_direction().width) *
                (180.0 / M_PI);

        ge211::Transform rotation_transform2 = ge211::Transform::rotation
                (rotation_angle2);

        ge211::geometry::Posn<int> tank2_center =
                model_.player2.get_position().into<int>();
        ge211::geometry::Posn<int> tank2_top_left =
                {tank2_center.x - TANK_SIZE / 2,
                 tank2_center.y - TANK_SIZE / 2};
        set.add_sprite(tank_body2, tank2_top_left, 5, rotation_transform2);

        //Player 1 bullets
        for (Bullet b1: model_.player1_bullets) {
            set.add_sprite(bullet_sprite, b1.top_left().into<int>());
        }

        //Player 2 bullets
        for (Bullet b2: model_.player2_bullets) {
            set.add_sprite(bullet_sprite, b2.top_left().into<int>());
        }

        //Player 1 lives
        for (int i = 0; i < model_.player1.get_lives(); i++) {
            ge211::geometry::Posn<int> p = {50, 570};
            set.add_sprite(tank1_life, p.right_by(15 * i), 7);
        }

        //Player 2 lives
        for (int i = 0; i < model_.player2.get_lives(); i++) {
            ge211::geometry::Posn<int> p = {750, 570};
            set.add_sprite(tank2_life, p.left_by(15 * i), 7);
        }

        //Border walls
        set.add_sprite(border_horizontal, {0, 0});
        set.add_sprite(border_horizontal, {0, 590});
        set.add_sprite(border_horizontal, {0, 580});
        set.add_sprite(border_horizontal, {0, 570});
        set.add_sprite(border_horizontal, {0, 560});
        set.add_sprite(border_horizontal, {0, 550});
        set.add_sprite(border_vertical, {0, 0});
        set.add_sprite(border_vertical, {790, 0});
    }
    else {
        set.add_sprite(cover, {0,0});
        if (model_.winner == "blue") {
            set.add_sprite(white, {470,50});
        }
        if (model_.winner == "red") {
            set.add_sprite(white, {675,50});
        }
        else {
            set.add_sprite(white, {600,50});
        }
    }
}


