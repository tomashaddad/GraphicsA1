#include "GameManager.h"
#include "GlutHeaders.h"
#include "Enums.h"
#include "Vector.h"
#include "Text.h"

#include <corecrt_math_defines.h>
#include <cmath>

#include <iostream>

GameManager::GameManager()
	: dt_(0),
	  last_time_(0),
	  playing(false),
	  game_over(false)
{
	// diagonal of arena
	const double slope = win_.arena_height_ / win_.arena_width_;
	ship_.setRotation(180.0 * (atan(slope) / M_PI));

	// 1/3 in from the bottom left
	ship_.setStartingPosition(-0.3 * win_.arena_width_, -0.3 * win_.arena_height_);
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
			ship_.drawSpaceShip();
			ship_.drawExhaust();
			ship_.drawBullets(dt_);
			ship_.update(dt_);
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
	double cur_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
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

		for (auto i = 0; i < arena_.getWalls().size(); ++i) {
		}
		for (Wall& wall : arena_.getWalls()) {
			if (wall.checkCollision(ship_pos, win_.arena_width_, win_.arena_height_, ship_warn_r)) {
				wall.setColour(Colour::red);
			}
			else {
				wall.setColour(Colour::white);
			}

			if (wall.checkCollision(ship_pos, win_.arena_width_, win_.arena_height_, ship_coll_r)) {
				game_over = true;
			}

			for (Asteroid& asteroid : asteroid_field_.getAsteroids()) {
				if (asteroid.isInArena()
					&& wall.checkCollision(asteroid.getPosition(),
										   win_.arena_width_, win_.arena_height_,
										   asteroid.getCollisionRadius())) {
					if (wall.getSide() == WallSide::bottom || wall.getSide() == WallSide::top) {
						asteroid.bounceInY(dt_);
					}
					else {
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
			if (asteroid_field_.isEmpty()) {
				for (int i = 0; i < asteroid_field_.asteroidCount(); ++i) {
					asteroid_field_.launchAsteroidAtShip(ship_.getPosition());
				}
				asteroid_field_.increaseAsteroidCountBy(1);
			}
		}
		asteroid_field_.updateAsteroids(dt_, win_.arena_width_, win_.arena_height_);
	}
}

void GameManager::updateAsteroidFieldRadius() {
	asteroid_field_.updateRadius(win_.xmax_ - win_.xmin_,
								 win_.ymax_ - win_.ymin_);
}

void GameManager::checkAsteroidCollisions() {
	if (playing) {
		Vector ship_pos = ship_.getPosition();
		double ship_collision_r = ship_.getCollisionRadius();

		for (Asteroid& a1 : asteroid_field_.getAsteroids()) {
			// Check if any asteroid has collided with the ship
			if (a1.checkCollision(ship_pos, ship_collision_r)) {
				game_over = true;
			}

			for (Asteroid& a2 : asteroid_field_.getAsteroids()) {
				if (a1.getPosition() != a2.getPosition()) {
					if (a1.checkCollision(a2.getPosition(), a2.getCollisionRadius())) {

						double distance_between = a1.getPosition().getDistanceFrom(a2.getPosition());
						distance_between = distance_between - a1.getCollisionRadius() - a2.getCollisionRadius();

						Vector& a1p = a1.getPosition();
						Vector& a2p = a2.getPosition();
						Vector& a1v = a1.getVelocity();
						Vector& a2v = a2.getVelocity();

						Vector un = a1p - a2p;
						un.normalise();
						Vector ut = Vector(-un.y, un.x);

						Vector new_a1_position = a1.getPosition() - (un * 0.5 * distance_between);
						Vector new_a2_position = a2.getPosition() + (un * 0.5 * distance_between);

						a1.setPosition(new_a1_position);
						a2.setPosition(new_a2_position);

						double v1n = un * a1v;
						double v1t = ut * a1v;
						double v2n = un * a2v;
						double v2t = ut * a2v;

						double a1m = a1.getSize();
						double a2m = a2.getSize();

						double new_v1n = (v1n * (a1m - a2m) + (2 * a2m) * v2n) / (a1m + a2m);
						double new_v2n = (v2n * (a2m - a1m) + (2 * a1m) * v1n) / (a1m + a2m);

						Vector new_a1_v = un * new_v1n + ut * v1t;
						Vector new_a2_v = un * new_v2n + ut * v2t;

						a1.setVelocity(new_a1_v);
						a2.setVelocity(new_a2_v);
					}
				}
			}
		}
	}
}

void GameManager::checkBulletCollisions() {
	if (playing) {
		std::array<Wall, 4>& walls = arena_.getWalls();
		std::vector<Asteroid>& asteroids = asteroid_field_.getAsteroids();

		for (Bullet& bullet : ship_.getBulletStream().getBullets()) {
			bool marked = false;
			Vector b_position = bullet.getPosition();

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
	game_over = false;
}