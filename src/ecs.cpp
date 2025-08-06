#include "include/ECS.h"

void Zero_Entity(ComponentStorage* cs, EntityID id) {
    cs->positions[id] = {0};
    cs->has_position[id] = false;

    cs->velocities[id] = {0};
    cs->has_velocity[id] = false;

    cs->sizes[id] = {0};
    cs->has_size[id] = false;

    cs->rotations[id] = {0};
    cs->has_rotation[id] = false;

    cs->sprites[id] = {0};
    cs->has_sprite[id] = false;
}

void ECS_Init(EntityManager* em, ComponentStorage* cs) {
    for(int i = 0; i < MAX_ENTITIES; i++) {
        Zero_Entity(cs, i);
        em->alive[i] = false;
    }
}

EntityID ECS_CreateEntity(EntityManager* em) {
    for(int i = 0; i < MAX_ENTITIES; i++) {
        if(!em->alive[i]) {
            em->alive[i] = true;
            return i;
        }
    }
    return UINT32_MAX;
}

void ECS_DestroyEntity(EntityManager* em, ComponentStorage* cs, EntityID id) {
    em->alive[id] = false;
    Zero_Entity(cs, id);
}

void ECS_AddPosition(ComponentStorage* cs, EntityID id, Position p) {
    cs->positions[id] = p;
    cs->has_position[id] = true;
}
void ECS_RemovePosition(ComponentStorage* cs, EntityID id) {
    cs->positions[id] = {0};
    cs->has_position[id] = false;
}
bool ECS_HasPosition(ComponentStorage* cs, EntityID id) {
    return cs->has_position[id];
}
Position ECS_GetPosition(ComponentStorage* cs, EntityID id) {
    return cs->positions[id];
}

void ECS_AddVelocity(ComponentStorage* cs, EntityID id, Velocity v) {
    cs->velocities[id] = v;
    cs->has_velocity[id] = true;
}
void ECS_RemoveVelocity(ComponentStorage* cs, EntityID id) {
    cs->velocities[id] = {0};
    cs->has_velocity[id] = false;
}
bool ECS_HasVelocity(ComponentStorage* cs, EntityID id) {
    return cs->has_velocity[id];
}
Velocity ECS_GetVelocity(ComponentStorage* cs, EntityID id) {
    return cs->velocities[id];
}

void ECS_AddSize(ComponentStorage* cs, EntityID id, Size s) {
    cs->sizes[id] = s;
    cs->has_size[id] = true;
}
void ECS_RemoveSize(ComponentStorage* cs, EntityID id) {
    cs->sizes[id] = {0};
    cs->has_size[id] = false;
}
bool ECS_HasSize(ComponentStorage* cs, EntityID id) {
    return cs->has_size[id];
}
Size ECS_GetSize(ComponentStorage* cs, EntityID id) {
    return cs->sizes[id];
}

void ECS_AddRotation(ComponentStorage* cs, EntityID id, Rotation r) {
    cs->rotations[id] = r;
    cs->has_rotation[id] = true;
}
void ECS_RemoveRotation(ComponentStorage* cs, EntityID id) {
    cs->rotations[id] = {0};
    cs->has_rotation[id] = false;
}
bool ECS_HasRotation(ComponentStorage* cs, EntityID id) {
    return cs->has_rotation[id];
}
Rotation ECS_GetRotation(ComponentStorage* cs, EntityID id) {
    return cs->rotations[id];
}

void ECS_AddSprite(ComponentStorage* cs, EntityID id, Sprite s) {
    cs->sprites[id] = s;
    cs->has_sprite[id] = true;
}
void ECS_RemoveSprite(ComponentStorage* cs, EntityID id) {
    cs->sprites[id] = {0};
    cs->has_sprite[id] = false;
}
bool ECS_HasSprite(ComponentStorage* cs, EntityID id) {
    return cs->has_sprite[id];
}
Sprite ECS_GetSprite(ComponentStorage* cs, EntityID id) {
    return cs->sprites[id];
}
