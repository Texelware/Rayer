project "Rayer"
    kind "StaticLib"
    language "C++"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

   

    files{

        "src/**.h",
        "src/**.cpp",

    }

    includedirs {
        "src",
        "vendor/GLFW/include",
        "vendor/GLAD/include",
        "vendor/ImGui/include",
        "vendor/stb_image/include",
        "vendor/glm"

    }

    defines {
        "_CRT_SECURE_NO_WARNINGS",
        "GLFW_INCLUDE_NONE"
    }

    links{

        "GLFW",
        "GLAD",
        "ImGui",
        "stb_image",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "off"
        systemversion "latest"

        defines { 
            
            "RAYER_PLATFORM_WINDOWS",
    
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
        
        defines {
            "RAYER_DEBUG" 
        } 

   


    