#include <base.hpp>
TTY *out;
bool tty_set = false;
void setMainTTY(Kobject *obj) {
    if (obj->type == kobjectType::TTY) {
        ++*obj;
        //        if(tty_set)
        //            --*out;
        out = (TTY *)obj;
        tty_set = true;
    }
}
