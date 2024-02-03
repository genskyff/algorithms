set_project("algorithms-c")
set_version("0.1.0")
set_languages("c17")

if is_plat("windows") then
    add_toolchains("mingw")
elseif is_plat("linux") then
    add_toolchains("gcc")
elseif is_plat("macosx") then
    add_toolchains("clang")
end

add_rules("mode.debug", "mode.release")
add_includedirs("include", "include/sort")

target("utils")
    set_kind("static")
    add_files("src/utils.c")

target("test_utils")
    set_kind("binary")
    add_files("test/utils.c")

target("bubble")
    set_kind("static")
    add_files("src/sort/bubble.c")
    add_deps("utils")

target("test_bubble")
    set_kind("binary")
    add_files("test/sort/bubble.c")
    add_deps("bubble", "utils")
