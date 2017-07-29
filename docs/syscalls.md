## Syscall list
This list is not complete, but the numbers and the arguments are most likely final

- `exit(int)`
- `void *mmap(void *addr, size_t length, int prot)`
- `void munmap(void *addr, size_t length)`
- `void closeHandle(void *handle)`
- `void *duplicateHandle(void *handle)`
- `void *createService(char name[16], int maxSessions)`
- `void *connectToService(char name[16])`
- `void *replyAndReceive(int * handleEventOut, void ** handles, int handleCount, uint8_t data[256])` - returns a handle if there is a new connection or if a handle has closed the connection
- `void *create_shared(void **handle_out, void* addr, size_t length, int prot, void *tgt_process)` - returns a handle for the other process to map shared memory
- `void *mmap_shared(void* handle, void* addr)`
- `int fork()`
- `int vfork()` - Used for threading
- `int getpid()`
- `int getppid()`
- `int setppid()`

## Example code
Bare-metal (no libc) hello world

    int main() {
        auto tty_handle = connectToService("tty:u");
        if(!tty_handle)
            exit(1);
        union {
            struct {
                int cmd_id;
                char text[252];
            }__attribute__((packed))
            uint8_t data[256];
        } cmdbuf;
        cmdbuf.cmd_id = 1; //1 == puts()
        const char* s = "Hello, World!";
        int i;
        for(i=0;s[i];i++)
            cmdbuf.text[i]=s[i];
        cmdbuf.text[i]=0;
        replyAndReceive(nullptr, &tty_handle, 1, cmdbuf.data); //Passing nullptr to handleEventOut will not wrote a event handle number
        closeHandle(tty_handle);
        exit(1);
    }

