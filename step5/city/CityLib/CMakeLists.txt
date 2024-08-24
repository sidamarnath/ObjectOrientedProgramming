project(CityLib)

set(SOURCE_FILES
        pch.h
        City.h City.cpp
        Tile.h Tile.cpp
        CityReport.h CityReport.cpp
        MemberReport.h MemberReport.cpp
        TileBuilding.h TileBuilding.cpp
        TileGarden.h TileGarden.cpp
        TileLandscape.h TileLandscape.cpp
        MainFrame.cpp MainFrame.h
        CityReport.cpp CityView.cpp CityView.h ids.h GrayCode.cpp GrayCode.h TileHive.cpp TileHive.h Population.cpp Population.h PopulationSegment.cpp PopulationSegment.h TileWater.cpp TileWater.h TileVisitor.cpp TileVisitor.h BuildingCounter.cpp BuildingCounter.h HiveVisitor.cpp HiveVisitor.h ResetTileVisitor.cpp ResetTileVisitor.h)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)