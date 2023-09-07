#include "model.hxx"
#include <catch.hxx>

TEST_CASE("example test (TODO: replace this)")
{
    CHECK(1 + 1 == 2);
}

//


// }

TEST_CASE("mini-game/expected ball action"){
    Model m;
    //Check that the game does not start too early
    CHECK(m.game_start == false);
    m.game_start = true;


    // Let's run at 1 fps.
    double const dt = 1;

    m.shoot(m.player1);

    // The ball is headed toward the paddle at 24 px/s from 72 px away,
    // so it should hit it in 3 s. If we simulate 8 fps then it should
    // hit in the 3rd frame.
    m.player1_bullets.begin()->center.x = 745;
    m.player1_bullets.begin()->center.y = 150;

    // Make a copy of the bullet for computing what we expect it to do.
    Bullet expected_bullet = *m.player1_bullets.begin();

    // Simulate frames
    for (int i = 0; i < 5; ++i) {
        // run both the expected bullet and the model for a frame
        // then check that they agree still
        expected_bullet = expected_bullet.next(dt);
        m.on_frame(dt);
        CHECK(*m.player1_bullets.begin() == expected_bullet);
    }

    // // Simulate one frame in which the ball finally hits the boundary,
    // // which means that it reflects horizontally.
    // expected_bullet.velocity.width *= -1;
    // expected_bullet = expected_bullet.next(dt);
    // m.on_frame(dt);
    // CHECK(*m.player1_bullets.begin() == expected_bullet);
    // CHECK(expected_bullet.velocity.width < 0);

}

//
TEST_CASE("Tank Hit")
{

    Model m;
    //Check that the game does not start too early
    CHECK(m.game_start == false);
    m.game_start = true;


    m.shoot(m.player1);

    //test that if a tank is hit, they lose a life
    CHECK(m.player1.get_lives() == 3);
    CHECK(m.player2.get_lives() == 3);
    if (m.player1_bullets.begin()->hits_block(m.player1.get_bounding_box())) {
        CHECK(m.player1.get_lives() == 2);
    }

}

TEST_CASE("cannot spam"){

    Model m;
    //Check that the game does not start too early
    CHECK(m.game_start == false);
    m.game_start = true;


    // Let's run at 1 fps.
    double const dt = 1;

    m.shoot(m.player1);
    CHECK(!m.can_shoot1);
    CHECK(m.can_shoot2);
    m.on_frame(dt);
    m.shoot(m.player2);
    CHECK(!m.can_shoot2);
    m.on_frame(dt);
    m.on_frame(dt);
    CHECK(m.can_shoot1);
    CHECK(m.can_shoot2);
    m.on_frame(dt);
    m.shoot(m.player1);
    m.shoot(m.player2);



}
TEST_CASE("Tank Control"){
    Model m;
    m.map = 2;
    //Check that the game does not start too early
    CHECK(m.game_start == false);
    m.game_start = true;

    double dt = 1;

    m.player1.set_velocity(1);
    m.player2.set_velocity(1);
    m.on_frame(dt);
    //since the direction is set to {1,0}, only moving in x
    CHECK(m.player1.get_position().x == 101);
    CHECK(m.player1.get_position().y == 300);
    CHECK(m.player2.get_position().x == 699);
    CHECK(m.player2.get_position().y == 300);
    //since the direction is set to {-1,0), only moving in x
    m.on_frame(dt);
    CHECK(m.player1.get_position().x == 102);
    CHECK(m.player1.get_position().y == 300);
    CHECK(m.player2.get_position().x == 698);
    CHECK(m.player2.get_position().y == 300);
    //change velocity to -1 and test
    m.player1.set_velocity(-1);
    m.player2.set_velocity(-1);
    m.on_frame(dt);
    CHECK(m.player1.get_position().x == 101);
    CHECK(m.player1.get_position().y == 300);
    CHECK(m.player2.get_position().x == 699);
    CHECK(m.player2.get_position().y == 300);
    m.on_frame(dt);
    CHECK(m.player1.get_position().x == 100);
    CHECK(m.player1.get_position().y == 300);
    CHECK(m.player2.get_position().x == 700);
    CHECK(m.player2.get_position().y == 300);
    m.player1.set_velocity(1);
    m.player2.set_velocity(1);
    //try changing direction
    m.player1.set_direction(90);
    m.player2.set_direction(90);
    m.on_frame(dt);
    CHECK(m.player1.get_position().x == 100);
    CHECK(m.player1.get_position().y == 301);
    CHECK(m.player2.get_position().x == 700);
    CHECK(m.player2.get_position().y == 299);
}

TEST_CASE("Game Over"){
    Model m;
    //Check that the game does not start too early
    CHECK(m.game_start == false);
    m.game_start = true;


    m.shoot(m.player1);

    //test that if a tank is hit, they lose a life
    CHECK(m.player1.get_lives() == 3);
    CHECK(m.player2.get_lives() == 3);
    if (m.player1_bullets.begin()->hits_block(m.player1.get_bounding_box())) {
        CHECK(m.player1.get_lives() == 2);
    }
    //test that when the game is over, the game_start status goes back to
    // false and both players return to 3 lives
    if (m.player1.get_lives() == 0){
        CHECK(m.game_start == false);
        CHECK(m.player1.get_lives() == 3);
        CHECK(m.player2.get_lives() == 3);

    }
}


TEST_CASE("Breakable walls turn into broken walls"){
    Model m;
    //Check that the game does not start too early
    CHECK(m.game_start == false);
    m.game_start = true;


    m.shoot(m.player1);

    CHECK(m.vertical_broken_walls.empty());
    CHECK(m.horizontal_broken_walls.empty());

    //check that if it hits a breakable wall, a broken wall is added to the
    // Vertical broken wall vector

    if (m.player1_bullets.begin()->hits_wall(m.vertical_breakable_walls)){
        CHECK(!m.vertical_broken_walls.empty());
    }
    if (m.player1_bullets.begin()->hits_wall(m.horiztonal_breakable_walls)){
        CHECK(!m.horizontal_broken_walls.empty());
    }
}

TEST_CASE("bullet goes through broken wall"){
    Model m;
    //Check that the game does not start too early
    CHECK(m.game_start == false);
    m.game_start = true;

    double dt = 1;


    m.shoot(m.player1);

    m.vertical_broken_walls.push_back(ge211::geometry::Rect<int>{100,100, 10,
                                                                 10});

    //would bump into wall if possible
    m.player1_bullets.begin()->center.x = 99;
    m.player1_bullets.begin()->center.y = 99;

    m.on_frame(dt);
    m.on_frame(dt);

    //check it does not reflect
    CHECK(m.player1_bullets.begin()->center.x == 299);
    CHECK(m.player1_bullets.begin()->center.y == 99);

}



