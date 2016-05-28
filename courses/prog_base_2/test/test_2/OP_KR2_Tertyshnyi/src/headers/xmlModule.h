#pragma once

#include "../headers/director.h"

#define XML_FILE_PATH "src/data/Directors.xml"

void xmlModule_parseDirector(director_t **directorSet);
int xmlModule_countDirectors();
