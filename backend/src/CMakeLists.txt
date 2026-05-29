add_library(backend
    grid.cpp
    cell.cpp
    rule_book.cpp
)

target_include_directories(backend PUBLIC ${backend_include_dir})