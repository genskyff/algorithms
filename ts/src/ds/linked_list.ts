type Node<T> = {
  val: T;
  prev: Node<T>;
  next: Node<T>;
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
  map(fn: (val: T, idx?: number) => T): LinkedList<T>;
  filter(fn: (val: T, idx?: number) => boolean): LinkedList<T>;
  reduce<U>(fn: (acc: U, val: T, idx?: number) => U, init: U): U;
  forEach(fn: (val: T, idx?: number) => void): void;
  toArray(): T[];
};

export const createLinkedList = <T>(...vals: T[]): LinkedList<T> => {
  const _head = {} as Node<T>;
  const _tail = {} as Node<T>;
  _head.next = _tail;
  _tail.prev = _head;
  let _len = 0;

  const _checkIdx = (idx: number, closed = false) => {
    if (idx < 0 || idx >= (closed ? _len + 1 : _len)) {
      throw new Error(`Index out of bounds: ${idx}`);
    }
  };

  const _checkNode = (
    node: Node<T>,
    type: "linked" | "detached" = "linked",
  ) => {
    if (type === "linked" && !node.prev && !node.next) {
      throw new Error("Node is detached");
    } else if (type === "detached" && (node.prev || node.next)) {
      throw new Error("Node is already linked");
    }
  };

  const _getNode = (idx: number, closed = false): Node<T> => {
    _checkIdx(idx, closed);

    let cur: Node<T>;
    if (idx < _len / 2) {
      cur = _head.next;
      for (let i = 0; i < idx; i++) {
        cur = cur.next;
      }
    } else {
      cur = _tail.prev;
      for (let i = _len - 1; i > idx; i--) {
        cur = cur.prev;
      }
    }

    return cur;
  };

  const _link = (target: Node<T>, node: Node<T>) => {
    _checkNode(target);
    _checkNode(node, "detached");

    const next = target.next;
    target.next = node;
    next.prev = node;
    node.next = next;
    node.prev = target;

    _len++;
  };

  const _unlink = (node: Node<T>) => {
    _checkNode(node);

    const prev = node.prev;
    const next = node.next;
    if (prev) prev.next = next;
    if (next) next.prev = prev;
    node.prev = undefined!;
    node.next = undefined!;

    _len--;
  };

  const len = () => _len;

  const get = (idx: number) => {
    const node = _getNode(idx);
    return node.val;
  };

  const set = (idx: number, val: T) => {
    const node = _getNode(idx);
    if (node) node.val = val;
  };

  const isEmpty = () => _len === 0;

  const clear = () => {
    _head.next = _tail;
    _tail.prev = _head;
    _len = 0;
  };

  const insert = (idx: number, val: T) => {
    _checkIdx(idx, true);

    const node = { val } as Node<T>;
    const target = idx === 0 ? _head : _getNode(idx - 1, true);
    _link(target, node);
  };

  const remove = (idx: number) => {
    _checkIdx(idx);

    const node = _getNode(idx);
    _unlink(node);
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
    let cur = _getNode(0);
    for (let i = 0; i < _len; i++) {
      if (cur.val === val) return i;
      cur = cur.next!;
    }
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
    let leftNode = _getNode(0);
    let rightNode = _getNode(_len - 1);
    let leftIdx = 0;
    let rightIdx = _len - 1;

    while (leftIdx < rightIdx) {
      const temp = leftNode.val;
      leftNode.val = rightNode.val;
      rightNode.val = temp;

      leftIdx++;
      rightIdx--;
      leftNode = leftNode.next!;
      rightNode = rightNode.prev!;
    }
  };

  const map = (fn: (val: T, idx?: number) => T) => {
    const result = createLinkedList<T>();
    let cur: Node<T> = _head.next;
    for (let i = 0; i < _len; i++) {
      result.push(fn(cur.val, i));
      cur = cur.next;
    }
    return result;
  };

  const filter = (fn: (val: T, idx?: number) => boolean) => {
    const result = createLinkedList<T>();
    let cur: Node<T> = _head.next;
    for (let i = 0; i < _len; i++) {
      if (fn(cur.val, i)) {
        result.push(cur.val);
      }
      cur = cur.next;
    }
    return result;
  };

  const reduce = <U>(fn: (acc: U, val: T, idx?: number) => U, init: U) => {
    let acc = init;
    let cur: Node<T> = _head.next;
    for (let i = 0; i < _len; i++) {
      acc = fn(acc, cur.val, i);
      cur = cur.next;
    }
    return acc;
  };

  const forEach = (fn: (val: T, idx?: number) => void) => {
    let cur: Node<T> = _head.next;
    for (let i = 0; i < _len; i++) {
      fn(cur.val, i);
      cur = cur.next;
    }
  };

  const toArray = () => {
    const result: T[] = [];
    let cur: Node<T> = _head.next;
    for (let i = 0; i < _len; i++) {
      result.push(cur.val);
      cur = cur.next;
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
