/*
Copyright (c) 2014-2020 AscEmu Team <http://www.ascemu.org>
This file is released under the MIT license. See README-MIT for more information.
*/

#pragma once

#include "../world/WorldConf.h"

#if VERSION_STRING == Classic
    #include "../world/GameClassic/UpdateFields.h"
#elif VERSION_STRING == TBC
    #include "../world/GameTBC/UpdateFields.h"
#elif VERSION_STRING == WotLK
    #include "../world/GameWotLK/UpdateFields.h"
#elif VERSION_STRING == Cata
    #include "../world/GameCata/UpdateFields.h"
#elif VERSION_STRING == Mop
#include "../world/GameMop/UpdateFields.h"
#endif

#include <stddef.h>

#define getOffsetForStructuredField(s,m) static_cast<uint32_t>(offsetof(s,m) / 4)

#define getSizeOfStructure(s) static_cast<uint32_t>(sizeof(s) / 4)

