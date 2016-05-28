#pragma once

#include <time.h>

// Directories management functions.
int dir_exists(const char * dirname);
int dir_printFiles(const char * dirname);

// Files management functions.
int file_exists(const char * filename);
long long file_getSize(const char * filename);
time_t file_getCreateTime(const char * filename);
// Creating and removing files.
int file_create(const char * filename);
int file_remove(const char * filename);
