set(PROJECT_NAME RayTracingTest)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "CMakeLists.txt"
)
source_group("" FILES ${no_group_source_files})

set(Header_Files
    "Camera.h"
    "CameraOrbitControl.h"
    "Mesh.h"
    "Model.h"
    "Scene.h"
    "ShaderManager.h"
    "Texture.h"
    "Utility.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Resource_Files
    "shader/fragment.fs"
    "shader/vertex.vs"
)
source_group("Resource Files" FILES ${Resource_Files})

set(Source_Files
    "../deps/glad_gl.c"
    "Camera.cpp"
    "CameraOrbitControl.cpp"
    "CameraOrbitControls.cpp"
    "DirectionalLight.cpp"
    "DirectionalLight.h"
    "Mesh.cpp"
    "Model.cpp"
    "RayTracingTest.cpp"
    "Scene.cpp"
    "ShaderManager.cpp"
    "stb_image.cpp"
    "Texture.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${no_group_source_files}
    ${Header_Files}
    ${Resource_Files}
    ${Source_Files}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DEBUG   "RayTracingTest"
    TARGET_NAME_RELEASE "RayTracingTest"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG   "E:/RayTracing/ray-tracing/x64/Debug/"
    OUTPUT_DIRECTORY_RELEASE "E:/RayTracing/ray-tracing/x64/Release/"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG   "E:/RayTracing/ray-tracing/x64/Debug"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "E:/RayTracing/ray-tracing/x64/Release"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_NAME_DEBUG   "RayTracingTest"
    ARCHIVE_OUTPUT_NAME_RELEASE "RayTracingTest"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
)
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
    $<$<CONFIG:Debug>:
        MultiThreadedDebugDLL
    >
    $<$<CONFIG:Release>:
        MultiThreadedDLL
    >
    $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Release>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
)
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "$<$<CONFIG:Release>:"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../vcpkg/installed/x86-windows/include"
    ">"
    "${CMAKE_CURRENT_SOURCE_DIR}/.;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../deps;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../deps/glm"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:"
        "_DEBUG;"
        "CMAKE_INTDIR=\"Debug\""
    ">"
    "$<$<CONFIG:Release>:"
        "NDEBUG;"
        "CMAKE_INTDIR=\"Release\""
    ">"
    "_CONSOLE;"
    "UNICODE;"
    "_UNICODE"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /Zi
        >
        $<$<CONFIG:Release>:
            /JMC;
            /Oi;
            /Gy;
            /ZI
        >
        /permissive-;
        /std:c++17;
        /sdl;
        /W3;
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /INCREMENTAL
        >
        $<$<CONFIG:Release>:
            /OPT:REF;
            /OPT:ICF
        >
        /MANIFEST;
        /DEBUG;
        /SUBSYSTEM:CONSOLE
    )
endif()

################################################################################
# Dependencies
################################################################################
# Link with other targets.
target_link_libraries(${PROJECT_NAME} PRIVATE
    ZERO_CHECK
)

set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "$<$<CONFIG:Debug>:"
        "glfw3;"
        "assimp-vc142-mtd"
    ">"
    "kernel32;"
    "user32;"
    "gdi32;"
    "winspool;"
    "shell32;"
    "ole32;"
    "oleaut32;"
    "uuid;"
    "comdlg32;"
    "advapi32"
)
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:"
        "${CMAKE_CURRENT_SOURCE_DIR}/../src/Debug/"
    ">"
)

