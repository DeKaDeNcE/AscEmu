# Copyright (c) 2014-2021 AscEmu Team <http://www.ascemu.org>

set(PATH_PREFIX ArathiBasin)

set(SRC_ArathiBasin
    ${PATH_PREFIX}/ArathiBasin.cpp
    ${PATH_PREFIX}/ArathiBasin.h
    ${PATH_PREFIX}/ArathiBasinDefinitions.h
)

source_group(ArathiBasin FILES ${SRC_ArathiBasin})
unset(PATH_PREFIX)
