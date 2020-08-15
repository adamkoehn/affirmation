#ifndef INCLUDE_NOTIFICATION_H
#define INCLUDE_NOTIFICATION_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int notification_path(char *path);

int notification_total();

int notification_random(int lines, char *summary, char *body);

#endif