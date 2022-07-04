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
	IncludeDir["stb_image"] = "Enma/vendor/stb/stb_image"

--_---------------------------------------------- ENMA --------------------------------
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
        "%{prj.name}/vendor/stb/stb_image/*.h",
        "%{prj.name}/vendor/stb/stb_image/*.cpp",
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
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
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
            "GLFW_INCLUDE_NONE",
            "_CRT_SECURE_NO_WARNINGS"
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

        
--_---------------------------------------------- SANBOX --------------------------------
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


    filter "configurations:Debug"
        defines "EM_DEBUG"
        symbols "on"

    filter "configurations:Release"
        defines "EM_RELEASE"
        symbols "on"
        
    filter "configurations:Dist"
        defines "EM_DIST"
        symbols "on"

group "Dependencies"
--_---------------------------------------------- DEPENDENCIES - GLFW --------------------------------
project "GLFW"
    GLFWlocation = "%{wks.location}/Enma/vendor/GLFW"
    location (GLFWlocation)
	kind "StaticLib"
	staticruntime "on"
	language "C"
	warnings "Off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{GLFWlocation}/include/GLFW/glfw3.h",
		"%{GLFWlocation}/include/GLFW/glfw3native.h",
		"%{GLFWlocation}/src/glfw_config.h",
		"%{GLFWlocation}/src/context.c",
		"%{GLFWlocation}/src/init.c",
		"%{GLFWlocation}/src/input.c",
		"%{GLFWlocation}/src/monitor.c",

		"%{GLFWlocation}/src/null_init.c",
		"%{GLFWlocation}/src/null_joystick.c",
		"%{GLFWlocation}/src/null_monitor.c",
		"%{GLFWlocation}/src/null_window.c",

		"%{GLFWlocation}/src/platform.c",
		"%{GLFWlocation}/src/vulkan.c",
		"%{GLFWlocation}/src/window.c",
	}
	filter "system:linux"
		pic "On"

		systemversion "latest"
		
		files
		{
			"%{GLFWlocation}/src/x11_init.c",
			"%{GLFWlocation}/src/x11_monitor.c",
			"%{GLFWlocation}/src/x11_window.c",
			"%{GLFWlocation}/src/xkb_unicode.c",
			"%{GLFWlocation}/src/posix_time.c",
			"%{GLFWlocation}/src/posix_thread.c",
			"%{GLFWlocation}/src/glx_context.c",
			"%{GLFWlocation}/src/egl_context.c",
			"%{GLFWlocation}/src/osmesa_context.c",
			"%{GLFWlocation}/src/linux_joystick.c"
		}

		defines
		{
			"_GLFW_X11",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "system:windows"
		systemversion "latest"

		files
		{
			"%{GLFWlocation}/src/win32_init.c",
			"%{GLFWlocation}/src/win32_joystick.c",
			"%{GLFWlocation}/src/win32_module.c",
			"%{GLFWlocation}/src/win32_monitor.c",
			"%{GLFWlocation}/src/win32_time.c",
			"%{GLFWlocation}/src/win32_thread.c",
			"%{GLFWlocation}/src/win32_window.c",
			"%{GLFWlocation}/src/wgl_context.c",
			"%{GLFWlocation}/src/egl_context.c",
			"%{GLFWlocation}/src/osmesa_context.c"
		}

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

		links
		{
			"Dwmapi.lib"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		runtime "Release"
		optimize "on"
        symbols "off"

        
--_---------------------------------------------- DEPENDENCIES - ImGui --------------------------------
project "ImGui"
ImGuilocation = "%{wks.location}/Enma/vendor/ImGui"
location (ImGuilocation)
	kind "StaticLib"
    staticruntime "on"
	language "C++"
    cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{ImGuilocation}/imconfig.h",
		"%{ImGuilocation}/imgui.h",
		"%{ImGuilocation}/imgui.cpp",
		"%{ImGuilocation}/imgui_draw.cpp",
		"%{ImGuilocation}/imgui_internal.h",
		"%{ImGuilocation}/imgui_tables.cpp",
		"%{ImGuilocation}/imgui_widgets.cpp",
		"%{ImGuilocation}/imstb_rectpack.h",
		"%{ImGuilocation}/imstb_textedit.h",
		"%{ImGuilocation}/imstb_truetype.h",
		"%{ImGuilocation}/imgui_demo.cpp"
	}
    defines 
    { 
        "_CRT_SECURE_NO_WARNINGS"
    }

	filter "system:windows"
		systemversion "latest"

	filter "system:linux"
		pic "On"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

    filter "configurations:Dist"
		runtime "Release"
		optimize "on"
        symbols "off"

--_---------------------------------------------- DEPENDENCIES - Glad --------------------------------
project "Glad"
Gladlocation = "%{wks.location}/Enma/vendor/Glad"
location (Gladlocation)
	kind "StaticLib"
	language "C"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{Gladlocation}/include/glad/glad.h",
		"%{Gladlocation}/include/KHR/khrplatform.h",
		"%{Gladlocation}/src/glad.c"
	}

	includedirs
	{
		"%{Gladlocation}/include"
	}

	filter "system:linux"
		pic "On"

		systemversion "latest"

	filter "system:windows"
		systemversion "latest"

		defines 
		{ 
			"_CRT_SECURE_NO_WARNINGS"
		}


	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		runtime "Release"
		optimize "on"
		symbols "off"

group ""