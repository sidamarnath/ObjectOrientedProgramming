
project(SpartyLib)

set(SOURCE_FILES MainFrame.cpp MainFrame.h pch.h Villain.cpp Villain.h Door.cpp Door.h TuitionUp.cpp TuitionUp.h Item.cpp Item.h Money.cpp Money.h GameView.cpp GameView.h Platform.cpp Platform.h SpartyGnome.cpp SpartyGnome.h Game.h Game.cpp Covid.cpp Covid.h Vector.cpp Vector.h Wall.cpp Wall.h)


set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

file(COPY ../images/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images/)
file(COPY ../levels/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/levels/)