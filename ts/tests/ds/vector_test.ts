import { strict as assert } from 'node:assert';
import { test } from 'node:test';

import { createVector } from '#/ds/index.ts';

test('Vector - create empty', () => {
  const list = createVector<number>();
  assert.deepEqual(list.toArray(), []);
  assert.deepEqual(list.len(), 0);
  assert.deepEqual(list.cap(), 100);
  assert.ok(list.isEmpty());
});

test('Vector - create with initial values', () => {
  const list = createVector(1, 2, 3);
  assert.deepEqual(list.toArray(), [1, 2, 3]);
  assert.deepEqual(list.len(), 3);
  assert.deepEqual(list.cap(), 100);
  assert.ok(!list.isEmpty());
});

test('Vector - clear', () => {
  const list = createVector(1, 2, 3);
  list.clear();
  assert.ok(list.isEmpty());
  assert.deepEqual(list.cap(), 100);
  assert.deepEqual(list.toArray(), []);
});

test('Vector - cap should grow', () => {
  const list = createVector(...Array(99).fill(0));
  assert.deepEqual(list.cap(), 100);
  list.push(0, 0);
  assert.deepEqual(list.cap(), 200);
  assert.deepEqual(list.toArray(), Array(101).fill(0));
});

test('Vector - cap should shrink', () => {
  const list = createVector(...Array(1001).fill(0));
  assert.deepEqual(list.cap(), 1100);
  list.clear();
  assert.deepEqual(list.cap(), 199);
  assert.deepEqual(list.toArray(), []);
});

test('Vector - get and set', () => {
  const list = createVector(1, 2, 3);
  assert.deepEqual(list.get(0), 1);
  assert.deepEqual(list.get(1), 2);
  assert.deepEqual(list.get(2), 3);

  list.set(0, 10);
  list.set(1, 20);
  list.set(2, 30);
  assert.deepEqual(list.toArray(), [10, 20, 30]);
});

test('Vector - insert and remove', () => {
  const list = createVector();
  list.insert(0, 3);
  list.insert(0, 1);
  list.insert(1, 2);
  list.insert(list.len(), 4);
  list.insert(list.len(), 5);
  assert.deepEqual(list.toArray(), [1, 2, 3, 4, 5]);

  assert.deepEqual(list.remove(0), 1);
  assert.deepEqual(list.remove(1), 3);
  assert.deepEqual(list.remove(list.len() - 1), 5);
  assert.deepEqual(list.toArray(), [2, 4]);
});

test('Vector - push and unshift', () => {
  const list = createVector(1, 2, 3);
  list.push(4, 5, 6);
  list.unshift(-2, -1, 0);
  assert.deepEqual(list.toArray(), [-2, -1, 0, 1, 2, 3, 4, 5, 6]);
  assert.deepEqual(list.len(), 9);
});

test('Vector - pop and shift', () => {
  const list = createVector(1, 2, 3);
  assert.deepEqual(list.pop(), 3);
  assert.deepEqual(list.shift(), 1);
  assert.deepEqual(list.toArray(), [2]);
  assert.deepEqual(list.len(), 1);
});

test('Vector - first and last', () => {
  const list = createVector(1, 2, 3);
  assert.deepEqual(list.first(), 1);
  assert.deepEqual(list.last(), 3);
});

test('Vector - indexOf', () => {
  const list = createVector(1, 2, 3);
  assert.deepEqual(list.indexOf(1), 0);
  assert.deepEqual(list.indexOf(2), 1);
  assert.deepEqual(list.indexOf(3), 2);
  assert.deepEqual(list.indexOf(4), undefined);
});

test('Vector - swap and reverse', () => {
  const list = createVector(1, 2, 3, 4, 5);
  list.swap(1, 3);
  assert.deepEqual(list.toArray(), [1, 4, 3, 2, 5]);
  list.reverse();
  assert.deepEqual(list.toArray(), [5, 2, 3, 4, 1]);
});

test('Vector - map, filter and reduce', () => {
  const list = createVector(1, 2, 3, 4, 5);
  const mapped = list.map((val) => val * 2);
  assert.deepEqual(mapped.toArray(), [2, 4, 6, 8, 10]);

  const filtered = list.filter((val) => val % 2 === 0);
  assert.deepEqual(filtered.toArray(), [2, 4]);

  const reduced = list.reduce((acc, val) => acc + val, 0);
  assert.deepEqual(reduced, 15);
});
