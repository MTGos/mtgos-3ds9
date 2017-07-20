# Memory Map File Format
## .mc - Clear text Memory Map
| Identifier | Meaning                                                  |
|------------|----------------------------------------------------------|
|`DEVICETYPE`|Type of the device. One of `PC`, `CONSOLE` and `EMBEDDED` |
|`DEVICENAME`|Pascal strings containing the name of the device          |
|`CPUARCH`   | Architecture. Currently one of `X86`, `X86_64` and `ARM` |
|`ENDIAN`    | `BIG` or `LITTLE`                                        |
|`BITS`      | `32` or `64`                                             |
|`REGION`    | A region of Memory. Arguments are `START_ADDR`, `END_ADDR`, and `PERMISSIONS` (`R`, `RW`, `RX`, `RWX`) Only memory with `RWX`                     permissions can be allocated.                            | 

Example:

    DEVICETYPE CONSOLE
    DEVICENAME 3DS9
    CPUARCH ARM
    ENDIAN LITTLE
    BITS 32
    REGION 0x00000000 0x00008000 RWX
    REGION 0x08000000 0x08100000 RWX
    REGION 0x10000000 0x18000000 RW
    REGION 0x18000000 0x18600000 RW
    REGION 0x1FF00000 0x1FF80000 RW
    REGION 0x1FF80000 0x20000000 RW
    REGION 0x20000000 0x28000000 RW

## .mmap - Compiled Memory Map
### Header

The header is always little-endian

| Offset | Width | Meaning |
|--------|-------|---------|
| `0x00` | 4     | Magic number `MMAP` |
| `0x04` | 4     | Version (Currently 0) |
| `0x08` | 4     | Tag count |

### Tag format

| Offset | Width | Meaning |
|--------|-------|---------|
| `0x00` | 1     | Tag type |
| `0x01` | 1     | Tag size |
| `0x02` | 2     | Paddding  |

### Supported tags
| Tag Type | Size | Name |
|-|-|-|
| `0x00`   | 1    | `DEVICETYPE` |
| `0x01`   | variable | `DEVICENAME` |
| `0x02`   | 1        | `CPUARCH` |
| `0x03`   | 1        | `ENDIAN` |
| `0x04`   | 1        | `BITS`   |
| `0x05`   | `BITS`/4 + 1 | `REGION` |
#### `DEVICETYPE`
| Value | Meaning |
|-|-|
| `0` | `PC` |
| `1` | `CONSOLE` |
| `2` | `EMBEDDED` |

#### `CPUARCH`
| Value | Meaning |
|-|-|
| 0 | `X86` |
| 1 | `X86_64` |
| 2 | `ARM` |

#### `ENDIAN`
| Value | Meaning |
|-|-|
| 0 | `BIG` |
| 1 | `LITTLE` |

#### `BITS`
This is a 8-bit integer

#### `REGION`
| Offset | Length | Meaning |
|-|-|-|
| 0 | `BITS`/8 | Start address |
| `BITS`/8 | `BITS`/8 | End address |
| `BITS`/4 | 1 | Permissions |

Permissions:
| Value | Meaning |
|-|-|
| `0` | No permission |
| `1` | `X` |
| `2` | `W` |
| `3` | `WX`|
| `4` | `R` |
| `5` | `RX` |
| `6` | `RW` |
| `7` | `RWX` |
