qt6_wrap_cpp(MOC_FILES 
    ../include/communicator.hpp
)

add_library(communicator
    communicator.cpp
    ${MOC_FILES}
)   

target_include_directories(communicator PUBLIC ${communicator_include_dir})
target_link_libraries(communicator PRIVATE Qt6::Widgets backend frontend)