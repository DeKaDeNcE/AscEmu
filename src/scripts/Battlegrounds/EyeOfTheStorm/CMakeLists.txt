# Copyright (c) 2014-2021 AscEmu Team <http://www.ascemu.org>

set(PATH_PREFIX EyeOfTheStorm)

set(SRC_EyeOfTheStorm
    ${PATH_PREFIX}/EyeOfTheStorm.cpp
    ${PATH_PREFIX}/EyeOfTheStorm.h
    ${PATH_PREFIX}/EyeOfTheStormDefinitions.h
)

source_group(EyeOfTheStorm FILES ${SRC_EyeOfTheStorm})
unset(PATH_PREFIX)
