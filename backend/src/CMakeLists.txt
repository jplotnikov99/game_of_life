qt6_wrap_cpp(MOC_FILES ../include/state_updater.hpp)

add_library(backend
    grid.cpp
    cell.cpp
    state_updater.cpp
    ${MOC_FILES}
)

target_include_directories(backend PUBLIC ${backend_include_dir})
target_link_libraries(backend PRIVATE Qt6::Widgets)