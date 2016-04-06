#pragma once
#include <pebble.h>

void delegates_menu_init(char *democrats_[], char *republicans_[]);
void delegates_menu_destroy();
void delegates_menu_show(bool animated);
void delegates_menu_reload();