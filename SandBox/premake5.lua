project "SandBox"

    kind "ConsoleApp"
    language "C++"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

   


    files{

        
        "src/**.cpp"
        
    }

    includedirs {

        "%{wks.location}/Rayer/src",
        "%{wks.location}/Rayer/vendor/GLFW/include",
        "%{wks.location}/Rayer/vendor/GLAD/include",
    }

    links{

        "Rayer"
    }

    filter "system:windows"

        cppdialect "C++20"
        staticruntime "off"
        systemversion "latest"

        
    