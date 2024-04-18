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
        "%{wks.location}/Rayer/vendor/ImGui/include"
    }

    links{

        "Rayer"
    }

    filter "system:windows"

        cppdialect "C++20"
        staticruntime "off"
        systemversion "latest"

        
    