set_project("algorithms-c")
set_version("0.1.0")
set_languages("c23")
set_warnings("all", "extra")

set_allowedplats("windows", "linux", "macosx")

add_rules("mode.debug", "mode.release", "mode.test")
rule("mode.test")
on_load(
    function(target)
        local group = target:get("group")
        if group and string.find(group, "^test") == 1 then
            target:add("includedirs", "tests")
            target:add("deps", "helper")
        end
    end
)
rule_end()

add_includedirs("include", {public = true})
add_includedirs("src")

on_load(
    function(target)
        if target:name() ~= "utils" and target:name() ~= "alg" then
            target:add("deps", "utils")
        end
    end
)

-- -------
--  tasks
-- -------

task("lint")
on_run(
    function()
        local projectdir = os.projectdir()
        local files =
            os.iorunv(
            "fd",
            {
                "-tf",
                ".c|.h"
            },
            {curdir = projectdir}
        )
        io.writefile(path.join(projectdir, ".clang-format-files"), files)
        os.execv(
            "mise",
            {
                "x",
                "--",
                "clang-format",
                "--dry-run",
                "-Werror",
                "-style=file",
                "--files=.clang-format-files"
            },
            {curdir = projectdir}
        )
    end
)
set_menu {
    usage = "xmake lint",
    description = "Run clang-format to check code format"
}
task_end()

task("lint:fix")
on_run(
    function()
        local projectdir = os.projectdir()
        local files =
            os.iorunv(
            "fd",
            {
                "-tf",
                ".c|.h"
            },
            {curdir = projectdir}
        )
        io.writefile(path.join(projectdir, ".clang-format-files"), files)
        os.execv(
            "mise",
            {
                "x",
                "--",
                "clang-format",
                "-i",
                "-style=file",
                "--files=.clang-format-files"
            },
            {curdir = projectdir}
        )
    end
)
set_menu {
    usage = "xmake lint:fix",
    description = "Run clang-format to fix code format"
}
task_end()

-- ------------
--  test tasks
-- ------------

function add_test_task(name, group, desc)
    task("test:" .. name)
    on_run(
        function()
            import("core.project.project")

            os.exec("xmake f -m test")
            os.exec("xmake build -g " .. group)

            local targets = {}
            for target_name, target in pairs(project.targets()) do
                local target_group = target:get("group")
                local matches =
                    target_group == group or
                    (group == "test*" and
                        string.find(target_group or "", "^test") == 1)
                if matches then
                    table.insert(targets, target_name)
                end
            end
            table.sort(targets)

            local failed = 0
            for _, target_name in ipairs(targets) do
                try {
                    function()
                        os.execv("xmake", {"run", target_name})
                    end,
                    catch {
                        function()
                            failed = failed + 1
                        end
                    }
                }
            end

            if failed > 0 then
                raise("%d test targets failed", failed)
            end
        end
    )
    set_menu {
        usage = "xmake test:" .. name,
        description = "Run " .. desc .. " tests"
    }
    task_end()
end

add_test_task("all", "test*", "all")
add_test_task("alg", "test_alg", "alg integration")
add_test_task("helper", "test_helper", "helper")
add_test_task("utils", "test_utils", "utils")
add_test_task("ds", "test_ds", "data structure")
add_test_task("sort", "test_sort", "sorting algorithm")
add_test_task("string", "test_string", "string algorithm")

-- ---------------
--  module helper
-- ---------------

function add_module(name, group, dir)
    target(name)
    set_kind("static")
    set_group(group)
    add_files("src/" .. dir .. "/" .. name .. ".c")
    target_end()

    target("test_" .. name)
    set_kind("binary")
    set_group("test_" .. group)
    add_files("tests/" .. dir .. "/test_" .. name .. ".c")
    add_deps(name)
    target_end()
end

-- -------------
--  test helper
-- -------------

target("helper")
set_kind("static")
add_files("tests/support/helper.c")
add_includedirs("tests")
target_end()

target("test_helper")
set_kind("binary")
set_group("test_helper")
add_files("tests/test_helper.c")
target_end()

-- ---------
--  library
-- ---------

target("alg")
set_kind("static")
set_group("lib")
add_files("src/*.c", "src/*/*.c")
target_end()

target("test_alg")
set_kind("binary")
set_group("test_alg")
add_files("tests/integration/test_alg.c")
add_deps("alg")
target_end()

-- -------
--  utils
-- -------

target("utils")
set_kind("static")
add_files("src/utils.c")
target_end()

target("test_utils")
set_kind("binary")
set_group("test_utils")
add_files("tests/test_utils.c")
add_deps("utils")
target_end()

-- -----------------
--  data structures
-- -----------------

for _, name in ipairs(
    {
        "array_queue",
        "array_stack",
        "binary_tree",
        "hashmap",
        "linked_list",
        "linked_queue",
        "linked_stack",
        "sqlist",
        "static_linked_list",
        "vector"
    }
) do
    add_module(name, "ds", "ds")
end

-- --------------------
--  sorting algorithms
-- --------------------

for _, name in ipairs(
    {
        "bubble",
        "insertion",
        "merge",
        "quick",
        "selection"
    }
) do
    add_module(name, "sort", "sort")
end

-- --------------------
--  string algorithms
-- --------------------

for _, name in ipairs(
    {
        "brute_force"
    }
) do
    add_module(name, "string", "string")
end
