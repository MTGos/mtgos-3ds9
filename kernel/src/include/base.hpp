#pragma once
#include <kobject.hpp>
#include <tty.hpp>
extern TTY *out; ///< main TTY for output
/***
 * Sets the main TTY to some other TTY object.
 */
void setMainTTY(Kobject *obj);
