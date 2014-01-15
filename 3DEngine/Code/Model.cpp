#include "Model.h"

Model::Model()
{
	TripleFloat tf = getPosition();
	tf.y = 500.0f;
	setPosition(tf.x, tf.y, tf.z);
}


Model::~Model()
{
}

void Model::update()
{
	// Gekopieerd van Camera
	/*TripleFloat tf = getPosition();
	tf.x += xMovement;
	tf.y += yMovement;
	tf.z += zMovement;
	setPosition(tf.x, tf.y, tf.z);*/
}