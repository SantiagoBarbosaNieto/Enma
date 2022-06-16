workspace "Enma"
    architecture "x64"
    startproject "Sandbox"
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
    IncludeDir["Glad"] = "Enma/vendor/Glad/include"
    IncludeDir["ImGui"] = "Enma/vendor/imgui/"
    IncludeDir["glm"] = "Enma/vendor/glm/"

group "Dependencies"
    include "Enma/vendor/GLFW"
    include "Enma/vendor/Glad"
    include "Enma/vendor/imgui"

group ""

project "Enma"
    location "Enma"
    kind "Staticlib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "empch.h"
    pchsource "Enma/src/empch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/*.hpp",
        "%{prj.name}/vendor/glm/glm/*.inl"
    }

    includedirs
    {
        "%{wks.location}/%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "GLFW",
        "Glad",
        "opengl32.lib",
        "ImGui"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "EM_PLATFORM_WINDOWS",
            "EM_BUILD_DLL",
            "GLFW_INCLUDE_NONE",
            "_CRT_SECURE_NO_WARNINGS"
        }


    filter "configurations:Debug"
        defines { "EM_DEBUG", "EM_ENABLE_ASSERTS"}
        symbols "on"

    filter "configurations:Release"
        defines "EM_RELEASE"
        symbols "on"
        
    filter "configurations:Dist"
        defines "EM_DIST"
        symbols "on"

project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"
        
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
        "Enma/src",
        "Enma/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Enma"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "EM_PLATFORM_WINDOWS"
        }


    filter "configurations:Debug"
        defines "EM_DEBUG"
        symbols "on"

    filter "configurations:Release"
        defines "EM_RELEASE"
        symbols "on"
        
    filter "configurations:Dist"
        defines "EM_DIST"
        symbols "on"


