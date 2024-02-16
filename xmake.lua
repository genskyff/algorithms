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

add_rules("mode.debug", "mode.release", "mode.test")
rule("mode.test")
    on_load(function (target)
        target:set("group", "test")
        target:add("includedirs", "test")
    end)
rule_end()

task("test")
    on_run(function ()
        os.exec("xmake f -m test")
        os.exec("xmake build -g test")
        os.exec("xmake run -g test")
    end)
    set_menu{
        usage = "xmake test",
        description = "Run tests"
    }
task_end()

add_includedirs("include", "include/sort")

on_load(function (target)
    if target:name() ~= "utils" then
        target:add("deps", "utils")
    end

    if target:name() ~= "utils" and target:name() ~= "test" and target:name("test_.*") then
        target:add("deps", "test")
    end
end)

target("test")
    set_kind("static")
    add_files("test/test.c")

-- -------
--  utils
-- -------

target("utils")
    set_kind("static")
    add_files("src/utils.c")

target("test_utils")
    set_kind("binary")
    set_group("test")
    add_files("test/test_utils.c")

-- --------------------
--  sorting algorithms
-- --------------------

target("bubble")
    set_kind("static")
    add_files("src/sort/bubble.c")

target("test_bubble")
    set_kind("binary")
    set_group("test")
    add_files("test/sort/test_bubble.c")
    add_deps("bubble")

target("insertion")
    set_kind("static")
    add_files("src/sort/insertion.c")

target("test_insertion")
    set_kind("binary")
    set_group("test")
    add_files("test/sort/test_insertion.c")
    add_deps("insertion")

target("merge")
    set_kind("static")
    add_files("src/sort/merge.c")

target("test_merge")
    set_kind("binary")
    set_group("test")
    add_files("test/sort/test_merge.c")
    add_deps("merge")

target("quick")
    set_kind("static")
    add_files("src/sort/quick.c")

target("test_quick")
    set_kind("binary")
    set_group("test")
    add_files("test/sort/test_quick.c")
    add_deps("quick")

target("selection")
    set_kind("static")
    add_files("src/sort/selection.c")

target("test_selection")
    set_kind("binary")
    set_group("test")
    add_files("test/sort/test_selection.c")
    add_deps("selection")
