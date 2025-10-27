import { assert, assertEquals, assertFalse } from "@std/assert";
import { createLinkedList } from "@/ds/linked_list.ts";

Deno.test("LinkedList - create empty", () => {
  const list = createLinkedList<number>();
  assertEquals(list.toArray(), []);
  assertEquals(list.len(), 0);
  assert(list.isEmpty());
});

Deno.test("LinkedList - create with initial values", () => {
  const list = createLinkedList(1, 2, 3);
  assertEquals(list.toArray(), [1, 2, 3]);
  assertEquals(list.len(), 3);
  assertFalse(list.isEmpty());
});

Deno.test("LinkedList - clear", () => {
  const list = createLinkedList(1, 2, 3);
  list.clear();
  assertEquals(list.toArray(), []);
  assertEquals(list.len(), 0);
  assert(list.isEmpty());
});

Deno.test("LinkedList - get and set", () => {
  const list = createLinkedList(1, 2, 3);
  assertEquals(list.get(0), 1);
  assertEquals(list.get(1), 2);
  assertEquals(list.get(2), 3);

  list.set(0, 10);
  list.set(1, 20);
  list.set(2, 30);
  assertEquals(list.toArray(), [10, 20, 30]);
});

Deno.test("LinkedList - insert and remove", () => {
  const list = createLinkedList();
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

Deno.test("LinkedList - push and unshift", () => {
  const list = createLinkedList(1, 2, 3);
  list.push(4);
  list.unshift(0);
  assertEquals(list.toArray(), [0, 1, 2, 3, 4]);
  assertEquals(list.len(), 5);
});

Deno.test("LinkedList - pop and shift", () => {
  const list = createLinkedList(1, 2, 3);
  assertEquals(list.pop(), 3);
  assertEquals(list.shift(), 1);
  assertEquals(list.toArray(), [2]);
  assertEquals(list.len(), 1);
});

Deno.test("LinkedList - first and last", () => {
  const list = createLinkedList(1, 2, 3);
  assertEquals(list.first(), 1);
  assertEquals(list.last(), 3);
});

Deno.test("LinkedList - indexOf", () => {
  const list = createLinkedList(1, 2, 3);
  assertEquals(list.indexOf(1), 0);
  assertEquals(list.indexOf(2), 1);
  assertEquals(list.indexOf(3), 2);
  assertEquals(list.indexOf(4), undefined);
});

Deno.test("LinkedList - swap and reverse", () => {
  const list = createLinkedList(1, 2, 3, 4, 5);
  list.swap(1, 3);
  assertEquals(list.toArray(), [1, 4, 3, 2, 5]);
  list.reverse();
  assertEquals(list.toArray(), [5, 2, 3, 4, 1]);
});

Deno.test("LinkedList - map, filter and reduce", () => {
  const list = createLinkedList(1, 2, 3, 4, 5);
  const mapped = list.map((val) => val * 2);
  assertEquals(mapped.toArray(), [2, 4, 6, 8, 10]);

  const filtered = list.filter((val) => val % 2 === 0);
  assertEquals(filtered.toArray(), [2, 4]);

  const reduced = list.reduce((acc, val) => acc + val, 0);
  assertEquals(reduced, 15);
});
