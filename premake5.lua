workspace "MineBreaker"
    architecture "x64"
    startproject "GameApp"

    configurations { "Debug", "Release" }
    flags { "MultiProcessorCompile" }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
-- GLFW 프로젝트
    project "glfw"
        location "Dependencies/glfw"
        kind "StaticLib"
        language "C"
        staticruntime "off"

        targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
        objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

        files {
            "Dependencies/glfw/include/GLFW/**.h",
            "Dependencies/glfw/src/**.h",
            "Dependencies/glfw/src/**.c"
        }

        includedirs {
            "Dependencies/glfw/include",
        }

        filter "system:windows"
            defines { "_GLFW_WIN32" }
            removefiles {
                "Dependencies/glfw/src/glx_*",
                "Dependencies/glfw/src/x11_*",
                "Dependencies/glfw/src/linux_*",
                "Dependencies/glfw/src/posix_*",
                "Dependencies/glfw/src/cocoa_*"
            }

        filter "system:macosx"
        defines { "_GLFW_COCOA" }
        removefiles {
            "Dependencies/glfw/src/win32_*",
            "Dependencies/glfw/src/x11_*",
            "Dependencies/glfw/src/glx_*",
            "Dependencies/glfw/src/linux_*",
            "Dependencies/glfw/src/posix_*",
            "Dependencies/glfw/src/wgl_*"
        }

        filter "system:linux"
        defines { "_GLFW_X11" }
        removefiles {
            "Dependencies/glfw/src/win32_*",
            "Dependencies/glfw/src/cocoa_*",
            "Dependencies/glfw/src/posix_time.h",
            "Dependencies/glfw/src/wgl_*"
        }

        filter "configurations:Debug"
            runtime "Debug"
            symbols "on"

        filter "configurations:Release"
            runtime "Release"
            optimize "on"

-- spdlog
    project "spdlog"
    location "Dependencies/spdlog"
    kind "None" -- headers only so no need to build
    language "C++"

    includedirs { "Dependencies/spdlog/include" }

    files {
        "Dependencies/spdlog/include/**.h",
        "Dependencies/spdlog/include/**.hpp"
    }

-- GLAD
    project "glad"
        location "Dependencies/glad"
        kind "StaticLib"
        language "C"
        staticruntime "on" -- 헤더 전용은 아니지만 src/glad.c 링크됨

        targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
        objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

        files {
            "Dependencies/glad/include/glad/glad.h",
            "Dependencies/glad/include/KHR/khrplatform.h",
            "Dependencies/glad/src/glad.c"
        }

        includedirs {
            "Dependencies/glad/include"
        }

        filter "system:windows"
            systemversion "latest"

    filter "configurations:Debug"
        defines { "_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

-- GLM
    project "glm"
        location "Dependencies/glm"
        kind "None" -- 헤더 전용이라 컴파일할 소스 없음
        language "C++"

        includedirs {
            "Dependencies/glm"
        }

        files {
            "Dependencies/glm/glm/**.hpp",
            "Dependencies/glm/glm/**.inl"
        }

-- FreeType
    project "freetype"
        location "Dependencies/freetype"
        kind "StaticLib"
        language "C"
        staticruntime "off"

        targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
        objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

        -- FreeType 소스 파일 수동 추가
        files {
            "Dependencies/freetype/src/**.c",
            "Dependencies/freetype/include/**.h"
        }

        includedirs {
            "Dependencies/freetype/include",
            "Dependencies/freetype/src"
        }

        defines {
            "FT2_BUILD_LIBRARY"
        }

        filter "system:windows"
            systemversion "latest"

        filter "configurations:Debug"
            defines { "_DEBUG" }
            symbols "On"

        filter "configurations:Release"
            defines { "NDEBUG" }
            optimize "On"

group ""

-- Engine 프로젝트
project "Engine"
    location "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    buildoptions { "/utf-8" }

    targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

    files {
        "Engine/**.h",
        "Engine/**.cpp"
    }

    includedirs {
        "Engine",
        "Dependencies/glfw/include",
        "Dependencies/glad/include",
        "Dependencies/spdlog/include",
        "Dependencies/glm",
        "Dependencies/freetype/include",
        "Dependencies/freetype/src"
    }

    links {
        "glfw",
        "glad",
        "freetype",
        "opengl32.lib"
    }

    filter "configurations:Debug"
        defines { "_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"


-- GameApp 프로젝트
project "GameApp"
    location "GameApp"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    buildoptions { "/utf-8" }

    targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

    files {
        "GameApp/**.h",
        "GameApp/**.cpp"
    }

    includedirs {
        "GameApp",
        "Engine",
        "Dependencies/glfw/include",
        "Dependencies/spdlog/include",
        "Dependencies/glad/include",
        "Dependencies/glm",
        "Dependencies/freetype/include",
        "Dependencies/freetype/src"
    }

    links {
        "Engine"
    }

    filter "configurations:Debug"
    defines { "_DEBUG" }
    symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

