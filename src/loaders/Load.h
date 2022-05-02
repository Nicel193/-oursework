#ifndef LOADPNG_H
#define LOADPNG_H

#pragma once

#include <string>
#include <iostream>

class Texture;

extern Texture* load_texture(std::string filename);

#endif