workspace "Enma"
    architecture "x64"
    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


    --Include directories relative to root folder (solution directory)
    IncludeDir = {}
    IncludeDir["GLFW"] = "Enma/vendor/GLFW/include"

include "Enma/vendor/GLFW"

project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
        language "C++"
        
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Enma/vendor/spdlog/include",
        "Enma/src"
    }

    links
    {
        "Enma"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "EM_PLATFORM_WINDOWS"
        }
        postbuildcommands
        {
            ("{COPY} ../bin/" .. outputdir .. "/Enma/Enma.dll" .. " ../bin/" .. outputdir .. "/%{prj.name}")
        }


    filter "configurations:Debug"
        defines "EM_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "EM_RELEASE"
        symbols "On"
        
    filter "configurations:Dist"
        defines "EM_DIST"
        symbols "On"

project "Enma"
    location "Enma"
    kind "SharedLib"
    language "C++"


    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "empch.h"
    pchsource "Enma/src/empch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{wks.location}/%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}"
    }

    links
    {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "EM_PLATFORM_WINDOWS",
            "EM_BUILD_DLL"
        }

    filter "configurations:Debug"
        defines { "EM_DEBUG", "EM_ENABLE_ASSERTS"}
        symbols "On"

    filter "configurations:Release"
        defines "EM_RELEASE"
        symbols "On"
        
    filter "configurations:Dist"
        defines "EM_DIST"
        symbols "On"