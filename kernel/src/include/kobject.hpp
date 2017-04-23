#pragma once
enum class kobjectType {
    POINTER, //Pointer to non-object
    KOBJECT, //garbage collected kobject
};
class Kobject {
    public:
        kobjectType type;
        void *ptr;
        unsigned int refctr;
        bool set;
        Kobject(kobjectType type) {
            this->type = type;
            refctr = 1;
            set = false;
        }
        template<typename T>
        auto set(T *data) -> Kobject & {
            if(set)
                return *this;
            ptr = (void*)data;
            set=true;
            return *this;
        }
        template<typename T>
        T *get() {
            return (T*)ptr;
        }
        auto operator++(int) -> Kobject & {
            unsigned int old = refctr;
            refctr++;
            if(old > refctr) {
                //uh-oh this shouldn't happen
                //Put panic() here, because this object could lead to kernel execution when the refctr overflows.
                for(;;);
            }
            return *this;
        }
        auto operator--(int) -> Kobject & {
            refctr--;
            if(!refctr) {
                //delete ptr;
                set = false;
                ptr = nullptr;
            }
            return *this;
        }
};
