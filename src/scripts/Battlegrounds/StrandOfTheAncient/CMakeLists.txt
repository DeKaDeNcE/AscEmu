# Copyright (c) 2014-2021 AscEmu Team <http://www.ascemu.org>

set(PATH_PREFIX StrandOfTheAncient)

set(SRC_StrandOfTheAncient
    ${PATH_PREFIX}/StrandOfTheAncient.cpp
    ${PATH_PREFIX}/StrandOfTheAncient.h
    ${PATH_PREFIX}/StrandOfTheAncientDefinitions.h
)

source_group(StrandOfTheAncient FILES ${SRC_StrandOfTheAncient})
unset(PATH_PREFIX)
