import { assert, assertEquals, assertFalse } from "@std/assert";
import { createVector } from "@/ds/vector.ts";

Deno.test("Vector - create empty", () => {
  const list = createVector<number>();
  assertEquals(list.toArray(), []);
  assertEquals(list.len(), 0);
  assertEquals(list.cap(), 100);
  assert(list.isEmpty());
});

Deno.test("Vector - create with initial values", () => {
  const list = createVector(1, 2, 3);
  assertEquals(list.toArray(), [1, 2, 3]);
  assertEquals(list.len(), 3);
  assertEquals(list.cap(), 100);
  assertFalse(list.isEmpty());
});

Deno.test("Vector - clear", () => {
  const list = createVector(1, 2, 3);
  list.clear();
  assert(list.isEmpty());
  assertEquals(list.cap(), 100);
  assertEquals(list.toArray(), []);
});

Deno.test("Vector - cap should grow", () => {
  const list = createVector(...Array(99).fill(0));
  assertEquals(list.cap(), 100);
  list.push(0, 0);
  assertEquals(list.cap(), 200);
});

Deno.test("Vector - cap should shrink", () => {
  const list = createVector(...Array(1001).fill(0));
  assertEquals(list.cap(), 1100);
  list.clear();
  assertEquals(list.cap(), 199);
});

Deno.test("Vector - get and set", () => {
  const list = createVector(1, 2, 3);
  assertEquals(list.get(0), 1);
  assertEquals(list.get(1), 2);
  assertEquals(list.get(2), 3);

  list.set(0, 10);
  list.set(1, 20);
  list.set(2, 30);
  assertEquals(list.toArray(), [10, 20, 30]);
});

Deno.test("Vector - insert and remove", () => {
  const list = createVector();
  list.insert(0, 3);
  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(list.len(), 4);
  list.insert(list.len(), 5);
  assertEquals(list.toArray(), [1, 2, 3, 4, 5]);

  assertEquals(list.remove(0), 1);
  assertEquals(list.remove(1), 3);
  assertEquals(list.remove(list.len() - 1), 5);
  assertEquals(list.toArray(), [2, 4]);
});

Deno.test("Vector - push and unshift", () => {
  const list = createVector(1, 2, 3);
  list.push(4, 5, 6);
  list.unshift(-2, -1, 0);
  assertEquals(list.toArray(), [-2, -1, 0, 1, 2, 3, 4, 5, 6]);
  assertEquals(list.len(), 9);
});

Deno.test("Vector - pop and shift", () => {
  const list = createVector(1, 2, 3);
  assertEquals(list.pop(), 3);
  assertEquals(list.shift(), 1);
  assertEquals(list.toArray(), [2]);
  assertEquals(list.len(), 1);
});

Deno.test("Vector - first and last", () => {
  const list = createVector(1, 2, 3);
  assertEquals(list.first(), 1);
  assertEquals(list.last(), 3);
});

Deno.test("Vector - indexOf", () => {
  const list = createVector(1, 2, 3);
  assertEquals(list.indexOf(1), 0);
  assertEquals(list.indexOf(2), 1);
  assertEquals(list.indexOf(3), 2);
  assertEquals(list.indexOf(4), undefined);
});

Deno.test("Vector - swap and reverse", () => {
  const list = createVector(1, 2, 3, 4, 5);
  list.swap(1, 3);
  assertEquals(list.toArray(), [1, 4, 3, 2, 5]);
  list.reverse();
  assertEquals(list.toArray(), [5, 2, 3, 4, 1]);
});

Deno.test("Vector - map, filter and reduce", () => {
  const list = createVector(1, 2, 3, 4, 5);
  const mapped = list.map((val) => val * 2);
  assertEquals(mapped.toArray(), [2, 4, 6, 8, 10]);

  const filtered = list.filter((val) => val % 2 === 0);
  assertEquals(filtered.toArray(), [2, 4]);

  const reduced = list.reduce((acc, val) => acc + val, 0);
  assertEquals(reduced, 15);
});
