// From: https://www.sfml-dev.org/tutorials/2.5/graphics-draw.php#the-drawing-window
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <list>

const int nrows = 20, ncols = 30, blocksize = 25;

struct point {
    int row, col;
};

void draw_field(sf::RenderWindow& window, sf::RectangleShape& fieldblock)
{
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            fieldblock.setPosition(j * blocksize, i * blocksize);
            window.draw(fieldblock);
        }
    }
}

void draw_snake(sf::RenderWindow& window,
    sf::RectangleShape& snakeblock, // TO DO: Replace by sf::Sprite and draw a apple
    std::list<point>& snake)
{
    for (auto p : snake) {
        snakeblock.setPosition(p.col * blocksize, p.row * blocksize);
        window.draw(snakeblock);
    }
}

void move_snake(std::list<point>& snake, sf::Keyboard::Key key)
{
    point new_head = snake.front();
    if (key == sf::Keyboard::Left || key == sf::Keyboard::A) {
        new_head.col--;
    } else if (key == sf::Keyboard::Up) {
        new_head.row--;
    } else if (key == sf::Keyboard::Right) {
        new_head.col++;
    } else if (key == sf::Keyboard::Down) {
        new_head.row++;
    }
    // FIXME: Game bugs if any other key is pressed: we get a game over!! Just ignore it
    snake.push_front(new_head);
}

void draw_apple(sf::RenderWindow& window, sf::CircleShape& appleshape, point& apple)
{
    appleshape.setPosition(apple.col * blocksize, apple.row * blocksize);
    window.draw(appleshape);
}

point random_position(std::list<point>& snake)
{
    point p;

    while (true) {
        p.row = rand() % nrows;
        p.col = rand() % ncols;

        bool is_in_snake = false;
        for (auto b : snake) {
            if (p.row == b.row && p.col == b.col) {
                is_in_snake = true;
                break;
            }
        }
        if (!is_in_snake)
            return p;
    }
}

bool test_game_over(std::list<point>& snake)
{
    point head = snake.front();

    if (head.row < 0 || head.row >= nrows || head.col < 0 || head.col >= ncols)
        return true;

    auto it = snake.begin();
    it++;
    while (it != snake.end()) {
        if (head.row == it->row && head.col == it->col)
            return true;
        ++it;
    }
    return false;
}

int main()
{
    // TO DO: avoid windows resize or maximize
    sf::RenderWindow window(sf::VideoMode(ncols * blocksize, nrows * blocksize), "Snake game");

    sf::Clock clock;

    sf::RectangleShape fieldblock(sf::Vector2f(blocksize, blocksize));
    fieldblock.setFillColor(sf::Color(84, 139, 84));
    fieldblock.setOutlineThickness(1);
    fieldblock.setOutlineColor(sf::Color(143, 188, 143));

    sf::RectangleShape snakeblock(sf::Vector2f(blocksize, blocksize));
    snakeblock.setFillColor(sf::Color(204, 102, 0));
    snakeblock.setOutlineThickness(1);
    snakeblock.setOutlineColor(sf::Color::Black);

    sf::CircleShape appleshape(blocksize / 2);
    appleshape.setFillColor(sf::Color::Red);

    srand(clock.getElapsedTime().asMicroseconds());
    // Todo: Load sounds ans textures (look at https://opengameart.org or https://freesvg.org)

    std::list<point> snake = { { 10, 15 }, { 10, 16 }, { 10, 17 }}; // TO DO: Initialize the snake position relative to board size (ncols and nrows)
    point apple = random_position(snake);
    float time_speed = 0.4;
    bool game_over = false;
    sf::Keyboard::Key last_key = sf::Keyboard::Left;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) { 
                // TO DO: Restart game on F2
                // TO DO: Close on Esc
                last_key = event.key.code;
            }
        }

        if (!game_over && clock.getElapsedTime().asSeconds() > time_speed) {
            move_snake(snake, last_key);
            game_over = test_game_over(snake);
            if (game_over) {
                // Todo: Play a sound
                snakeblock.setFillColor(sf::Color::Red);
            }

            if (snake.front().col == apple.col && snake.front().row == apple.row) {
                // Todo: Play a sound
                apple = random_position(snake);
                // TO DO: Speed ​​up the snake every 5 apples
            } else if (!game_over) {
                snake.pop_back();
                // TO DO: Test if snake fill the board, then draw "You won!!" "F2 to restart"
            }

            clock.restart();
        }

        window.clear();

        draw_field(window, fieldblock);
        draw_snake(window, snakeblock, snake);
        draw_apple(window, appleshape, apple);
        if (game_over) {
            // TO DO: Draw "Game Over" "F2: Restart   Esc: Close"
        }
        window.display();
    }

    return 0;
}
