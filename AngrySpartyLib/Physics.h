/**
 * @file Physics.h
 * @author Will Morant
 *
 *
 */

#ifndef PROJECT1_PHYSICS_H
#define PROJECT1_PHYSICS_H

#include <b2_world.h>
#include <b2_body.h>
#include <b2_polygon_shape.h>
#include <b2_mouse_joint.h>
#include <b2_fixture.h>
#include <b2_collision.h>
#include <b2_circle_shape.h>
#include <b2_world_callbacks.h>
#include <b2_contact.h>

/**
 * Physics system for a level.
 */
class Physics {
private:
    /// The box2d world
    b2World mWorld;

    /// A ground reference object
    b2Body* mGround;


public:
    Physics(const b2Vec2& size);

    b2World *GetWorld() {return &mWorld;}


    void UpdateP(double elapsed);


};

#endif //PROJECT1_PHYSICS_H

