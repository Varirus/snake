cmake_minimum_required (VERSION 3.1)

project (snake)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-Wall -Wextra -pedantic -Werror=return-type -Werror=parentheses -Werror=vla -Werror=array-bounds -Wcast-qual -Wmaybe-uninitialized )

# Windows specific config
IF (WIN32)
    # Include local sfml cmake config
    set(SFML_DIR "C:/lib/SFML-2.5.1/lib/cmake/SFML")
    # Link sfml statically (Optional)
    set(SFML_STATIC_LIBRARIES TRUE)
ENDIF()

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

# Create a list with all .cpp source files
set(project_sources
    main.cpp
    Controller.cpp
    GameManager.cpp
    View.cpp
    Scoreboard.cpp
)

# Create executable with all necessary source files
add_executable(${PROJECT_NAME}
    ${project_sources})

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)