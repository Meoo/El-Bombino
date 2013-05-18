
-- Link automatique avec SFML2
function sfml_links(tab, dbg, static)
    local suffix = (static and "-s" or "") .. (dbg and "-d" or "")
    for _, v in pairs(tab) do
        links("sfml-" .. v .. suffix)
    end
end

-- Projet El-Bombino
solution "El-Bombino"
  configurations { "Debug", "Release" }
  targetdir "bin"
  objdir "bin/obj"
  includedirs { "include", "../SFML2/include" }
  libdirs "../SFML2/lib"

  -- Configurations Debug et Release
  configuration "Debug"
    defines { "DEBUG" }
    flags { "Symbols", "ExtraWarnings" }
    targetsuffix "-d"

  configuration "Release"
    defines { "NDEBUG" }
    flags { "OptimizeSpeed", "ExtraWarnings" }
    linkoptions "-static-libstdc++"

  configuration "gmake"
    linkoptions "-static-libgcc"

  configuration {}

  -- Le programme du jeu
  project "elbombino"
    language "C++"
    files { "src/**.cpp" }
    sfml_libs = { "graphics", "audio", "window", "system" }
    defines { "SFML_STATIC" }

    configuration "Debug"
      kind "ConsoleApp"
      sfml_links(sfml_libs, true, true)

    configuration "Release"
      kind "WindowedApp"
      sfml_links(sfml_libs, false, true)
