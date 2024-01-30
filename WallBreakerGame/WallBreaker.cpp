#include "WallBreaker.h"
#include "raylib.h"

/*
This is our first serious attempt at creating a game using Raylib + C++.

To do that, we will take the game created in class on Session 4 (Wall Breaker) and expand it with the following:

1- Include deltaTime in all speed, movement calculations to make sure
consistent speed is applied across devices


2- Develop a CircleToRoundRectangleCollision to detect the collision that happens
with the corners of the bricks


3- Depending on where the collision happens with the bricks, come up with a direction
that will affect the x and y of the ball's speed


4- Include an unlimited number of levels that are created procedurally.
Each time you spawn the game, a new layout should be displayed


5- Have pickups such as life that fall from certain bricks upon impact.
Collecting them by the player, will activate the reward.


6- Include a cheat. Such as a pickup that temporarily (for instance for the next 5 seconds)
[with a time feedback for the user] eliminates the reversal of speed upon impact with bricks.


7- Bonus -> Include sound effects
8- Bonus -> Find a way to put the game on your phone
*/




void WallBreaker::Main()
{
	InitWindow(screenWidth, screenHeight, "Wall Breaker");

	Start();

	SetTargetFPS(180); // This will become important
	while (!WindowShouldClose())
	{
		Update();
	}
	CloseWindow();
}

void WallBreaker::Start()
{
#pragma region BRICKS
	float spaceForBricks = screenWidth - (BRICKS_PER_ROW * GAP + GAP);
	Vector2 brickSize = Vector2{ spaceForBricks / BRICKS_PER_ROW, BRICK_HEIGHT };

	bricks.clear();

	for (int row = 0; row < ROWS_OF_BRICKS; row++)
	{
		for (int col = 0; col < BRICKS_PER_ROW; col++)
		{
			float x = GAP + (GAP + brickSize.x) * col;
			float y = GAP + (GAP + brickSize.y) * row;

			Rectangle rect = Rectangle{ x, y, brickSize.x, brickSize.y };
			
			Brick brick = Brick{ colors[row], rect};

			bricks.push_back(brick);
		}
	}
#pragma endregion 

#pragma region PLAYER
	player.position = Vector2{ screenWidth / 2, screenHeight * 9 / 10 };
	player.size = Vector2{ screenWidth / 10 , 20 };
	player.curLife = MAX_LIVES; // at the beginning
#pragma endregion


	ball.position = Vector2{ screenWidth / 2, screenHeight * 9 / 10 - 30 };
}

void WallBreaker::EvalCurFrame()
{
	if (gameOver)
	{
		if (IsKeyPressed(KEY_ENTER))
		{
			Start();
			gameOver = false;
		}

		return;
	}

	if (IsKeyPressed(KEY_P))
		gamePaused = !gamePaused;

	if (gamePaused) return;


	if (!ball.active)
	{
		ball.position = Vector2{ player.position.x, screenHeight * 9 / 10 - 30 };

		if (IsKeyPressed(KEY_SPACE))
		{
			ball.active = true;
			ball.speed = Vector2{ 0, -5 };
		}
	}
	else
	{
		ball.position.x += ball.speed.x;
		ball.position.y += ball.speed.y;
	}

	// player position
	if (IsKeyDown(KEY_LEFT))
		player.position.x -= 5;

	// we have reached the far left
	if (player.position.x - player.size.x / 2 <= 0)
		player.position.x = player.size.x / 2; // stick it to the far left

	// we have reached the far right
	if (player.position.x + player.size.x / 2 >= screenWidth)
		player.position.x = screenWidth - player.size.x / 2; // stick it to the far right

	if (IsKeyDown(KEY_RIGHT))
		player.position.x += 5;


	// Collision with the Bricks
	for (int i = 0; i < bricks.size(); i++)
	{
		if (CheckCollisionCircleRec(ball.position, ball.radius, bricks[i].rect))
		{
			// delete the brick
			bricks.erase(bricks.begin() + i);

			// reverse the direction of the ball
			ball.speed.y *= -1;

			break; // Because the ball might hit two bricks at the same frame		
		}
	}

	// Colision with the pedal
	if (CheckCollisionCircleRec(ball.position, ball.radius, player.GetRect()))
	{
		if (ball.speed.y > 0) // we are going downwards
		{
			ball.speed.y *= -1;
			ball.speed.x = (ball.position.x - player.position.x) / (player.size.x / 10);
		}
	}

	// collision with the walls
	if ((ball.position.x + ball.radius >= screenWidth) || ball.position.x - ball.radius <= 0)
		ball.speed.x *= -1;
	if (ball.position.y - ball.radius <= 0) // we hit the top
		ball.speed.y *= -1;
	if (ball.position.y + ball.radius >= screenHeight)
	{
		player.curLife--;
		ball.active = false;
		ball.speed = Vector2{ 0 , 0 };
	}


	if (player.curLife == 0)
		gameOver = true;
	else
	{
		if (bricks.size() == 0)
			levelWon = true;
	}


}


void WallBreaker::DrawCurFrame()
{
	BeginDrawing();
	ClearBackground(BLACK);

	if (gameOver)
	{
		DrawText("Press Enter to play again",
			GetScreenWidth() / 2 - MeasureText("Press Enter to play again", 30) / 2,
			GetScreenHeight() / 2 - 15,
			30, GRAY);
	}
	else if (levelWon)
	{
		DrawText("You Won! Press Enter to go to next level!",
			GetScreenWidth() / 2 - MeasureText("You Won! Press Enter to go to next level!", 30) / 2,
			GetScreenHeight() / 2 - 15,
			30, GRAY);
	}
	else
	{
		player.Draw();
		ball.Draw();

		for (Brick b : bricks)
			b.Draw();


		// draw player lives!
		for (int i = 0; i < MAX_LIVES; i++)
		{
			if (i < player.curLife)
				DrawRectangle(10 + 40 * i, screenHeight - 20, 30, 10, LIGHTGRAY);
			else
				DrawRectangle(10 + 40 * i, screenHeight - 20, 30, 10, GRAY);
		}
	}





	EndDrawing();
}

void WallBreaker::Update()
{
	EvalCurFrame();
	DrawCurFrame();
}

