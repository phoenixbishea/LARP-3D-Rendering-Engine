#include "PhysicsPlayerController.hpp"

PhysicsPlayerController::PhysicsPlayerController(PhysicsWorld* physics_world, btVector3 initial_position,
    btScalar forward_speed, btScalar backward_speed, btScalar strafe_speed, btScalar jump_speed, btScalar max_slope)
    : _forward_speed(forward_speed),
      _backward_speed(backward_speed),
      _strafe_speed(strafe_speed),
      _jump_speed(jump_speed)
{
    // Create player shape
    btCylinderShape* player_shape = new btCylinderShape(btVector3(0.2, 0.6, 1.0));

    // Init player ghost object
    this->_ghost_object = new btPairCachingGhostObject();
    this->_transform = this->_ghost_object->getWorldTransform();
    this->_transform.setOrigin(initial_position);

    this->_ghost_object->setWorldTransform(this->_transform);

    // Set the shape and collision object type
    this->_ghost_object->setCollisionShape(player_shape);
    this->_ghost_object->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);

    // Setup the character controller and add it to the physics world
    this->_char_controller =
        new btKinematicCharacterController(this->_ghost_object, player_shape, 1.0);
    this->_char_controller->setGravity(4.9);
    this->_char_controller->setMaxSlope(max_slope);
    this->_char_controller->setJumpSpeed(jump_speed);
    physics_world->get_dynamics_world()->addCollisionObject(
        this->_ghost_object,
        btBroadphaseProxy::CharacterFilter,
        btBroadphaseProxy::StaticFilter | btBroadphaseProxy::DefaultFilter);
    physics_world->get_dynamics_world()->addAction(this->_char_controller);
}

void PhysicsPlayerController::update_movement(PhysicsWorld* world, PhysicsPlayerController::PlayerDirection direction)
{
    // For finding movement vectors:
    //   forward X up = right
    //   up X forward = left
    /*
      And the great thing about transformation matrices, is that this 3x3 rotation sub-matrix
      itself consists of three normalized vectors.
      Turns out, the first column is the vector pointing to the right (positive X axis).
      The column to the right of that is the 'up vector' (positive Y).
      The column next to that, is the vector pointing rearward or forward depending on your
      camera orientation convention (positive Z axis).
      https://www.opengl.org/discussion_boards/showthread.php/175515-Get-Direction-from-Transformation-Matrix-or-Quat
    */
    // btVector3 btFrom = this->_ghost_object->getWorldTransform().getOrigin();
    // btVector3 btTo(btFrom.x(), -0.001f, btFrom.z());
    // btCollisionWorld::ClosestRayResultCallback res(btFrom, btTo);

    // world->get_dynamics_world()->rayTest(btFrom, btTo, res); // m_btWorld is btDiscreteDynamicsWorld


    // /*
    //  * 0.7 is the magic number for detecting whether the player has hit one of the slopes
    //  */
    // if(res.hasHit() && btFrom.y() - res.m_hitPointWorld.y() < 0.7f)
    // {
    //     _char_controller->setGravity(0);
    // }
    // else
    // {
    //     _char_controller->setGravity(4.9);
    // }


    btScalar matrix[16];
    this->_ghost_object->getWorldTransform().getOpenGLMatrix(matrix);

    if (direction == PlayerDirection::STOP)
    {
        _char_controller->setWalkDirection(btVector3(0, 0, 0));
    }

    if (direction == PlayerDirection::FORWARD)
    {
        btVector3 forward(matrix[8], matrix[9], matrix[10]);
        forward *= this->_forward_speed;
        _char_controller->setWalkDirection(forward);
    }
    else if (direction == PlayerDirection::BACKWARD)
    {
        btVector3 forward(matrix[8], matrix[9], matrix[10]);
        forward *= -this->_backward_speed;
        _char_controller->setWalkDirection(forward);
    }
    else if (direction == PlayerDirection::LEFT)
    {
        btVector3 forward(matrix[8], matrix[9], matrix[10]);
        forward *= this->_strafe_speed;
        btVector3 left = btVector3(0, 1, 0).cross(forward);
        _char_controller->setWalkDirection(left);
    }
    else if (direction == PlayerDirection::RIGHT)
    {
        btVector3 forward(matrix[8], matrix[9], matrix[10]);
        forward *= this->_strafe_speed;
        btVector3 right = forward.cross(btVector3(0, 1, 0));
        _char_controller->setWalkDirection(right);
    }
}

void PhysicsPlayerController::rotate(btQuaternion rotation_amount)
{
    btTransform trans = this->_ghost_object->getWorldTransform();
    btQuaternion quat = trans.getRotation();
    quat = rotation_amount * quat;
    trans.setRotation(quat);
    this->_ghost_object->setWorldTransform(trans);
}

void PhysicsPlayerController::jump()
{
     this->_char_controller->jump();
}

void PhysicsPlayerController::set_user_pointer(void * user_pointer)
{
    this->_ghost_object->setUserPointer(user_pointer);
}

void PhysicsPlayerController::step(PhysicsWorld* world, btScalar delta_time)
{
    this->_char_controller->playerStep(world->get_dynamics_world(), delta_time);
}

void * PhysicsPlayerController::get_user_pointer()
{
    return this->_ghost_object->getUserPointer();
}

btVector3 PhysicsPlayerController::get_position() const
{
    return this->_ghost_object->getWorldTransform().getOrigin();
}

btQuaternion PhysicsPlayerController::get_orientation() const
{
    return this->_ghost_object->getWorldTransform().getRotation();
}