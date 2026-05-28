add_library(backend
    grid.cpp
    cell.cpp
    state_updater.cpp
)

target_include_directories(backend PUBLIC ${backend_include_dir})