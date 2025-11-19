import { assert, assertEquals, assertFalse } from "@std/assert";
import { createHashMap } from "@/ds";

Deno.test("HashMap - create empty", () => {
  const map = createHashMap<number>();
  assertEquals(map.len(), 0);
  assert(map.isEmpty());
  assertEquals(map.toArray(), []);
});

Deno.test("HashMap - insert and get", () => {
  const map = createHashMap<number>();
  map.insert("one", 1);
  map.insert("two", 2);
  map.insert("three", 3);

  assertEquals(map.len(), 3);
  assertFalse(map.isEmpty());
  assertEquals(map.get("one"), 1);
  assertEquals(map.get("two"), 2);
  assertEquals(map.get("three"), 3);
  assertEquals(map.get("four"), undefined);
});

Deno.test("HashMap - update value", () => {
  const map = createHashMap<number>();
  map.insert("key", 1);
  assertEquals(map.get("key"), 1);
  
  map.insert("key", 2);
  assertEquals(map.get("key"), 2);
  assertEquals(map.len(), 1);
});

Deno.test("HashMap - remove", () => {
  const map = createHashMap<number>();
  map.insert("a", 1);
  map.insert("b", 2);
  
  assertEquals(map.remove("a"), 1);
  assertEquals(map.len(), 1);
  assertEquals(map.get("a"), undefined);
  
  assertEquals(map.remove("c"), undefined);
  assertEquals(map.len(), 1);
  
  assertEquals(map.remove("b"), 2);
  assertEquals(map.len(), 0);
  assert(map.isEmpty());
});

Deno.test("HashMap - clear", () => {
  const map = createHashMap<number>();
  map.insert("a", 1);
  map.insert("b", 2);
  
  map.clear();
  assertEquals(map.len(), 0);
  assert(map.isEmpty());
  assertEquals(map.get("a"), undefined);
});

Deno.test("HashMap - keys, values, toArray", () => {
  const map = createHashMap<number>();
  map.insert("a", 1);
  map.insert("b", 2);
  
  const keys = map.keys().sort();
  const values = map.values().sort((a, b) => a - b);
  
  assertEquals(keys, ["a", "b"]);
  assertEquals(values, [1, 2]);
  
  // Order of toArray is not guaranteed to be sorted, but should contain all elements
  const pairs = map.toArray();
  assertEquals(pairs.length, 2);
  const pairA = pairs.find(p => p.key === "a");
  const pairB = pairs.find(p => p.key === "b");
  assertEquals(pairA?.value, 1);
  assertEquals(pairB?.value, 2);
});

Deno.test("HashMap - resize grow", () => {
  const map = createHashMap<number>();
  // Default INIT_CAP is 100, LOAD_FACTOR 0.75 -> grow at > 75 elements
  for (let i = 0; i < 100; i++) {
    map.insert(`key${i}`, i);
  }
  
  assertEquals(map.len(), 100);
  // Cap should have doubled from 100 -> 200
  assertEquals(map.cap(), 200);
  
  for (let i = 0; i < 100; i++) {
    assertEquals(map.get(`key${i}`), i);
  }
});

Deno.test("HashMap - resize shrink", () => {
  const map = createHashMap<number>();
  // Insert many to grow beyond SHRINK_CAP (1000)
  // We need cap > 1000 to test shrink.
  // Start at 100. Grow path: 100 -> 200 -> 400 -> 800 -> 1600.
  // To reach 1600 cap, we need to insert roughly 800 * 0.75 = 600 elements.
  
  const count = 1000;
  for (let i = 0; i < count; i++) {
    map.insert(`key${i}`, i);
  }
  
  // Cap should be at least 1600.
  // 1000 elements. 1600 * 0.75 = 1200. Not grown again.
  assertEquals(map.cap(), 1600);
  
  // Remove until low factor (0.25) is reached
  // 1600 * 0.25 = 400.
  
  // Remove down to 300 elements.
  for (let i = 300; i < count; i++) {
    map.remove(`key${i}`);
  }
  
  assertEquals(map.len(), 300);
  // 300 / 1600 = 0.18 < 0.25. Should shrink.
  // New cap = 1600 / 2 = 800.
  assertEquals(map.cap(), 800);
  
  // Verify remaining elements
  for (let i = 0; i < 10; i++) {
      assertEquals(map.get(`key${i}`), i);
  }
});

Deno.test("HashMap - collision handling", () => {
    // Force collisions by using keys that might hash same (hard to predict without knowing hash implementation details perfectly, but we can rely on pidgeonhole principle if we insert enough, or mock hash... but we can't mock internal hash).
    // Instead we just trust the logic handles it.
    // Let's insert enough elements to likely cause collisions in a small bucket size if we force small cap?
    // We can't force small cap easily from outside.
    
    const map = createHashMap<number>();
    // Just insert a bunch.
    for (let i=0; i<100; i++) {
        map.insert(i.toString(), i);
    }
    assertEquals(map.len(), 100);
    for (let i=0; i<100; i++) {
        assertEquals(map.get(i.toString()), i);
    }
});
