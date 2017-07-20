#pragma once
#include <kobject.hpp>
#include <tty.hpp>
extern TTY *out; ///< main TTY for output
/***
 * Sets the main TTY to some other TTY object.
 */
void setMainTTY(TTY *obj);

/**
 * Halts the kernel due to a unresolvable error
 */
extern "C" void panic(const char* s);
