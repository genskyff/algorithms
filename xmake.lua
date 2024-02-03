set_project("algorithms-c")
set_version("0.1.0")
set_languages("c17")
set_allowedplats("windows", "linux", "macosx")

if is_plat("windows") then
    add_toolchains("mingw")
elseif is_plat("linux") then
    add_toolchains("gcc")
elseif is_plat("macosx") then
    add_toolchains("clang")
end

option("test", { default = false, showmenu = true, description = "Enable test" })

if has_config("test") then
    add_requires("gtest")
end

rule("mode.test")
    on_load(function (target)
        if not has_config("test") then
            target:set("enabled", false)
            return
        end
        target:set("rundir", os.projectdir())
        target:set("group", "test")
        target:add("packages", "gtest")
    end)
rule_end()

task("test")
    on_run(function ()
        os.exec("xmake f -m debug --test=y")
        os.exec("xmake build -g test")
        os.exec("xmake run -g test")
    end)

    set_menu{}
task_end()

add_rules("mode.debug", "mode.release", "mode.test")
add_includedirs("include", "include/sort")

on_load(function (target)
    if target:name() ~= "utils" then
        target:add("deps", "utils")
    end
end)

target("utils")
    set_kind("static")
    add_files("src/utils.c")

target("test_utils")
    set_kind("binary")
    set_group("test")
    add_files("test/utils.c")

target("bubble")
    set_kind("static")
    add_files("src/sort/bubble.c")

target("test_bubble")
    set_kind("binary")
    set_group("test")
    add_files("test/sort/bubble.c")
    add_deps("bubble")
