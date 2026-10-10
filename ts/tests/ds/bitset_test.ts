import { strict as assert } from 'node:assert';
import { test } from 'node:test';

import { createBitset } from '#/ds/index.ts';

test('Bitset - create less than 64', () => {
  const bitset = createBitset(4);
  assert.deepEqual(bitset.size(), 4);
  assert.deepEqual(bitset.arrayLen(), 1);
  assert.deepEqual(bitset.toArray(), Array(4).fill(false));
});

test('Bitset - create more than 64', () => {
  const bitset = createBitset(255);
  assert.deepEqual(bitset.size(), 255);
  assert.deepEqual(bitset.arrayLen(), 4);
  assert.deepEqual(bitset.toArray(), Array(255).fill(false));
});

test('Bitset - get and set', () => {
  const bitset = createBitset(4);
  assert.ok(!bitset.get(0));
  assert.ok(!bitset.get(1));
  assert.ok(!bitset.get(2));
  assert.ok(!bitset.get(3));

  bitset.set(0);
  bitset.set(2);
  assert.deepEqual(bitset.toArray(), [true, false, true, false]);
  bitset.set();
  assert.deepEqual(bitset.toArray(), Array(4).fill(true));
});

test('Bitset - reset', () => {
  const bitset = createBitset(4);
  bitset.set();
  bitset.reset(0);
  bitset.reset(3);
  assert.deepEqual(bitset.toArray(), [false, true, true, false]);

  bitset.reset();
  assert.deepEqual(bitset.toArray(), Array(4).fill(false));
});
