#pragma once
#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_ENTITIES 1024

typedef uint32_t EntityID;

typedef struct {
    double x;
    double y;
} Position;

typedef struct {
    double x;
    double y;
} Velocity;

typedef struct {
    double w;
    double h;
} Size;

typedef struct {
    double angle;
} Rotation;

typedef struct {
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} Color;

typedef struct {
    SDL_Texture* texture;
    SDL_Rect src;
    Color color;
} Sprite;


typedef struct {
    Position positions[MAX_ENTITIES];
    bool has_position[MAX_ENTITIES];

    Velocity velocities[MAX_ENTITIES];
    bool has_velocity[MAX_ENTITIES];

    Size sizes[MAX_ENTITIES];
    bool has_size[MAX_ENTITIES];

    Rotation rotations[MAX_ENTITIES];
    bool has_rotation[MAX_ENTITIES];

    Sprite sprites[MAX_ENTITIES];
    bool has_sprite[MAX_ENTITIES];
} ComponentStorage;

typedef struct {
    bool alive[MAX_ENTITIES];
} EntityManager;

void ECS_Init(EntityManager* em, ComponentStorage* cs);

EntityID ECS_CreateEntity(EntityManager* em);

void ECS_DestroyEntity(EntityManager* em, ComponentStorage* cs, EntityID id);

void ECS_AddPosition(ComponentStorage* cs, EntityID id, Position p);
void ECS_RemovePosition(ComponentStorage* cs, EntityID id);
bool ECS_HasPosition(ComponentStorage* cs, EntityID id);
Position ECS_GetPosition(ComponentStorage* cs, EntityID id);

void ECS_AddVelocity(ComponentStorage* cs, EntityID id, Velocity v);
void ECS_RemoveVelocity(ComponentStorage* cs, EntityID id);
bool ECS_HasVelocity(ComponentStorage* cs, EntityID id);
Velocity ECS_GetVelocity(ComponentStorage* cs, EntityID id);

void ECS_AddSize(ComponentStorage* cs, EntityID id, Size s);
void ECS_RemoveSize(ComponentStorage* cs, EntityID id);
bool ECS_HasSize(ComponentStorage* cs, EntityID id);
Size ECS_GetSize(ComponentStorage* cs, EntityID id);

void ECS_AddRotation(ComponentStorage* cs, EntityID id, Rotation r);
void ECS_RemoveRotation(ComponentStorage* cs, EntityID id);
bool ECS_HasRotation(ComponentStorage* cs, EntityID id);
Rotation ECS_GetRotation(ComponentStorage* cs, EntityID id);

void ECS_AddSprite(ComponentStorage* cs, EntityID id, Sprite s);
void ECS_RemoveSprite(ComponentStorage* cs, EntityID id);
bool ECS_HasSprite(ComponentStorage* cs, EntityID id);
Sprite ECS_GetSprite(ComponentStorage* cs, EntityID id);