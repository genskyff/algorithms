import { assertEquals } from "@std/assert";
import { createLinkedList } from "@ds/linked_list.ts";

const list = createLinkedList(1, 2, 3);

Deno.test("LinkedList creation", () => {
  assertEquals(list.toArray(), [1, 2, 3]);
});

console.log(list.toArray());
