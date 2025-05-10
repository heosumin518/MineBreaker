workspace "MineBreaker"
    architecture "x64"
    startproject "GameApp"

    configurations { "Debug", "Release" }
    flags { "MultiProcessorCompile" }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- GLFW 프로젝트
group "Dependencies"
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
            "Dependencies/glfw/include"
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
group ""

-- Engine 프로젝트
project "Engine"
    location "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

    files {
        "Engine/**.h",
        "Engine/**.cpp"
    }

    includedirs {
        "Engine",
        "Dependencies/glfw/include"
    }

-- GameApp 프로젝트
project "GameApp"
    location "GameApp"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("Binaries/" .. outputdir .. "/%{prj.name}")
    objdir ("Intermediate/" .. outputdir .. "/%{prj.name}")

    files {
        "GameApp/**.h",
        "GameApp/**.cpp"
    }

    includedirs {
        "GameApp",
        "Engine",
        "Dependencies/glfw/include"
    }

    links {
        "Engine",
        "glfw",
        "opengl32"
    }
