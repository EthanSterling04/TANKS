#include "controller.hxx"

Controller::Controller()
        : model_(),
          view_(model_)
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

void
Controller::on_frame(double dt)
{
    model_.on_frame(dt);
}

void
Controller::on_key_down(ge211::Key key)
{
    //Player 1
    if (key == ge211::events::Key::code('w')) {
        model_.player1.set_velocity(1);
    }
    else if (key == ge211::events::Key::code('s')) {
        model_.player1.set_velocity(-1);
    }
    if (key == ge211::events::Key::code('d')) {
        model_.player1.angular_velocity = 3;
    }
    else if (key == ge211::events::Key::code('a')) {
        model_.player1.angular_velocity = -3;
    }
    if (key == ge211::events::Key::code('v')) {
        model_.shoot(model_.player1);
    }

    //Player 2
    if (key == ge211::events::Key::up()) {
        model_.player2.set_velocity(1);
    }
    else if (key == ge211::events::Key::down()) {
        model_.player2.set_velocity(-1);
    }
    if (key == ge211::events::Key::right()) {
        model_.player2.angular_velocity = 3;
    }
    else if (key == ge211::events::Key::left()) {
        model_.player2.angular_velocity = -3;
    }
    if (key == ge211::events::Key::code('m')) {
        model_.shoot(model_.player2);
    }

    //all - select game map
    if (key == ge211::events::Key::code('1')){
        model_.map = 1;
    }
    if (key == ge211::events::Key::code('2')){
        model_.map = 2;

    }
    if (key == ge211::events::Key::code('3')){
        model_.map = 3;

    }
    if (key == ge211::events::Key::code(' ')){
        model_.game_start = true;

    }
}

void
Controller::on_key_up(ge211::Key key)
{
    if (key == ge211::events::Key::code('w') || key ==
    ge211::events::Key::code('s')) {
        model_.player1.set_velocity(0);
    }
    if (key == ge211::events::Key::up() || key == ge211::events::Key::down()) {
        model_.player2.set_velocity(0);
    }
    if (key == ge211::events::Key::code('a') || key ==
    ge211::events::Key::code('d')) {
        model_.player1.angular_velocity = 0;
    }
    if (key == ge211::events::Key::right() || key ==
    ge211::events::Key::left()) {
        model_.player2.angular_velocity = 0;
    }
}