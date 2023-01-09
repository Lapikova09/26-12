#include <SFML/Graphics.hpp>
#include "Header.h"
#include "functions.h"

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
    window.setFramerateLimit(FPS);

    RectangleShape Bat;
    Bat.setSize(BAT_SIZE);
    Bat.setFillColor(BAT_COLOR);
    Bat.setPosition(BAT_OFFSET_X, BAT_OFFSET_Y);

    CircleShape ball(BALL_RADIUS);
    ball.setFillColor(BALL_COLOR);
    ball.setPosition((WINDOW_WIDTH - 2 * BALL_RADIUS) / 2,
        (WINDOW_HEIGHT - 2 * BALL_RADIUS) / 2);

    float ballSpeedX = 2.f;
    float ballSpeedY = 2.f;

    Font font;
    font.loadFromFile("DS-DIGIB.ttf");
    int Score = 0;
    Text text;
    text.setString(std::to_string(Score));
    text.setFont(font);
    text.setCharacterSize(FONT_SIZE);
    text.setPosition(TEXT_POS);
    Text finish;
    finish.setString(end);
    finish.setFont(font);
    finish.setCharacterSize(60);
    finish.setPosition(300.f, 100.f);


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }


        ball.move(ballSpeedX, ballSpeedY);
        if (ball.getPosition().x <= 0)
        {
            ballSpeedX = -ballSpeedX;
        }
        if (ball.getPosition().x + 2 * BALL_RADIUS >= WINDOW_WIDTH) {
            ballSpeedX = -ballSpeedX;
        }
        if (
            ball.getPosition().y + 2 * BALL_RADIUS >= WINDOW_HEIGHT)
        {
            ballSpeedY = -ballSpeedY;
            Score++;
            text.setString(std::to_string(Score));
        }
        if (ball.getPosition().y <= 0) {
            ballSpeedY = -ballSpeedY;
        }
      
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            Bat.move(-BAT_DY,0.f);
        }
        else if (Keyboard::isKeyPressed(Keyboard::D)) {
            Bat.move(BAT_DY,0.f);
        }
        if (Bat.getPosition().x < 0) {
            Bat.setPosition(Vector2f( 0.f, BAT_OFFSET_Y));
        }
        if (Bat.getPosition().x > WINDOW_WIDTH - BAT_WIDTH) {
            Bat.setPosition(Vector2f(WINDOW_WIDTH - BAT_WIDTH, BAT_OFFSET_Y));
        }
        if (Score == 5) {
            ballSpeedX = 0.f;
            ballSpeedY = 0.f;
            ball.setPosition(10.f, 10.f);
            window.clear();
            window.draw(finish);
            window.display();
       }

        Vector2f left{ ball.getPosition().x + 2 * BALL_RADIUS,ball.getPosition().y};
        Vector2f mid{ ball.getPosition().x + BALL_RADIUS,ball.getPosition().y};//?
        Vector2f right{ ball.getPosition().x,ball.getPosition().y +2*BALL_RADIUS};
        Vector2f midleft{ ball.getPosition().x + 2 * BALL_RADIUS,ball.getPosition().y + BALL_RADIUS };
        Vector2f midright{ ball.getPosition().x,ball.getPosition().y + BALL_RADIUS };
        Vector2f bottomleft{ ball.getPosition().x + 2 * BALL_RADIUS,ball.getPosition().y + 2 * BALL_RADIUS };
        Vector2f bottomright{ ball.getPosition().x,ball.getPosition().y + 2 * BALL_RADIUS };

        if (pointInRect(Bat, mid) && pointInRect(Bat, left) ||
            pointInRect(Bat, mid) && pointInRect(Bat, right)) {
            ballSpeedY = -ballSpeedY;
        }
        if (pointInRect(Bat, right) && pointInRect(Bat, midright) ||
            pointInRect(Bat, bottomright) && pointInRect(Bat, midright)) {
            ballSpeedX = -ballSpeedX;
        }
        if (pointInRect(Bat, midleft) && pointInRect(Bat, left) ||
            pointInRect(Bat, midleft) && pointInRect(Bat, bottomleft)) {
            ballSpeedX = -ballSpeedX;
        }
        if(pointInRect(Bat, left) || pointInRect(Bat, right)) {
            ballSpeedY = -ballSpeedY;
        }

        window.clear();
        window.draw(Bat);
        window.draw(ball);
        window.draw(text);
        window.display();
    }

    return 0;
}