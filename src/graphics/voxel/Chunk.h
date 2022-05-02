#ifndef CHANK_H
#define CHANK_H

#pragma once

#include "Voxel.h"

#define CHUNK_W 36
#define CHUNK_H 36
#define CHUNK_D 36
#define CHUNK_VOL (CHUNK_W * CHUNK_H * CHUNK_D)

class Chunk
{
public:
    Chunk();
    ~Chunk();

    Voxel *voxels;
};

#endif