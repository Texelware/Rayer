project "RayerEditor"

    kind "ConsoleApp"
    language "C++"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

   
    files{

        "src/**.h",
        "src/**.cpp"
        
    }

    includedirs {

        "src",
        "%{wks.location}/Rayer/src",
        "%{wks.location}/Rayer/vendor/GLFW/include",
        "%{wks.location}/Rayer/vendor/GLAD/include",
        "%{wks.location}/Rayer/vendor/ImGui/include",
        "%{wks.location}/Rayer/vendor/assimp/include",
        "%{wks.location}/Rayer/vendor/glm"
    }

    links{

        "Rayer"
    }

    filter "system:windows"

        cppdialect "C++20"
        staticruntime "off"
        systemversion "latest"
        

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

        defines {
            "RAYER_DEBUG" 
        } 

        
    