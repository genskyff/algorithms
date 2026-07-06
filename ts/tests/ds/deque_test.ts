import { assert, assertEquals, assertFalse } from "@std/assert";
import { createDeque } from "@/ds";

Deno.test("Deque - create empty", () => {
  const list = createDeque<number>();
  assertEquals(list.toArray(), []);
  assertEquals(list.len(), 0);
  assertEquals(list.cap(), 100);
  assert(list.isEmpty());
});

Deno.test("Deque - create with initial values", () => {
  const list = createDeque(1, 2, 3);
  assertEquals(list.toArray(), [1, 2, 3]);
  assertEquals(list.len(), 3);
  assertEquals(list.cap(), 100);
  assertFalse(list.isEmpty());
});

Deno.test("Deque - clear", () => {
  const list = createDeque(1, 2, 3);
  list.clear();
  assert(list.isEmpty());
  assertEquals(list.cap(), 100);
  assertEquals(list.toArray(), []);
});

Deno.test("Deque - cap should grow", () => {
  const list = createDeque(...Array(99).fill(0));
  assertEquals(list.cap(), 100);
  list.push(0, 0);
  assertEquals(list.cap(), 200);
  assertEquals(list.toArray(), Array(101).fill(0));
});

Deno.test("Deque - cap should shrink", () => {
  const list = createDeque(...Array(1001).fill(0));
  assertEquals(list.cap(), 1100);
  list.clear();
  assertEquals(list.cap(), 199);
  assertEquals(list.toArray(), []);
});

Deno.test("Deque - push and unshift", () => {
  const list = createDeque(1, 2, 3);
  list.push(4, 5, 6);
  list.unshift(-2, -1, 0);
  assertEquals(list.toArray(), [-2, -1, 0, 1, 2, 3, 4, 5, 6]);
  assertEquals(list.len(), 9);
});

Deno.test("Deque - pop and shift", () => {
  const list = createDeque(1, 2, 3);
  assertEquals(list.pop(), 3);
  assertEquals(list.shift(), 1);
  assertEquals(list.toArray(), [2]);
  assertEquals(list.len(), 1);
});

Deno.test("Deque - first and last", () => {
  const list = createDeque(1, 2, 3);
  assertEquals(list.first(), 1);
  assertEquals(list.last(), 3);
});
