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

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
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

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    updateScoreboard(window, label, points);
    double speed = drand48();
    if (speed > 0.5)
    speed = 0.13;
    else speed = -0.13;
    double velx = speed;
    double vely = 0.13;
    
    if (lives > 0)
    waitForClick();

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        GEvent event = getNextEvent(MOUSE_EVENT);
        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event) - getWidth(paddle) / 2;
                if (getX(event) >= WIDTH - getWidth(paddle)/2)
                setLocation(paddle, WIDTH-getWidth(paddle), 530);
                else if ((getX(event) - getWidth(paddle)/2) <= 0)
                setLocation(paddle, 0, 530);
                else setLocation(paddle, x, 530);
            }
        }
            move(ball, velx, vely);
            if (getX(ball) + getWidth(ball) >= getWidth(window))
            {
                if (velx>0.0 && vely>0.0)
                {
                   velx = -velx;  
                }
                else if (velx>0.0 && vely<0.0)
                {
                    velx = -velx; 
                }
            }    
            else if (getX(ball) <= 0)
            {
                if (velx<0.0 && vely>0.0)
                {
                   velx = -velx;  
                }
                else if (velx<0.0 && vely<0.0)
                {
                    velx = -velx; 
                }
            }    
            else if (getY(ball) + getHeight(ball) >= getHeight(window))
            {
                lives--;
                //updateScoreboard(window, label, lives);
                double x_m = getX(ball);
                setLocation(ball, x_m, HEIGHT-2*RADIUS);
                if (lives > 0)
                {             
                waitForClick();
                setLocation(ball, WIDTH/2-RADIUS, HEIGHT/2-RADIUS);
                setLocation(paddle, 165, 530);
                waitForClick();
                move(ball, velx, vely);
                }
            }
            else if (getY(ball) <= 0)
            {
                if (velx>0.0 && vely<0.0)
                {
                   vely = -vely;  
                }
                else if (velx<0.0 && vely<0.0)
                {
                    vely = -vely; 
                }
            }
            GObject object = detectCollision(window, ball);
            if (object != NULL)
            {
                if (object == paddle)
                {
                    //removeGWindow(window, paddle);
                        if (velx>0.0 && vely>0.0)
                        {
                           vely = -vely;  
                        }
                        else if (velx<0.0 && vely>0.0)
                        {
                            vely = -vely; 
                        } 
                }
                
                int n = getWidth(object);
                if (n == 34)
                {
                    vely = -vely;
                    removeGWindow(window, object);
                    points++;
                    bricks--;
                    updateScoreboard(window, label, points);
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
    double y_br = 50.0;
    string color[ROWS] = {"RED", "ORANGE", "YELLOW" ,"GREEN", "PINK"};
    for (int i = 0; i < ROWS; i++)
    {
        double x_br = 3.0;
        for (int j = 0; j < COLS; j++)
        {
            GRect brick = newGRect(x_br, y_br, 34, 12);
            setColor(brick, color[i]);
            setFilled(brick, true);
            add(window, brick);
            x_br += 40.0;
        }
        y_br += 18.0;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval bal = newGOval(WIDTH/2-RADIUS, HEIGHT/2-RADIUS, RADIUS*2, RADIUS*2);
    setColor(bal, "BLACK");
    setFilled(bal, true);
    add(window, bal);
    return bal;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect pad = newGRect(165, 530, 70, 10);
    setColor(pad, "BLUE");
    setFilled(pad, true);
    add(window, pad);
    
    return pad;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-36");
    setColor(label, "00ffff");
    add(window, label);
    
    return label;
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
