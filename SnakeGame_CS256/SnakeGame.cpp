#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace sf;

int num_vertBox = 30, num_horzBox = 30;
int size = 16; //number of pixels
int w = size * num_horzBox; //background number of pixels in width
int h = size * num_vertBox; //background number of pixels in height

int direction1;
int direction2;
int snake_length1 = 4;
int snake_length2 = 4;

// delay = snake's speed
float timer = 0, delay = .2;

struct Snake1
{
    int x1,y1;
}s1[100];

struct Snake2
{
    int x2,y2;
}s2[100];

struct Fruit
{
    int x, y;
}food;


void Tick()
{
    //Move remaining pieces of snake s[1] - s[99]
    for(int i = snake_length1; i>0; --i)
    {
        s1[i].x1 = s1[i - 1].x1;
        s1[i].y1 = s1[i - 1].y1;
    }

    for(int i = snake_length2; i>0; --i)
    {
        s2[i].x2 = s2[i - 1].x2;
        s2[i].y2 = s2[i - 1].y2;
    }

    //Head of snake depends on direction of user s1[0]
    //User Up
    if(direction1 == 3)
        s1[0].y1 -= 1;

    if(direction1 == 0)
        s1[0].y1 += 1;

    if(direction1 == 1)
        s1[0].x1 -= 1;

    if(direction1 == 2)
        s1[0].x1 += 1;

    //Head of snake depends on direction of user s2[0]
    if(direction2 == 3)
        s2[0].y2 -= 1;

    if(direction2 == 0)
        s2[0].y2 += 1;

    if(direction2 == 1)
        s2[0].x2 -= 1;

    if(direction2 == 2)
        s2[0].x2 += 1;

    // Snake 1 eats the food it should grow
    if((s1[0].x1 == food.x) && (s1[0].y1 == food.y))
    {
        snake_length1++;
        delay -= .05;

        // randomly place food
        food.x = rand() % num_horzBox;
        food.y = rand() % num_vertBox;
    }

    // Snake 2 eats food it should grow
    if((s2[0].x2 == food.x) && (s2[0].y2 == food.y))
    {
        snake_length2++;
        delay -= .05;

        // randomly place food somewhere else
        food.x = rand() % num_horzBox;
        food.y = rand() % num_vertBox;
    }

    // Boundary checking screen loop back Player 1
    if( s1[0].x1  > num_horzBox-1)
        s1[0].x1 = 0;
    if( s1[0].x1  < 0)
        s1[0].x1 = num_horzBox;

    if( s1[0].y1  > num_vertBox-1)
        s1[0].y1 = 0;
    if( s1[0].y1  < 0)
        s1[0].y1 = num_vertBox;

    // Check if go over snake
    for(int i = 1; i < snake_length1; i++)
    {
        // Cut snake in half from place eaten
        if(s1[0].x1 == s1[i].x1 && s1[0].y1 == s1[i].y1)
        {
            snake_length1 = i;
            delay = .2;
        }
    }

    // Boundary checking s1creen loop back Player 2
    if( s2[0].x2  > num_horzBox-1)
        s2[0].x2 = 0;
    if( s2[0].x2  < 0)
        s2[0].x2 = num_horzBox;

    if( s2[0].y2  > num_vertBox-1)
        s2[0].y2 = 0;
    if( s2[0].y2  < 0)
        s2[0].y2 = num_vertBox;

    // Check if go over snake
    for(int i = 1; i < snake_length2; i++)
    {
        // Cut snake in half from place eaten
        if(s2[0].x2 == s2[i].x2 && s2[0].y2 == s2[i].y2)
        {
            snake_length2 = i;
            delay = .2;
        }
    }

}

int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(w, h), "Snake Game!");

    //textures
    Texture t1, t2, t3, t4;

    t1.loadFromFile("image/white.png");
    t2.loadFromFile("image/red.png");
    t3.loadFromFile("image/fruit.png");
    t4.loadFromFile("image/player2.png");


    // Sprite has physical dimensions
    Sprite sprite1(t1);
    Sprite sprite2(t2);
    Sprite sprite3(t3);

    //player 2
    Sprite player2(t4);

    food.x = 10;
    food.y = 10;

    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        //Allow us to check when a user does something
        Event e;

        //check when window is closed
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                window.close();
            }
        }

        //Controls for snake movement user1
        if(Keyboard::isKeyPressed(Keyboard::Up)) direction1 = 3;
        if(Keyboard::isKeyPressed(Keyboard::Down)) direction1 = 0;
        if(Keyboard::isKeyPressed(Keyboard::Left)) direction1 = 1;
        if(Keyboard::isKeyPressed(Keyboard::Right)) direction1 = 2;

        //Controls for snake movement user2
        if(Keyboard::isKeyPressed(Keyboard::W)) direction2 = 3;
        if(Keyboard::isKeyPressed(Keyboard::S)) direction2 = 0;
        if(Keyboard::isKeyPressed(Keyboard::A)) direction2 = 1;
        if(Keyboard::isKeyPressed(Keyboard::D)) direction2 = 2;

        if(timer > delay)
        {
            timer = 0;
            Tick();
        }
        //Draw
        window.clear();

         // draw background
        for(int i = 0; i < num_horzBox; i++)

            for(int j = 0; j < num_vertBox; j++)
            {
                sprite1.setPosition(i*size,j*size);
                window.draw(sprite1);
            }

        // draw snake1
        for(int i =0; i < snake_length1; i++)
        {
            sprite2.setPosition(s1[i].x1*size, s1[i].y1*size);
            window.draw(sprite2);

        }

        // draw snake
        for(int i =0; i < snake_length2; i++)
        {
            sprite4.setPosition(s2[i].x2*size, s2[i].y2*size);
            window.draw(sprite4);
        }


        // Draw fruit
        sprite3.setPosition(food.x*size, food.y*size);
        window.draw(sprite3);

        window.display();
    }

    return 0;
}
