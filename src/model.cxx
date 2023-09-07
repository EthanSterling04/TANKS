#include "model.hxx"

std::vector<Block> map1_horizontal = {
        Block(0, 100, 100, 10),
        Block(200, 100, 100, 10),
        Block(300, 100, 100, 10),
        Block(500, 100, 100, 10),
        Block(700, 100, 100, 10),
        Block(0, 200, 100, 10),
        Block(400, 200, 100, 10),
        Block(600, 200, 100, 10),
        Block(700, 200, 100, 10),
        Block(100, 300, 100, 10),
        Block(300, 300, 100, 10),
        Block(0, 400, 100, 10),
        Block(210, 400, 100, 10),
        Block(400, 400, 100, 10),
        Block(700, 400, 100, 10),

};

std::vector<Block> map1_vertical = {
        Block(200, 0, 10, 100),
        Block(300, 100, 10, 100),
        Block(300, 300, 10, 100),
        Block(400, 300, 10, 100),
        Block(400, 500, 10, 100),
        Block(500, 0, 10, 100),
        Block(600, 200, 10, 100),

};

std::vector<Block> map1_horizontal_breakable = {
        Block(100, 200, 100, 10),
        Block(600, 300, 100, 10),

};

std::vector<Block> map1_vertical_breakable = {
        Block(400, 200, 10, 100),
        Block(500, 310, 10, 100),

};


std::vector<Block> map1_vertical_broken_walls = {

};

std::vector<Block> map1_horizontal_broken_walls = {

};


std::vector<Block> map2_horizontal = {
        Block(0, 100, 100, 10),
        Block(200, 100, 100, 10),
        Block(500, 100, 100, 10),
        Block(700, 100, 100, 10),
        Block(0, 200, 100, 10),
        Block(400, 200, 100, 10),
        Block(600, 200, 100, 10),
        Block(110, 300, 100, 10),
        Block(310, 300, 100, 10),
        Block(700, 300, 100, 10),
        Block(210, 400, 100, 10),
        Block(400, 400, 100, 10),
        Block(500, 400, 100, 10),
        Block(600, 400, 100, 10),
};

std::vector<Block> map2_vertical = {
        Block(100, 300, 10, 100),
        Block(200, 200, 10, 100),
        Block(200, 400, 10, 100),
        Block(300, 0, 10, 100),
        Block(300, 100, 10, 100),
        Block(300, 300, 10, 100),
        Block(400, 400, 10, 100),
        Block(500, 0, 10,100)
};

std::vector<Block> map2_horizontal_breakable = {
        Block(310, 100, 100, 10),
        Block(500, 300, 100, 10),

};

std::vector<Block> map2_vertical_breakable = {
        Block(100, 200, 10, 100),
        Block(400, 200, 10, 100),

};

std::vector<Block> map2_vertical_broken_walls = {

};

std::vector<Block> map2_horizontal_broken_walls = {

};

std::vector<Block> map3_vertical;
std::vector<Block> map3_horizontal;
std::vector<Block> map3_horizontal_breakable;
std::vector<Block> map3_vertical_breakable;
std::vector<Block> map3_vertical_broken_walls;
std::vector<Block> map3_horizontal_broken_walls;

Model::Model()
        : Model(2)
{ }

Model::Model(size_t m)
        : player1({100, 300}, {1,0}),
          player2({700, 300}, {-1,0}),
          elapsed_time(0.0),
          end_time_set1(false),
          end_time_set2(true),
          end_time1(-1.0),
          end_time2(-1.0),
          map(m),
          can_shoot1(true),
          can_shoot2(true),
          start1(100, 300),
          start2(700, 300),
          game_start(false),
          winner("None")
{

}

void
Model::shoot(Tank player)
{
    if (player == player1) {
        if (can_shoot1) {
            player1_bullets.push_back(Bullet(player1));
        }
        can_shoot1 = false;
    }
    else {
        if (can_shoot2) {
            player2_bullets.push_back(Bullet(player2));
        }
        can_shoot2 = false;
    }
}

void
Model::on_frame(double dt)
{
    elapsed_time += dt;

    if(!game_start){
        if (map == 1) {
            horizontal_walls = map1_horizontal;
            vertical_walls = map1_vertical;
            horiztonal_breakable_walls = map1_horizontal_breakable;
            vertical_breakable_walls = map1_vertical_breakable;
            horizontal_broken_walls = map1_horizontal_broken_walls;
            vertical_broken_walls = map1_vertical_broken_walls;
            start1 = {100, 50};
            start2 = {700, 50};
            player1 = Tank(start1, {1,0});
            player2 = Tank(start2, {-1,0});

        }

        if (map == 2){
            horizontal_walls = map2_horizontal;
            vertical_walls = map2_vertical;
            horiztonal_breakable_walls = map2_horizontal_breakable;
            vertical_breakable_walls = map2_vertical_breakable;
            horizontal_broken_walls = map2_horizontal_broken_walls;
            vertical_broken_walls = map2_vertical_broken_walls;
            start1 = {100, 500};
            start2 = {650, 150};
            player1 = Tank(start1, {1,0});
            player2 = Tank(start2, {-1,0});

        }

        if (map == 3){
            horizontal_walls = map3_horizontal;
            vertical_walls = map3_vertical;
            horiztonal_breakable_walls = map3_horizontal_breakable;
            vertical_breakable_walls = map3_vertical_breakable;
            horizontal_broken_walls = map3_horizontal_broken_walls;
            vertical_broken_walls = map3_vertical_broken_walls;
            start1 = {100, 300};
            start2 = {700, 300};
            player1 = Tank(start1, {1,0});
            player2 = Tank(start2, {-1,0});
        }



        horizontal_walls.push_back(Block(0, 0, 800, 10));
        horizontal_walls.push_back(Block(0, 550, 800, 10));
        vertical_walls.push_back(Block(0, 0, 10, 600));
        vertical_walls.push_back(Block(790, 0, 10, 600));
    }

    // Check if player1 or player2 has no lives left
    if (player1.get_lives() == 0 || player2.get_lives() == 0) {
        // handle game over condition
        if (player1.get_lives() == 0) {
            winner = "red";
        }
        else {
            winner = "blue";
        }
        game_start = false;
        player1.set_lives(3 - player1.get_lives());
        player2.set_lives(3 - player2.get_lives());
    }

    // Handle player1 shooting
    if (!can_shoot1 && !end_time_set1) {
        end_time1 = elapsed_time + 1;
        end_time_set1 = true;
    }

    if (!can_shoot1 && end_time_set1) {
        double tolerance = 0.0001; // Adjust the tolerance value as needed
        if (elapsed_time >= end_time1 - tolerance) {
            can_shoot1 = true;
            end_time_set1 = false;
            end_time1 = -1;
        }
    }

    // Handle player2 shooting
    if (!can_shoot2 && !end_time_set2) {
        end_time2 = elapsed_time + 1;
        end_time_set2 = true;
    }

    if (!can_shoot2 && end_time_set2) {
        double tolerance = 0.0001; // Adjust the tolerance value as needed
        if (elapsed_time >= end_time2 - tolerance) {
            can_shoot2 = true;
            end_time_set2 = false;
            end_time2 = -1;
        }
    }

    // Update rotation
    player1.set_direction(1 * player1.angular_velocity);
    player2.set_direction(1 * player2.angular_velocity);

    // Update tank positions
    player1.update_position(horizontal_walls, vertical_walls,
                            vertical_breakable_walls,
                            horiztonal_breakable_walls,
                            vertical_broken_walls, horizontal_broken_walls);
    player2.update_position(horizontal_walls, vertical_walls,
                            vertical_breakable_walls,
                            horiztonal_breakable_walls,
                            vertical_broken_walls, horizontal_broken_walls);


    // Check for bullet-tank collision for player1's bullets
    for (Bullet& b1 : player1_bullets) {
        if (b1.lifespan == 0) {
            player1_bullets.erase(player1_bullets.begin());
        }
        else {
            Bullet b = b1.next(dt);

            // Check if the bullet hits tank
            if (b.hits_block(player1.get_bounding_box()) ||
                b.hits_block(player2.get_bounding_box())) {
                // Destroy the tank and deduct a life from the player
                if (b.hits_block(player2.get_bounding_box())) {
                    player2.set_lives(-1);
                }
                else {
                    player1.set_lives(-1);
                }

                // Clear all bullets on the board
                player1_bullets.clear();
                player2_bullets.clear();

                // Respawn the tanks at their starting positions
                player1 = Tank(start1, {1, 0}, player1.get_lives());
                player2 = Tank(start2, {-1, 0}, player2.get_lives());

                return; // No need to continue the loop
            }

            // Check if bullet hits a vertical wall
            if (b.hits_wall(vertical_walls)) {
                b1.reflect_horizontal();
            }

            // Check if bullet hits a horizontal wall
            if (b.hits_wall(horizontal_walls)) {
                b1.reflect_vertical();
            }

            if (b.break_wall(horiztonal_breakable_walls)){
                horizontal_broken_walls.push_back
                    (horiztonal_breakable_walls.back());
                horiztonal_breakable_walls.pop_back();
                horiztonal_breakable_walls.pop_back();
                b1.lifespan = 1;

            }
            if(b.break_wall(vertical_breakable_walls)){
                vertical_broken_walls.push_back(vertical_breakable_walls.back()
                );
                vertical_breakable_walls.pop_back();
                vertical_breakable_walls.pop_back();
                b1.lifespan = 1;
            }

            b1 = b1.next(dt);
        }
    }


    // Check for bullet-tank collision for player2's bullets
    for (Bullet& b2 : player2_bullets) {
        if (b2.lifespan == 0) {
            player2_bullets.erase(player2_bullets.begin());
        }
        else {
            Bullet b = b2.next(dt);

            // Check if the bullet hits tank
            if (b.hits_block(player1.get_bounding_box()) ||
                b.hits_block(player2.get_bounding_box())) {
                // Destroy the tank and deduct a life from the player
                if (b.hits_block(player1.get_bounding_box())) {
                    player1.set_lives(-1);
                }
                else {
                    player2.set_lives(-1);
                }

                // Clear all bullets on the board
                player1_bullets.clear();
                player2_bullets.clear();

                // Respawn the tanks at their starting positions
                player1 = Tank(start1, {1, 0}, player1.get_lives());
                player2 = Tank(start2, {-1, 0}, player2.get_lives());

                return; // No need to continue the loop
            }

            // Check if bullet hits a vertical wall
            if (b.hits_wall(vertical_walls)) {
                b2.reflect_horizontal();
            }

            // Check if bullet hits a horizontal wall
            if (b.hits_wall(horizontal_walls)) {
                b2.reflect_vertical();
            }

            if (b.break_wall(horiztonal_breakable_walls)){
                horizontal_broken_walls.push_back
                    (horiztonal_breakable_walls.back());
                horiztonal_breakable_walls.pop_back();
                horiztonal_breakable_walls.pop_back();
                b2.lifespan = 1;

            }
            if(b.break_wall(vertical_breakable_walls)){
                vertical_broken_walls.push_back
                    (vertical_breakable_walls.back());
                vertical_breakable_walls.pop_back();
                vertical_breakable_walls.pop_back();
                b2.lifespan = 1;
            }

            b2 = b2.next(dt);
        }
    }
}