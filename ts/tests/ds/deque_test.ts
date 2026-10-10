import { strict as assert } from 'node:assert';
import { test } from 'node:test';

import { createDeque } from '#/ds/index.ts';

test('Deque - create empty', () => {
  const list = createDeque<number>();
  assert.deepEqual(list.toArray(), []);
  assert.deepEqual(list.len(), 0);
  assert.deepEqual(list.cap(), 100);
  assert.ok(list.isEmpty());
});

test('Deque - create with initial values', () => {
  const list = createDeque(1, 2, 3);
  assert.deepEqual(list.toArray(), [1, 2, 3]);
  assert.deepEqual(list.len(), 3);
  assert.deepEqual(list.cap(), 100);
  assert.ok(!list.isEmpty());
});

test('Deque - clear', () => {
  const list = createDeque(1, 2, 3);
  list.clear();
  assert.ok(list.isEmpty());
  assert.deepEqual(list.cap(), 100);
  assert.deepEqual(list.toArray(), []);
});

test('Deque - cap should grow', () => {
  const list = createDeque(...Array(99).fill(0));
  assert.deepEqual(list.cap(), 100);
  list.push(0, 0);
  assert.deepEqual(list.cap(), 200);
  assert.deepEqual(list.toArray(), Array(101).fill(0));
});

test('Deque - cap should shrink', () => {
  const list = createDeque(...Array(1001).fill(0));
  assert.deepEqual(list.cap(), 1100);
  list.clear();
  assert.deepEqual(list.cap(), 199);
  assert.deepEqual(list.toArray(), []);
});

test('Deque - push and unshift', () => {
  const list = createDeque(1, 2, 3);
  list.push(4, 5, 6);
  list.unshift(-2, -1, 0);
  assert.deepEqual(list.toArray(), [-2, -1, 0, 1, 2, 3, 4, 5, 6]);
  assert.deepEqual(list.len(), 9);
});

test('Deque - pop and shift', () => {
  const list = createDeque(1, 2, 3);
  assert.deepEqual(list.pop(), 3);
  assert.deepEqual(list.shift(), 1);
  assert.deepEqual(list.toArray(), [2]);
  assert.deepEqual(list.len(), 1);
});

test('Deque - first and last', () => {
  const list = createDeque(1, 2, 3);
  assert.deepEqual(list.first(), 1);
  assert.deepEqual(list.last(), 3);
});
