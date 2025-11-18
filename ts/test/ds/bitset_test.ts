import { assertEquals, assertFalse } from "@std/assert";
import { createBitset } from "@/ds";

Deno.test("Bitset - create less than 64", () => {
  const bitset = createBitset(4);
  assertEquals(bitset.size(), 4);
  assertEquals(bitset.arrayLen(), 1);
  assertEquals(bitset.toArray(), Array(4).fill(false));
});

Deno.test("Bitset - create more than 64", () => {
  const bitset = createBitset(255);
  assertEquals(bitset.size(), 255);
  assertEquals(bitset.arrayLen(), 4);
  assertEquals(bitset.toArray(), Array(255).fill(false));
});

Deno.test("Bitset - get and set", () => {
  const bitset = createBitset(4);
  assertFalse(bitset.get(0));
  assertFalse(bitset.get(1));
  assertFalse(bitset.get(2));
  assertFalse(bitset.get(3));

  bitset.set(0);
  bitset.set(2);
  assertEquals(bitset.toArray(), [true, false, true, false]);
  bitset.set();
  assertEquals(bitset.toArray(), Array(4).fill(true));
});

Deno.test("Bitset - reset", () => {
  const bitset = createBitset(4);
  bitset.set();
  bitset.reset(0);
  bitset.reset(3);
  assertEquals(bitset.toArray(), [false, true, true, false]);

  bitset.reset();
  assertEquals(bitset.toArray(), Array(4).fill(false));
});
