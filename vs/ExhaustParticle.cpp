#include "ExhaustParticle.h"
#include "ExhaustDefines.h"
#include "GlutHeaders.h"


ExhaustParticle::ExhaustParticle(Vector position)
	: position_(position),
	  size_(EXHAUST_STARTING_SIZE)
{
}

// TODO: Ask about the potential for this to bug out if size_ ever becomes neg
void ExhaustParticle::update(float dt)
{
	size_ -= EXHAUST_DECAY_SPEED * dt; // enforces time to "decay"
}

// Note to self: Changing this from int to float will kill program since
//  this is used for glPointSize() which only likes integers
int ExhaustParticle::size()
{
	return size_;
}

// 5 step sizes (> 4/5, 3/5, 2/5, 1/5, 0) of starting size
void ExhaustParticle::draw()
{
	glPointSize(size_);
	glBegin(GL_POINTS);
	if (size_ > 0.8 * EXHAUST_STARTING_SIZE)
	{
		glColor3f(1.0, 1.0, 1.0);
	}
	else if (size_ > 0.6 * EXHAUST_STARTING_SIZE)
	{
		glColor3f(1.0, 1.0, 0.5);
	}
	else if (size_ > 0.4 * EXHAUST_STARTING_SIZE)
	{
		glColor3f(1.0, 1.0, 0);
	}
	else if (size_ > 0.2 * EXHAUST_STARTING_SIZE)
	{
		glColor3f(1.0, 0.5, 0.0);
	}
	else
	{
		glColor3f(1.0, 0.0, 0.0);
	}
	glVertex2f(position_.x, position_.y);
	glEnd();
}
