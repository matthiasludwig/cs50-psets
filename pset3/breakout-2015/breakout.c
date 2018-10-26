//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

//height and width of the paddle
#define PADHEIGHT 11
#define PADWIDTH 60

// number of rows of bricks
#define ROWS 5
//number of columns of bricks
#define COLS 10
//positioning dimensions of the bricks
#define DISTOTOP 50
#define BRIHEIGHT 11
#define BRIWIDTH 36
#define BRISPACED 4

// radius and velocity of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks - DONE
    initBricks(window);

    // instantiate ball, centered in middle of window - DONE
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window - DONE
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially and show scoreoboard
    int points = 0;
    updateScoreboard(window, label, points);
    
    //velocity of the ball
    double yvelocity = 2.0;
    double xvelocity = drand48() * 2.0;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        //PADDLE MOVEMENT
        GEvent event = getNextEvent(MOUSE_EVENT);

        //if mouse event happened
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure paddle cursor
                double x = getX(event) - (PADWIDTH / 2);
                setLocation(paddle, x, HEIGHT - 50);
            }
        }
        //BALL MOVEMENT
        
        move(ball, xvelocity, yvelocity);

        // bounce off right edge of window
        if (getX(ball) + RADIUS * 2 >= WIDTH)
        {
            xvelocity = -xvelocity;
        }

        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            xvelocity = -xvelocity;
        }
        // loose live bottom edge
        else if (getY(ball) + RADIUS * 2 >= HEIGHT)
        {
            lives--;
            waitForClick();
            removeGWindow(window, ball);
            ball = initBall(window);
            xvelocity = -xvelocity;
        }

        // bounce off top of window
        else if (getY(ball) <= 0)
        {
            yvelocity = -yvelocity;
        }

        // linger before moving again
        pause(10);
        
        
        
        //DETECTCOLLION WITH PADDLE AND BRICKS
        
        GObject object = detectCollision(window, ball);
        
        if (object != NULL)
        {
            if (strcmp(getType(object), "GRect") == 0)
            {
                if (object == paddle)
                    yvelocity = -yvelocity;
                else
                {
                    removeGWindow(window, object);
                    yvelocity = -yvelocity;
                    points++;
                    updateScoreboard(window, label, points);
                }
            }
        }
    }
    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    string colors[5] = {"RED", "ORANGE", "YELLOW", "GREEN", "BLUE"};
    for (int i = 0; i < ROWS; i++)
    {
        int y = 50 + (i * (BRIHEIGHT + BRISPACED));
        
        for (int j = 0; j < COLS; j++)
        {
            int x = 2 + (j * (BRIWIDTH + 4));
            GRect brick = newGRect(x, y, BRIWIDTH, BRIHEIGHT);
            setFilled(brick, true);
            setColor(brick, colors[i]);
            add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    int x = (WIDTH / 2) - RADIUS;
    int y = (HEIGHT / 2) - RADIUS;
    
    GOval ball = newGOval(x, y, RADIUS * 2, RADIUS * 2);
    setFilled(ball, true);
    setColor(ball, "BLACK");
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    int x = (WIDTH / 2) - (PADWIDTH / 2);
    int y = HEIGHT - 50;
    
    GRect paddle = newGRect(x, y, PADWIDTH, PADHEIGHT);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel scoreboard = newGLabel("");
    setFont(scoreboard, "SansSerif-36");
    setColor(scoreboard, "GRAY");
    add(window, scoreboard);
    return scoreboard;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
