import { strict as assert } from 'node:assert';
import { test } from 'node:test';

import { createLinkedList } from '#/ds/index.ts';

test('LinkedList - create empty', () => {
  const list = createLinkedList<number>();
  assert.deepEqual(list.toArray(), []);
  assert.deepEqual(list.len(), 0);
  assert.ok(list.isEmpty());
});

test('LinkedList - create with initial values', () => {
  const list = createLinkedList(1, 2, 3);
  assert.deepEqual(list.toArray(), [1, 2, 3]);
  assert.deepEqual(list.len(), 3);
  assert.ok(!list.isEmpty());
});

test('LinkedList - clear', () => {
  const list = createLinkedList(1, 2, 3);
  list.clear();
  assert.deepEqual(list.toArray(), []);
  assert.deepEqual(list.len(), 0);
  assert.ok(list.isEmpty());
});

test('LinkedList - get and set', () => {
  const list = createLinkedList(1, 2, 3);
  assert.deepEqual(list.get(0), 1);
  assert.deepEqual(list.get(1), 2);
  assert.deepEqual(list.get(2), 3);

  list.set(0, 10);
  list.set(1, 20);
  list.set(2, 30);
  assert.deepEqual(list.toArray(), [10, 20, 30]);
});

test('LinkedList - insert and remove', () => {
  const list = createLinkedList();
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

test('LinkedList - push and unshift', () => {
  const list = createLinkedList(1, 2, 3);
  list.push(4, 5, 6);
  list.unshift(-2, -1, 0);
  assert.deepEqual(list.toArray(), [-2, -1, 0, 1, 2, 3, 4, 5, 6]);
  assert.deepEqual(list.len(), 9);
});

test('LinkedList - pop and shift', () => {
  const list = createLinkedList(1, 2, 3);
  assert.deepEqual(list.pop(), 3);
  assert.deepEqual(list.shift(), 1);
  assert.deepEqual(list.toArray(), [2]);
  assert.deepEqual(list.len(), 1);
});

test('LinkedList - first and last', () => {
  const list = createLinkedList(1, 2, 3);
  assert.deepEqual(list.first(), 1);
  assert.deepEqual(list.last(), 3);
});

test('LinkedList - indexOf', () => {
  const list = createLinkedList(1, 2, 3);
  assert.deepEqual(list.indexOf(1), 0);
  assert.deepEqual(list.indexOf(2), 1);
  assert.deepEqual(list.indexOf(3), 2);
  assert.deepEqual(list.indexOf(4), undefined);
});

test('LinkedList - swap and reverse', () => {
  const list = createLinkedList(1, 2, 3, 4, 5);
  list.swap(1, 3);
  assert.deepEqual(list.toArray(), [1, 4, 3, 2, 5]);
  list.reverse();
  assert.deepEqual(list.toArray(), [5, 2, 3, 4, 1]);
});

test('LinkedList - map, filter and reduce', () => {
  const list = createLinkedList(1, 2, 3, 4, 5);
  const mapped = list.map((val) => val * 2);
  assert.deepEqual(mapped.toArray(), [2, 4, 6, 8, 10]);

  const filtered = list.filter((val) => val % 2 === 0);
  assert.deepEqual(filtered.toArray(), [2, 4]);

  const reduced = list.reduce((acc, val) => acc + val, 0);
  assert.deepEqual(reduced, 15);
});
