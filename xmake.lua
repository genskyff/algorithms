set_project("algorithms-c")
set_version("0.1.0")
set_languages("c17")

set_allowedplats("windows", "linux", "macosx")
if is_plat("windows") then
    set_toolchains("mingw")
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

task("test-all")
    on_run(function ()
        os.exec("xmake f -m test")
        os.exec("xmake build -g test*")
        os.exec("xmake run -g test*")
    end)
    set_menu{
        usage = "xmake test-all",
        description = "Run all tests"
    }
task_end()

task("test-ds")
    on_run(function ()
        os.exec("xmake f -m test")
        os.exec("xmake build -g test_ds")
        os.exec("xmake run -g test_ds")
    end)
    set_menu{
        usage = "xmake test-ds",
        description = "Run all data structures tests"
    }
task_end()

task("test-sort")
    on_run(function ()
        os.exec("xmake f -m test")
        os.exec("xmake build -g test_sort")
        os.exec("xmake run -g test_sort")
    end)
    set_menu{
        usage = "xmake test-sort",
        description = "Run all sorting algorithms tests"
    }
task_end()

task("test-utils")
    on_run(function ()
        os.exec("xmake f -m test")
        os.exec("xmake build -g test_utils")
        os.exec("xmake run -g test_utils")
    end)
    set_menu{
        usage = "xmake test-utils",
        description = "Run all utils tests"
    }
task_end()

add_includedirs("include", "include/ds", "include/sort")

on_load(function (target)
    if target:name() ~= "utils" then
        target:add("deps", "utils")
    end

    local group = target:get("group")
    if group and string.find(group, "^test") == 1 then
        target:add("deps", "test_helper")
    end
end)

-- -------------
--  test helper
-- -------------

target("test_helper")
    set_kind("static")
    add_files("test/test_helper.c")

-- -------
--  utils
-- -------

target("utils")
    set_kind("static")
    add_files("src/utils.c")

target("test_utils")
    set_kind("binary")
    set_group("test_utils")
    add_files("test/test_utils.c")
    add_deps("utils")

-- -----------------
--  data structures
-- -----------------

-- target("array_list")
--     set_kind("static")
--     set_group("ds")
--     add_files("src/ds/array_list.c")

-- target("test_array_list")
--     set_kind("binary")
--     set_group("test_ds")
--     add_files("test/ds/test_array_list.c")
--     add_deps("array_list")

target("array_queue")
    set_kind("static")
    set_group("ds")
    add_files("src/ds/array_queue.c")

target("test_array_queue")
    set_kind("binary")
    set_group("test_ds")
    add_files("test/ds/test_array_queue.c")
    add_deps("array_queue")

target("array_stack")
    set_kind("static")
    set_group("ds")
    add_files("src/ds/array_stack.c")

target("test_array_stack")
    set_kind("binary")
    set_group("test_ds")
    add_files("test/ds/test_array_stack.c")
    add_deps("array_stack")

target("linked_list")
    set_kind("static")
    set_group("ds")
    add_files("src/ds/linked_list.c")

target("test_linked_list")
    set_kind("binary")
    set_group("test_ds")
    add_files("test/ds/test_linked_list.c")
    add_deps("linked_list")

target("linked_queue")
    set_kind("static")
    set_group("ds")
    add_files("src/ds/linked_queue.c")

target("test_linked_queue")
    set_kind("binary")
    set_group("test_ds")
    add_files("test/ds/test_linked_queue.c")
    add_deps("linked_queue")

target("linked_stack")
    set_kind("static")
    set_group("ds")
    add_files("src/ds/linked_stack.c")

target("test_linked_stack")
    set_kind("binary")
    set_group("test_ds")
    add_files("test/ds/test_linked_stack.c")
    add_deps("linked_stack")

target("vector")
    set_kind("static")
    set_group("ds")
    add_files("src/ds/vector.c")

target("test_vector")
    set_kind("binary")
    set_group("test_ds")
    add_files("test/ds/test_vector.c")
    add_deps("vector")

-- --------------------
--  sorting algorithms
-- --------------------

target("bubble")
    set_kind("static")
    set_group("sort")
    add_files("src/sort/bubble.c")

target("test_bubble")
    set_kind("binary")
    set_group("test_sort")
    add_files("test/sort/test_bubble.c")
    add_deps("bubble")

target("insertion")
    set_kind("static")
    set_group("sort")
    add_files("src/sort/insertion.c")

target("test_insertion")
    set_kind("binary")
    set_group("test_sort")
    add_files("test/sort/test_insertion.c")
    add_deps("insertion")

target("merge")
    set_kind("static")
    set_group("sort")
    add_files("src/sort/merge.c")

target("test_merge")
    set_kind("binary")
    set_group("test_sort")
    add_files("test/sort/test_merge.c")
    add_deps("merge")

target("quick")
    set_kind("static")
    set_group("sort")
    add_files("src/sort/quick.c")

target("test_quick")
    set_kind("binary")
    set_group("test_sort")
    add_files("test/sort/test_quick.c")
    add_deps("quick")

target("selection")
    set_kind("static")
    set_group("sort")
    add_files("src/sort/selection.c")

target("test_selection")
    set_kind("binary")
    set_group("test_sort")
    add_files("test/sort/test_selection.c")
    add_deps("selection")
