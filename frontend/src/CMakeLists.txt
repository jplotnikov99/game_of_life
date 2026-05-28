qt6_wrap_cpp(MOC_FILES 
    ../include/window.hpp
    ../include/grid_widget.hpp
)

add_library(frontend
    window.cpp
    grid_widget.cpp
    ${MOC_FILES}
)

target_include_directories(frontend PUBLIC ${frontend_include_dir} ${backend_include_dir})
target_link_libraries(frontend PRIVATE Qt6::Widgets backend)