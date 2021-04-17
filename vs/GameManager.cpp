#include "GameManager.h"
#include "GlutHeaders.h"
#include "Enums.h"
#include "Vector.h"
#include "Text.h"
#include "Utility.h"

#include <corecrt_math_defines.h>
#include <cmath>

#include <iostream>
#include <memory>

GameManager::GameManager()
	: ship_(black_hole_),
	  arena_(win_),
	  asteroid_field_(black_hole_),
	  dt_(0),
	  last_time_(0),
	  playing_(false),
	  game_over_(false)
{
	// diagonal of arena
	const double slope = win_.arena_height_ / win_.arena_width_;
	ship_.setRotation(180.0 * (atan(slope) / M_PI));
	ship_.setStartingPosition(-0.5 * win_.arena_width_, -0.5 * win_.arena_height_);
	
	black_hole_.randomisePosition(win_.arena_width_, win_.arena_height_);
}

void GameManager::startGameLoop() {
	glutMainLoop();
}

void GameManager::onDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	arena_.drawArena();
	
	if (!explosions_.isEmpty()) {
		explosions_.update(dt_);
	}

	if (playing_) {
		if (!game_over_) {
			arena_.update(dt_);
			ship_.drawShip();
			ship_.drawExhaust();
			ship_.drawBullets(dt_);
			ship_.update(dt_);
		}
		else {
			Text::renderText("Game over! Press any key to play again ...",
				win_.win_width_ / 2.0,
				win_.win_height_ / 2.0,
				win_.win_width_,
				win_.win_height_);
		}
		black_hole_.draw();
		black_hole_.update(dt_);

		for (Asteroid& asteroid : asteroid_field_.getAsteroids()) {
			asteroid.draw();
		}

		for (ExplosionParticle& explosion_particle : explosions_.getExplosions()) {
			explosion_particle.draw();
		}
	}
	else {
		Text::renderText("Press 'B' to begin!",
			win_.win_width_ / 2.0,
			win_.win_height_ / 2.0,
			win_.win_width_,
			win_.win_height_);
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
	if (playing_) {
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

// Converts between window and world coordinates for moving the ship with mouse
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

	if (keyboard_.getKeyState('b') && !playing_) {
		playing_ = true;
	}

	if (playing_) {
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
		
		// Shoot bullets with space bar
		// Makes it easier to play on a laptop
		//if (keyboard_.getKeyState(' ')) {
		//	ship_.shootBullet(dt_);
		//}
	}

	if (game_over_) {
		if (keyboard_.anyKeyIsPressed()) {
			resetGame();
		}
	}

	glutPostRedisplay();
}

void GameManager::handleMouseInput() {
	if (mouse_.isHoldingLeftClick()) {
		ship_.shootBullet(dt_);
	}
	
	// allows ship to be moved by click-drag if you need to, Tony!
	//if (playing_) {
	//	if (mouse_.isHoldingRightClick()) {
	//		ship_.setPosition(mouse_.getMouseCoords());
	//	}
	//}
}

void GameManager::checkWallCollisions() {
	if (playing_) {
		const Vector ship_pos = ship_.getPosition();
		const double ship_warn_r = ship_.getWarningRadius();
		const double ship_coll_r = ship_.getCollisionRadius();

		for (Wall& wall : arena_.getWalls()) {
			// SHIP->WALL COLLISION ///////////////
			// Warning
			if (wall.checkCollision(ship_pos, win_.arena_width_,
				win_.arena_height_, ship_warn_r)) {
				wall.setColour(Colour::red);
			} else {
				wall.setColour(Colour::white);
			}

			// Collision
			if (wall.checkCollision(ship_pos, win_.arena_width_,
				win_.arena_height_, ship_coll_r)) {
				game_over_ = true;
			}
			
			// ASTEROID->WALL COLLISION ///////////////
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
	if (playing_) {
		// Separate check to keep rendering Asteroids on death
		if (!game_over_) {
			if (asteroid_field_.isEmpty() || asteroid_field_.levellingUp()) {
				// Reset timer to prevent two waves spawning back to back
				if (asteroid_field_.isEmpty()) {
					asteroid_field_.resetTimer();
				}
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
	if (playing_) {
		const Vector ship_pos = ship_.getPosition();
		const double ship_collision_r = ship_.getCollisionRadius();

		for (Asteroid& a1 : asteroid_field_.getAsteroids()) {
			const Vector a1_pos = a1.getPosition();
			const double a1_radius = a1.getRadius();

			
			// SHIP->ASTEROID COLLISION ///////////////
			if (Utility::checkCollision(a1_pos, ship_pos, a1_radius, ship_collision_r)) {
				game_over_ = true;
			}

			// ASTEROID->ASTEROID COLLISION ///////////////
			for (Asteroid& a2 : asteroid_field_.getAsteroids()) {
				const Vector a2_pos = a2.getPosition();
				const double a2_radius = a2.getRadius();
				if (a1.getPosition() != a2.getPosition()) {
					if (Utility::checkCollision(a1_pos, a2_pos, a1_radius, a2_radius)) {
						a1.resolveCollisionWith(a2);
					}
				}
			}
		}
	}
}

void GameManager::checkBulletCollisions() {
	if (playing_) {
		std::array<Wall, 4>& walls = arena_.getWalls();
		std::vector<Asteroid>& asteroids = asteroid_field_.getAsteroids();

		for (std::unique_ptr<Bullet>& bullet : ship_.getBulletStream().getBullets()) {
			bool marked = false; // if bullet is marked to delete, skip loops
			const Vector b_position = bullet->getPosition();

			// BULLET->WALL COLLISION ///////////////
			for (auto i = 0; i < walls.size() && !marked; ++i) {
				if (walls[i].checkCollision(b_position, win_.arena_width_, win_.arena_height_)) {
					bullet->markForDeletion();
					marked = true;
				}
			}

			// BULLET->ASTEROID COLLISION ///////////////
			for (auto i = 0; i < asteroids.size() && !marked; ++i) {
				if (Utility::checkCollision(asteroids[i].getPosition(), b_position, asteroids[i].getRadius()))
				{
					bullet->markForDeletion();
					asteroids[i].decrementHealthBy(1);
					if (asteroids[i].health() <= 0) {
						arena_.increasePointsBy(1);
						explosions_.populate(asteroids[i].getPosition());
					}
					marked = true;
				}
			}
		}
	}
}

void GameManager::checkBlackHoleCollisions() {
	if (playing_) {
		// SHIP->HOLE COLLISION ///////////////
		if (Utility::checkCollision(ship_.getPosition(), black_hole_.getPosition(),
			ship_.getCollisionRadius(), black_hole_.getRadius())) {
			game_over_ = true;
		}

		// ASTEROID->HOLE COLLISION ///////////////
		for (Asteroid& asteroid : asteroid_field_.getAsteroids()) {
			if (Utility::checkCollision(asteroid.getPosition(), black_hole_.getPosition(),
				asteroid.getRadius(), black_hole_.getRadius())) {
				explosions_.populate(asteroid.getPosition());
				asteroid.markForDeletion();
			}
		}

		// BULLET->HOLE COLLISION ///////////////
		for (std::unique_ptr<Bullet>& bullet : ship_.getBulletStream().getBullets()) {
			if (Utility::checkCollision(black_hole_.getPosition(), bullet->getPosition(),
				black_hole_.getRadius())) {
				bullet->markForDeletion();
			}
		}
	}
}

void GameManager::resetGame() {
	arena_.reset();
	ship_.reset();
	asteroid_field_.reset();
	explosions_.reset();
	black_hole_.reset();
	black_hole_.randomisePosition(win_.arena_width_, win_.arena_height_);
	game_over_ = false;
}