#include <raylib.h>

static void moveBall(Vector2 *ballPosition, float ballSize,
                     Vector2 *ballDirection, float ballSpeed, Vector2 *player,
                     Vector2 *playerSize, int screenWidth, int screenHeight);
static bool ballWillHitPlayer(Vector2 *ballPosition, float ballSize,
                              Vector2 *ballDirection, Vector2 *player,
                              Vector2 *playerSize);
static void playerBallInteraction(Vector2 *ballPosition, float ballSize,
                                  Vector2 *ballDirection, Vector2 *player,
                                  Vector2 *playerSize);
static bool isDead(Vector2 *ballPosition, float limit);

static void reset(Vector2 *ballPosition, Vector2 *ballDirection,
                  float *ballSpeed, Vector2 *player);

int main(void) {
  const int screenWidth = 600;
  const int screenHeight = 800;
  InitWindow(screenWidth, screenHeight, "Breakout");

  Vector2 player;
  Vector2 playerSize = (Vector2){50.0f, 10.0f};
  int moveStep = 3;

  Vector2 ballPosition;
  float ballSize = 6.0f;
  float ballSpeed = 1.0f;
  Vector2 ballDirection;
  reset(&ballPosition, &ballDirection, &ballSpeed, &player);

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    if (IsKeyDown(KEY_Q)) {
      break;
    }

    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A) || IsKeyDown(KEY_H)) {
      if (player.x >= moveStep) {
        player.x -= moveStep;
      }
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D) || IsKeyDown(KEY_L)) {
      if (player.x + playerSize.x <= screenWidth) {
        player.x += moveStep;
      }
    }

    moveBall(&ballPosition, ballSize, &ballDirection, ballSpeed, &player,
             &playerSize, screenWidth, screenHeight);

    if (ballPosition.y >= player.y + playerSize.y) {
      reset(&ballPosition, &ballDirection, &ballSpeed, &player);
    }

    BeginDrawing();

    ClearBackground(BLACK);
    DrawRectangleV(player, playerSize, GREEN);
    DrawCircleV(ballPosition, ballSize, WHITE);
    DrawRectangle(0, player.y + playerSize.y, screenWidth, 3, GRAY);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}

static void moveBall(Vector2 *ballPosition, float ballSize,
                     Vector2 *ballDirection, float ballSpeed, Vector2 *player,
                     Vector2 *playerSize, int screenWidth, int screenHeight) {
  // Invert ballDirection
  // ------------------------------------------
  if (ballDirection->x < 0 && ballPosition->x - ballSize < 0) {
    ballDirection->x *= -1;
  }
  if (ballDirection->x > 0 && ballPosition->x + ballSize > screenWidth) {
    ballDirection->x *= -1;
  }
  if (ballDirection->y < 0 && ballPosition->y - ballSize < 0) {
    ballDirection->y *= -1;
  }
  if (ballDirection->y > 0 && ballPosition->y + ballSize > screenHeight) {
    ballDirection->y *= -1;
  }
  if (ballWillHitPlayer(ballPosition, ballSize, ballDirection, player,
                        playerSize)) {
    playerBallInteraction(ballPosition, ballSize, ballDirection, player,
                          playerSize);
  }

  // The actual Ball Movement
  // --------------------------------------------
  ballSpeed += 0.1f;
  ballPosition->x += ballDirection->x + ballSpeed;
  ballPosition->y += ballDirection->y + ballSpeed;
}

static bool ballWillHitPlayer(Vector2 *ballPosition, float ballSize,
                              Vector2 *ballDirection, Vector2 *player,
                              Vector2 *playerSize) {
  float nextX = ballPosition->x + ballDirection->x;
  float nextY = ballPosition->y + ballDirection->y;

  float ballLeft = nextX - ballSize;
  float ballRight = nextX + ballSize;
  float ballUp = nextY - ballSize;
  float ballDown = nextY + ballSize;

  float playerLeft = player->x;
  float playerRight = player->x + playerSize->x;
  float playerUp = player->y;
  float playerDown = player->y + playerSize->y;

  if (ballRight <= playerLeft || ballLeft >= playerRight ||
      ballUp >= playerDown || ballDown <= playerUp) {
    return false;
  }

  return true;
}

static void playerBallInteraction(Vector2 *ballPosition, float ballSize,
                                  Vector2 *ballDirection, Vector2 *player,
                                  Vector2 *playerSize) {
  ballDirection->y *= -1;
}

static void reset(Vector2 *ballPosition, Vector2 *ballDirection,
                  float *ballSpeed, Vector2 *player) {
  ballPosition->x = 300.0f;
  ballPosition->y = 400.0f;

  ballDirection->x = 1.0f;
  ballDirection->y = 2.0f;

  *ballSpeed = 1.0f;

  player->x = 300.0f;
  player->y = 700.0f;
}
