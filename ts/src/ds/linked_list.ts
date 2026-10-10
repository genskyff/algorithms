type Node<T> = {
  val: T;
  prev: Node<T> | undefined;
  next: Node<T> | undefined;
};

export type LinkedList<T> = {
  len(): number;
  get(idx: number): T | undefined;
  set(idx: number, val: T): void;
  isEmpty(): boolean;
  clear(): void;
  insert(idx: number, val: T): void;
  remove(idx: number): T | undefined;
  unshift(...vals: T[]): void;
  shift(): T | undefined;
  push(...vals: T[]): void;
  pop(): T | undefined;
  first(): T | undefined;
  last(): T | undefined;
  indexOf(val: T): number | undefined;
  swap(i: number, j: number): void;
  reverse(): void;
  map(fn: (val: T, idx: number) => T): LinkedList<T>;
  filter(fn: (val: T, idx: number) => boolean): LinkedList<T>;
  reduce<U>(fn: (acc: U, val: T, idx: number) => U, init: U): U;
  forEach(fn: (val: T, idx: number) => void): void;
  toArray(): T[];
};

export const createLinkedList = <T>(...vals: T[]): LinkedList<T> => {
  let _head: Node<T> | undefined;
  let _tail: Node<T> | undefined;
  let _len = 0;

  const _checkIdx = (idx: number, closed = false) => {
    if (idx < 0 || idx >= (closed ? _len + 1 : _len)) {
      throw new Error(`Index out of bounds: ${idx}`);
    }
  };

  const _getNode = (idx: number): Node<T> => {
    _checkIdx(idx);

    let cur: Node<T> | undefined;
    if (idx < _len / 2) {
      cur = _head;
      for (let i = 0; i < idx; i++) {
        cur = cur?.next;
      }
    } else {
      cur = _tail;
      for (let i = _len - 1; i > idx; i--) {
        cur = cur?.prev;
      }
    }

    if (!cur) {
      throw new Error(`Index out of bounds: ${idx}`);
    }
    return cur;
  };

  const len = () => _len;

  const get = (idx: number) => {
    return _getNode(idx).val;
  };

  const set = (idx: number, val: T) => {
    _getNode(idx).val = val;
  };

  const isEmpty = () => _len === 0;

  const clear = () => {
    _head = undefined;
    _tail = undefined;
    _len = 0;
  };

  const insert = (idx: number, val: T) => {
    _checkIdx(idx, true);

    const prev = idx === 0 ? undefined : _getNode(idx - 1);
    const next = prev ? prev.next : _head;
    const node: Node<T> = { val, prev, next };

    if (prev) prev.next = node;
    else _head = node;
    if (next) next.prev = node;
    else _tail = node;

    _len++;
  };

  const remove = (idx: number) => {
    const node = _getNode(idx);

    if (node.prev) node.prev.next = node.next;
    else _head = node.next;
    if (node.next) node.next.prev = node.prev;
    else _tail = node.prev;

    _len--;
    return node.val;
  };

  const unshift = (...vals: T[]) => {
    for (const val of vals.reverse()) {
      insert(0, val);
    }
  };

  const shift = () => {
    return remove(0);
  };

  const push = (...vals: T[]) => {
    for (const val of vals) {
      insert(_len, val);
    }
  };

  const pop = () => {
    return remove(_len - 1);
  };

  const first = () => {
    return get(0);
  };

  const last = () => {
    return get(_len - 1);
  };

  const indexOf = (val: T) => {
    let cur = _head;
    for (let i = 0; cur; i++) {
      if (cur.val === val) return i;
      cur = cur.next;
    }
    return undefined;
  };

  const swap = (i: number, j: number) => {
    _checkIdx(i);
    _checkIdx(j);
    if (i === j) return;

    const nodeA = _getNode(i);
    const nodeB = _getNode(j);
    const temp = nodeA.val;
    nodeA.val = nodeB.val;
    nodeB.val = temp;
  };

  const reverse = () => {
    let leftNode = _head;
    let rightNode = _tail;
    let leftIdx = 0;
    let rightIdx = _len - 1;

    while (leftNode && rightNode && leftIdx < rightIdx) {
      const temp = leftNode.val;
      leftNode.val = rightNode.val;
      rightNode.val = temp;

      leftIdx++;
      rightIdx--;
      leftNode = leftNode.next;
      rightNode = rightNode.prev;
    }
  };

  const map = (fn: (val: T, idx: number) => T) => {
    const result = createLinkedList<T>();
    let cur = _head;
    for (let i = 0; cur; i++) {
      result.push(fn(cur.val, i));
      cur = cur.next;
    }
    return result;
  };

  const filter = (fn: (val: T, idx: number) => boolean) => {
    const result = createLinkedList<T>();
    let cur = _head;
    for (let i = 0; cur; i++) {
      if (fn(cur.val, i)) {
        result.push(cur.val);
      }
      cur = cur.next;
    }
    return result;
  };

  const reduce = <U>(fn: (acc: U, val: T, idx: number) => U, init: U) => {
    let acc = init;
    let cur = _head;
    for (let i = 0; cur; i++) {
      acc = fn(acc, cur.val, i);
      cur = cur.next;
    }
    return acc;
  };

  const forEach = (fn: (val: T, idx: number) => void) => {
    let cur = _head;
    for (let i = 0; cur; i++) {
      fn(cur.val, i);
      cur = cur.next;
    }
  };

  const toArray = () => {
    const result: T[] = [];
    for (let cur = _head; cur; cur = cur.next) {
      result.push(cur.val);
    }
    return result;
  };

  const api = {
    len,
    get,
    set,
    isEmpty,
    clear,
    insert,
    remove,
    unshift,
    shift,
    push,
    pop,
    first,
    last,
    indexOf,
    swap,
    reverse,
    map,
    filter,
    reduce,
    forEach,
    toArray,
  };

  for (const val of vals) {
    push(val);
  }

  return api;
};
