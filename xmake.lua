set_project("algorithms-c")
set_version("0.1.0")
set_languages("c17")

set_allowedplats("windows", "linux", "macosx")
if is_plat("windows") then
    set_toolchains("msvc")
elseif is_plat("linux") then
    set_toolchains("gcc")
elseif is_plat("macosx") then
    set_toolchains("clang")
end

add_rules("mode.debug", "mode.release", "mode.test")
rule("mode.test")
    on_load(function (target)
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

add_includedirs("include", "include/ds", "include/sort")

on_load(function (target)
    if target:name() ~= "utils" then
        target:add("deps", "utils")
    end

    if target:get("group") == "test" then
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
    add_deps("utils")

-- -----------------
--  data structures
-- -----------------

target("linked_list")
    set_kind("static")
    set_group("ds")
    add_files("src/ds/linked_list.c")

target("test_linked_list")
    set_kind("binary")
    set_group("test")
    add_files("test/ds/test_linked_list.c")
    add_deps("linked_list")

target("sqlist")
    set_kind("static")
    set_group("ds")
    add_files("src/ds/sqlist.c")

target("test_sqlist")
    set_kind("binary")
    set_group("test")
    add_files("test/ds/test_sqlist.c")
    add_deps("sqlist")

target("vec")
    set_kind("static")
    set_group("ds")
    add_files("src/ds/vec.c")

target("test_vec")
    set_kind("binary")
    set_group("test")
    add_files("test/ds/test_vec.c")
    add_deps("vec")

-- --------------------
--  sorting algorithms
-- --------------------

target("bubble")
    set_kind("static")
    set_group("sort")
    add_files("src/sort/bubble.c")

target("test_bubble")
    set_kind("binary")
    set_group("test")
    add_files("test/sort/test_bubble.c")
    add_deps("bubble")

target("insertion")
    set_kind("static")
    set_group("sort")
    add_files("src/sort/insertion.c")

target("test_insertion")
    set_kind("binary")
    set_group("test")
    add_files("test/sort/test_insertion.c")
    add_deps("insertion")

target("merge")
    set_kind("static")
    set_group("sort")
    add_files("src/sort/merge.c")

target("test_merge")
    set_kind("binary")
    set_group("test")
    add_files("test/sort/test_merge.c")
    add_deps("merge")

target("quick")
    set_kind("static")
    set_group("sort")
    add_files("src/sort/quick.c")

target("test_quick")
    set_kind("binary")
    set_group("test")
    add_files("test/sort/test_quick.c")
    add_deps("quick")

target("selection")
    set_kind("static")
    set_group("sort")
    add_files("src/sort/selection.c")

target("test_selection")
    set_kind("binary")
    set_group("test")
    add_files("test/sort/test_selection.c")
    add_deps("selection")
