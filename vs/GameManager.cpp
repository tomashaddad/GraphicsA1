#include "GameManager.h"
#include "GlutHeaders.h"
#include "Enums.h"
#include "Vector.h"
#include "Text.h"

#include <corecrt_math_defines.h>
#include <cmath>

#include <iostream>

GameManager::GameManager()
	: ship_(black_hole_),
	  asteroid_field_(black_hole_),
	  dt_(0),
	  last_time_(0),
	  playing(false),
	  game_over(false)
{
	// diagonal of arena
	const double slope = win_.arena_height_ / win_.arena_width_;
	ship_.setRotation(180.0 * (atan(slope) / M_PI));

	ship_.setStartingPosition(-0.5 * win_.arena_width_, -0.5 * win_.arena_height_);
}

void GameManager::startGameLoop() {
	glutMainLoop();
}

void GameManager::onDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	arena_.drawArena();

	if (playing) {
		if (!game_over) {
			ship_.drawShip();
			ship_.drawExhaust();
			ship_.drawBullets(dt_);
			ship_.update(dt_);

			black_hole_.draw();
			black_hole_.update(dt_);
		}
		else {
			Text::renderText("Game over! Press any key to play again ...",
				win_.win_width_ / 2.0, win_.win_height_ / 2.0,
				win_.win_width_, win_.win_height_);
		}

		for (Asteroid& asteroid : asteroid_field_.getAsteroids()) {
			asteroid.drawAsteroid();
		}
	}
	else {
		Text::renderText("Press 'B' to begin!",
			win_.win_width_ / 2.0, win_.win_height_ / 2.0,
			win_.win_width_, win_.win_height_);
	}

	int err;
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("display: %s\n", gluErrorString(err));

	glutSwapBuffers();
}

void GameManager::onReshape(const int w, const int h) {
	win_.win_width_ = w;
	win_.win_height_ = h;

	const double aspect_ratio = static_cast<double>(w) / static_cast<double>(h);

	if (w > h) {
		win_.xmin_ = win_.plane_lim_ * -aspect_ratio;
		win_.xmax_ = win_.plane_lim_ * aspect_ratio;
		win_.ymin_ = -win_.plane_lim_;
		win_.ymax_ = win_.plane_lim_;
	}
	else {
		win_.xmin_ = -win_.plane_lim_;
		win_.xmax_ = win_.plane_lim_;
		win_.ymin_ = win_.plane_lim_ / -aspect_ratio;
		win_.ymax_ = win_.plane_lim_ / aspect_ratio;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(win_.xmin_, win_.xmax_, win_.ymin_, win_.ymax_, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, w, h);
}

void GameManager::onKeyDown(const unsigned char key, int x, int y) {
	keyboard_.setKeyState(key, true);
}

void GameManager::onKeyUp(const unsigned char key, int x, int y) {
	keyboard_.setKeyState(key, false);
}

void GameManager::onMouseClick(int button, int state, int x, int y) {
	if (playing) {
		switch (button) {
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN) {
				mouse_.setHoldingLeftClick(true);
			}
			else {
				mouse_.setHoldingLeftClick(false);
			}
			break;
		case GLUT_RIGHT_BUTTON:
			if (state == GLUT_DOWN) {
				mouse_.setHoldingRightClick(true);
			}
			else {
				mouse_.setHoldingRightClick(false);
			}
			break;
		default:
			break;
		}
		glutPostRedisplay();
	}
}

void GameManager::onMouseClickDrag(const int x, const int y)
{
	const double xmouse =
		win_.xmin_ + static_cast<double>(x) / win_.win_width_ * (win_.xmax_ - win_.xmin_);
	const double ymouse =
		win_.ymax_ + static_cast<double>(y) / win_.win_height_ * (win_.ymin_ - win_.ymax_);
	
	mouse_.setMouseCoords(xmouse, ymouse);
}


void GameManager::calculateTimeDelta() {
	// gives delta time in seconds
	const double cur_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	dt_ = cur_time - last_time_;
	last_time_ = cur_time;
}

void GameManager::handleKeyboardInput() {
	// quit
	if (keyboard_.getKeyState('q')) {
		exit(EXIT_SUCCESS);
	}

	if (keyboard_.getKeyState('b') && !playing) {
		playing = true;
	}

	if (playing) {
		// forward/backward (+ acceleration case)
		if (keyboard_.getKeyState('w')) {
			ship_.move(Movement::move_forward, dt_);
		}
		else if (keyboard_.getKeyState('s')) {
			ship_.move(Movement::move_backward, dt_);
		}
		else {
			ship_.setAcceleration(Vector{ 0,0 });
		}

		// rotation
		if (keyboard_.getKeyState('a')) {
			ship_.rotate(Movement::rotate_left, dt_);
		}
		else if (keyboard_.getKeyState('d')) {
			ship_.rotate(Movement::rotate_right, dt_);
		}

		if (keyboard_.getKeyState(' ')) {
			ship_.shootBullet(dt_);
		}
	}

	if (game_over) {
		if (keyboard_.anyKeyIsPressed()) {
			resetGame();
		}
	}

	glutPostRedisplay();
}

void GameManager::handleMouseInput() {
	// allows ship to be moved by click-drag
	if (playing) {
		if (mouse_.isHoldingLeftClick()) {
			ship_.setPosition(mouse_.getMouseCoords());
		}
	}

	//if (mouse_.isHoldingRightClick()) {
	//	// pass dt_ to determine if shooting a bullet is allowed
	//	ship_.shootBullet(dt_);
	//}
}

void GameManager::checkWallCollisions() {
	if (playing) {
		const Vector ship_pos = ship_.getPosition();
		const double ship_warn_r = ship_.getWarningRadius();
		const double ship_coll_r = ship_.getCollisionRadius();

		for (Wall& wall : arena_.getWalls()) {
			// Checking if the ship's warning radius has crossed the arena wall
			if (wall.checkCollision(ship_pos, win_.arena_width_,
				win_.arena_height_, ship_warn_r)) {
				wall.setColour(Colour::red);
			} else {
				wall.setColour(Colour::white);
			}

			// Checking if the ship's collision radius has hit the arena wall
			if (wall.checkCollision(ship_pos, win_.arena_width_,
				win_.arena_height_, ship_coll_r)) {
				game_over = true;
			}

			// Bouncing asteroids on walls
			for (Asteroid& asteroid : asteroid_field_.getAsteroids()) {
				if (asteroid.isInArena()
					&& wall.checkCollision(asteroid.getPosition(),
										   win_.arena_width_, win_.arena_height_,
										   asteroid.getRadius())) {
					if (wall.getSide() == WallSide::bottom ||
						wall.getSide() == WallSide::top) {
						asteroid.bounceInY(dt_);
					} else {
						asteroid.bounceInX(dt_);
					}
				}
			}
		}
	}
}

void GameManager::updateAsteroids() {
	if (playing) {
		// Separate check to keep rendering Asteroids on death
		if (!game_over) {
			if (asteroid_field_.isEmpty() || asteroid_field_.levellingUp()) {
				asteroid_field_.launchAsteroidsAtShip(ship_.getPosition());
				asteroid_field_.increaseAsteroidCountBy(1);
			}
		}
		asteroid_field_.update(dt_, win_.arena_width_, win_.arena_height_);
	}
}

void GameManager::updateAsteroidFieldRadius() {
	asteroid_field_.updateRadius(win_.xmax_ - win_.xmin_,
								 win_.ymax_ - win_.ymin_);
}

void GameManager::checkAsteroidCollisions() {
	//if (playing) {
	//	Vector ship_pos = ship_.getPosition();
	//	double ship_collision_r = ship_.getCollisionRadius();

	//	for (Asteroid& a1 : asteroid_field_.getAsteroids()) {
	//		// Check if any asteroid has collided with the ship
	//		if (a1.checkCollision(ship_pos, ship_collision_r)) {
	//			game_over = true;
	//		}

	//		for (Asteroid& a2 : asteroid_field_.getAsteroids()) {
	//			if (a1.getPosition() != a2.getPosition()) {
	//				if (a1.checkCollision(a2.getPosition(), a2.getRadius())) {
	//					a1.resolveCollisionWith(a2);
	//				}
	//			}
	//		}
	//	}
	//}
}

void GameManager::checkBulletCollisions() {
	if (playing) {
		std::array<Wall, 4>& walls = arena_.getWalls();
		std::vector<Asteroid>& asteroids = asteroid_field_.getAsteroids();

		for (Bullet& bullet : ship_.getBulletStream().getBullets()) {
			bool marked = false; // if bullet is marked to delete, skip loops
			const Vector b_position = bullet.getPosition();

			for (auto i = 0; i < walls.size() && !marked; ++i) {
				if (walls[i].checkCollision(b_position, win_.arena_width_, win_.arena_height_)) {
					bullet.markForDeletion();
					marked = true;
				}
			}

			for (auto i = 0; i < asteroids.size() && !marked; ++i) {
				if (asteroids[i].checkCollision(b_position)) {
					bullet.markForDeletion();
					asteroids[i].decrementHealthBy(1);
					marked = true;
				}
			}
		}
	}
}

void GameManager::resetGame() {
	ship_.reset();
	asteroid_field_.reset();
	black_hole_.reset();

	game_over = false;
}