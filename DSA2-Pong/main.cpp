/**
 * Pong, with a twist!
 *
 * Data Structures & Algorithms II
 * Professor Schwartz
 * Section 01
 *
 * @author Bryan Gawinski
 * @author Peter B. Tummillo
 */

#include "ClippingPlanes.h"
#include "DebugDrawing.h"
#include "GameTimer.h"
#include "Text.h"
#include "Viewport.h"
#include "Window.h"

#include <Input/GLKeyboard.h>

#include <Math/Random.h>

#include <Pong/AIPaddle.h>
#include <Pong/Ball.h>
#include <Pong/PlayerPaddle.h>
#include <Pong/Obstacle.h>

#include <Utility/String.h>


// Window
Window window;

// Clipping Planes
ClippingPlanes planes;

// Viewport
Viewport viewport;

// Keyboard
GLKeyboard keyboard;
KeyboardState currState;
KeyboardState prevState;

// Utils
GameTimer timer;

// Paddles
PlayerPaddle player(Point2(25.0f, 300.0f), 15, 80);
AIPaddle ai(Point2(775.0f, 300.0f), 15, 80);

// Ball
Ball ball(Point2(400.0f, 300.0f), 6.0f);

// Obstacles
Obstacle o1(Point2(600.0f, 125.0f), 6, 20.0f);
Obstacle o2(Point2(200.0f, 475.0f), 8, 20.0f);

// UI / Scoring
GLuint playerScore = 0, aiScore = 0;
GLuint points = 1;
GLboolean paused = false;
GLboolean won = false;
string whoWon = "";
const GLuint POINTS_TO_WIN = 10;


void changeSize(GLint width, GLint height)
{
	// Set window size
	window.width = width;
	window.height = height;
	window.centerX = static_cast<GLuint>(width * 0.5f);
	window.centerY = static_cast<GLuint>(height * 0.5f);

	// Use the GL Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset the matrix
	glLoadIdentity();
	
	// Set the clipping region (origin will be in the top-left corner)
	planes.left = 0.0;
	planes.right = width;
	planes.bottom = height;
	planes.top = 0.0;
	gluOrtho2D(planes.left, planes.right, planes.bottom, planes.top);

	// Get back to the ModelView Matrix
	glMatrixMode(GL_MODELVIEW);
}

void checkBall()
{
	float ballRadius = ball.getRadius();
	
	// if the ball hits the wall behind the player paddle, ai scores
	if(ball.position.x + ballRadius < 0.0f)
	{
		aiScore += points;

		if(aiScore == POINTS_TO_WIN)
		{
			whoWon = "AI has won!!!";
			won = true;
		}

		ball.reset( Point2(static_cast<GLfloat>(window.centerX), static_cast<GLfloat>(window.centerY)) );
	}
	// if ball hits the wall behind the ai paddle, player scores
	else if(ball.position.x + ballRadius > window.width)
	{
		playerScore += points;

		if(playerScore == POINTS_TO_WIN)
		{
			whoWon = "Player has won!!!";
			won = true;
		}
		
		ball.reset( Point2(static_cast<GLfloat>(window.centerX), static_cast<GLfloat>(window.centerY)) );
	}
}

void gameInput()
{
	// Game state
	if (currState.isKeyDown(KEY_ESC))
	{
		glutLeaveMainLoop();
	}
	else if (currState.isKeyDown(KEY_SPACE))
	{
		Random random;
		int num = random.getInt(2);
		if (num == 0)
		{
			ball.launch(Vector2(1.0f, random.getFloat(-1.0f, 1.0f)));
		}
		else if (num == 1)
		{
			ball.launch(Vector2(-1.0f, random.getFloat(-1.0f, 1.0f)));
		}
	}
	else if (currState.isKeyDown(KEY_B) && prevState.isKeyUp(KEY_B))
	{
		// Toggle debug drawing
		DebugDrawing::getInstance().enabled = !DebugDrawing::getInstance().enabled;
	}
	else if (currState.isKeyDown(KEY_P) && prevState.isKeyUp(KEY_P))
	{
		if (paused)
		{
			timer.start();

			paused = false;
		}
		else
		{
			keyboard.onPause();

			timer.stop();

			paused = true;
		}
	}
	else if(currState.isKeyDown(KEY_R) && prevState.isKeyUp(KEY_R))
	{
		if (won)
		{
			// reset the string
			whoWon = "";

			// reset the scores of both players
			playerScore = 0;
			aiScore = 0;

			ball.reset(Point2(static_cast<float>(window.centerX), static_cast<float>(window.centerY)));

			won = false;
		}
	}
	
	// Player movement
	if (currState.isKeyDown(KEY_W))
	{
		player.movePaddle(Vector2(0.0f, -1.0f));
	}
	else if (currState.isKeyDown(KEY_S))
	{
		player.movePaddle(Vector2(0.0f, 1.0f));
	}
}

void updateGame(void)
{
	// Get game time
	timer.tick();
	GameTime gameTime = timer.getGameTime();

	// Get input
	keyboard.getState(currState);
	gameInput();

	if (!paused && !won)
	{
		// Update game objects
		ball.update(gameTime, 0, window.height);

		player.update(gameTime, 0, window.height);
		ai.update(gameTime, 0, window.height, ball.position);

		GLuint halfPoints = static_cast<GLuint>(POINTS_TO_WIN * 0.5f);
		if (playerScore >= halfPoints || aiScore >= halfPoints)
		{
			// Increase obstacle speed as the stakes heighten
			GLuint higherScore = std::max(playerScore, aiScore);
			GLuint diff = POINTS_TO_WIN - higherScore;
			float t = 1.0f / diff;

			float minSpeed = 200.0f;
			float maxSpeed = 600.0f;

			float speed = Math::lerp(minSpeed, maxSpeed, t);

			o1.update(gameTime, 125.0f, 475.0f, speed);
			o2.update(gameTime, 125.0f, 475.0f, speed);
		}

		// Resolve collisions
		if(ball.position.distanceToSquared(player.position) <= 50.0f * 50.0f)
		{
			player.checkCollisions(ball);
		}
		else if(ball.position.distanceToSquared(ai.position) <= 50.0f * 50.0f)
		{
			ai.checkCollisions(ball);
		}
		else if(ball.position.distanceToSquared(o1.position) <= 50.0f * 50.0f)
		{
			o1.checkCollisions(ball);
		}
		else if(ball.position.distanceToSquared(o2.position) <= 50.0f * 50.0f)
		{
			o2.checkCollisions(ball);
		}

		// Scoring
		checkBall();

		// Save input state
		prevState = currState;

		// Force game to redisplay
		glutPostRedisplay();
	}
}

void drawUI()
{
	// Draw divider
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(3.0f);
	glLineStipple(1, 4080); // 0000 1111 1111 0000
	glBegin(GL_LINES);
		glVertex2i(window.centerX, 0);
		glVertex2i(window.centerX, window.height);
	glEnd();

	// Draw Scoreboard
	int width = glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, STRINGIFY(playerScore)[0]);
	Text::draw2DString(planes, Point2(window.centerX - (20.0f + width), 40.0f), GLUT_BITMAP_TIMES_ROMAN_24, STRINGIFY(playerScore));
	Text::draw2DString(planes, Point2(window.centerX + 20.0f, 40.0f), GLUT_BITMAP_TIMES_ROMAN_24, STRINGIFY(aiScore));

	// draw out the string for who won
	if (won)
	{
		Text::draw2DString(planes, Point2(335.0f, 270.0f), GLUT_BITMAP_TIMES_ROMAN_24, whoWon);
	}

	// Draw help text if the game is paused
	if(paused)
	{
		Text::draw2DString(planes, Point2(40.0f, 50.0f), GLUT_BITMAP_TIMES_ROMAN_24, "Press B for Debug Drawing");
		Text::draw2DString(planes, Point2(40.0f, 85.0f), GLUT_BITMAP_TIMES_ROMAN_24, "Press W/S to Move Paddle");
		Text::draw2DString(planes, Point2(40.0f, 120.0f), GLUT_BITMAP_TIMES_ROMAN_24, "Press Space to Launch Ball");
		Text::draw2DString(planes, Point2(40.0f, 155.0f), GLUT_BITMAP_TIMES_ROMAN_24, "Press R to reset game after win/loss");
		Text::draw2DString(planes, Point2(40.0f, 190.0f), GLUT_BITMAP_TIMES_ROMAN_24, "Press ESC to close game");
	}
}

void renderGame()
{
	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Set the viewport to the entire window
	viewport.x = 0;
	viewport.y = 0;
	viewport.width = window.width;
	viewport.height = window.height;
	glViewport(viewport.x, viewport.y, viewport.width, viewport.height);

	drawUI();

	// Draw game objects
	ball.draw();

	player.draw();
	ai.draw();

	o1.draw();
	o2.draw();

	// Draw debug stuff
	DebugDrawing::getInstance().draw(timer.getGameTime());

	// Present
	glutSwapBuffers();
}

void keyDown(BYTE keyCode, GLint x, GLint y)
{
	keyboard.handleKeyDownMessage(keyCode);
}

void keyUp(BYTE keyCode, GLint x, GLint y)
{
	keyboard.handleKeyUpMessage(keyCode);
}

// initialize each object that will be shown on screen
void init()
{
	glutIgnoreKeyRepeat(1);

	glEnable(GL_LINE_STIPPLE);

	ball.init();

	player.init();
	ai.init();

	o1.init();
	o2.init();
}

int main(int argc, char** argv)
{
	// Initialize GLUT and create a window
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Gawinski & Tummillo Present: DSA2 - A1                                                                                                    Press P to Pause/Help");
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	
	// Register GLUT callback functions
	glutDisplayFunc(renderGame);
	glutReshapeFunc(changeSize);
	glutIdleFunc(updateGame);

	// Keyboard Functions
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);

	// Initialize
	init();

	// enter the GLUT processing events
	glutMainLoop();

	return 0;
}
