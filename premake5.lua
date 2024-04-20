workspace "Rayer"

    architecture "x64"
    configurations {

        "Debug",
        "Release",
        "Dist"
    }

    startproject "RayerEditor"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"

    include "Rayer/vendor/GLFW"
    include "Rayer/vendor/GLAD"
    include "Rayer/vendor/ImGui"
    include "Rayer/vendor/stb_image"

group ""

group "Core"

    include "Rayer"
    
group ""

group "Editor"

    include "RayerEditor"

group ""


group "Misc" 

    include "Sandbox"

group ""

