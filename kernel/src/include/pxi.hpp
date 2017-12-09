#pragma once
#include <function.hpp>
struct PXIcmd {
    uint32_t conid;
    uint32_t cmdid;
    uint32_t args[14];
};

enum class ErrorCode {
    SUCCESS,
    SEGV,
    UNKNOWN
};

struct PXIreply {
    uint32_t conid;
    ErrorCode err;
    uint32_t resp[14];
};

struct PXI {
    PXIcmd command;
    function<PXIreply(PXIcmd)> pxi_handlers[16];
    uint32_t connid;
    PXI();
    ~PXI();

    void set_cmd_handler(uint32_t cmd, function<PXIreply(PXIcmd)> handler);
    void send_cmd(PXIcmd command, function<void(PXIreplay)> callback);
    void main_loop();

    void 
};

extern PXI pxi;
