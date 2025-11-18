type Inner<T> = {
  data: T[];
  len: number;
  cap: number;
};

export type Vector<T> = {
  len(): number;
  cap(): number;
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
  map(fn: (val: T, idx?: number) => T): Vector<T>;
  filter(fn: (val: T, idx?: number) => boolean): Vector<T>;
  reduce<U>(fn: (acc: U, val: T, idx?: number) => U, init: U): U;
  forEach(fn: (val: T, idx?: number) => void): void;
  toArray(): T[];
};

export const createVector = <T>(...vals: T[]): Vector<T> => {
  const INIT_CAP = 100;
  const SHRINK_CAP = 1000;
  const LOW_FACTOR = 0.25;
  const GROWTH_FACTOR = 2;

  const _len = vals.length;
  const _cap = _len < INIT_CAP
    ? INIT_CAP
    : ((_len + INIT_CAP - 1) / INIT_CAP) * INIT_CAP;
  const _data = Array<T>(_cap);
  for (let i = 0; i < _len; i++) {
    _data[i] = vals[i];
  }
  const inner: Inner<T> = {
    data: _data,
    len: _len,
    cap: _cap,
  };

  const _checkIdx = (idx: number, closed = false) => {
    if (idx < 0 || idx >= (closed ? inner.len + 1 : inner.len)) {
      throw new Error(`Index out of bounds: ${idx}`);
    }
  };

  const _shrink = () => {
    if (inner.cap > SHRINK_CAP && inner.len < inner.cap * LOW_FACTOR) {
      const baseCap = Math.max(INIT_CAP, inner.len * GROWTH_FACTOR);
      const newCap = ((baseCap + INIT_CAP - 1) / INIT_CAP) * INIT_CAP;
      const newData = Array<T>(newCap);
      for (let i = 0; i < inner.len; i++) {
        newData[i] = inner.data[i];
      }
      inner.data = newData;
      inner.cap = newCap;
    }
  };

  const _grow = () => {
    if (inner.len == inner.cap) {
      const newCap = inner.cap * GROWTH_FACTOR;
      const newData = Array<T>(newCap);
      for (let i = 0; i < inner.len; i++) {
        newData[i] = inner.data[i];
      }
      inner.data = newData;
      inner.cap = newCap;
    }
  };

  const len = () => inner.len;
  const cap = () => inner.cap;

  const get = (idx: number) => {
    _checkIdx(idx);

    return inner.data[idx];
  };

  const set = (idx: number, val: T) => {
    _checkIdx(idx);

    inner.data[idx] = val;
  };

  const isEmpty = () => inner.len === 0;

  const clear = () => {
    inner.len = 0;
    _shrink();
  };

  const insert = (idx: number, val: T) => {
    _checkIdx(idx, true);
    _grow();

    for (let i = inner.len; i > idx; i--) {
      inner.data[i] = inner.data[i - 1];
    }

    inner.data[idx] = val;
    inner.len++;
  };

  const remove = (idx: number) => {
    _checkIdx(idx);

    const val = inner.data[idx];
    for (let i = idx; i < inner.len - 1; i++) {
      inner.data[i] = inner.data[i + 1];
    }
    inner.len--;
    _shrink();

    return val;
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
      insert(inner.len, val);
    }
  };

  const pop = () => {
    return remove(inner.len - 1);
  };

  const first = () => {
    return get(0);
  };

  const last = () => {
    return get(inner.len - 1);
  };

  const indexOf = (val: T) => {
    for (let i = 0; i < inner.len; i++) {
      if (inner.data[i] === val) {
        return i;
      }
    }
  };

  const swap = (i: number, j: number) => {
    _checkIdx(i);
    _checkIdx(j);
    if (i === j) return;

    const temp = inner.data[i];
    inner.data[i] = inner.data[j];
    inner.data[j] = temp;
  };

  const reverse = () => {
    let leftIdx = 0;
    let rightIdx = inner.len - 1;

    while (leftIdx < rightIdx) {
      const temp = inner.data[leftIdx];
      inner.data[leftIdx] = inner.data[rightIdx];
      inner.data[rightIdx] = temp;

      leftIdx++;
      rightIdx--;
    }
  };

  const map = (fn: (val: T, idx?: number) => T) => {
    const result = createVector<T>();
    for (let i = 0; i < inner.len; i++) {
      result.push(fn(inner.data[i], i));
    }
    return result;
  };

  const filter = (fn: (val: T, idx?: number) => boolean) => {
    const result = createVector<T>();
    for (let i = 0; i < inner.len; i++) {
      if (fn(inner.data[i], i)) {
        result.push(inner.data[i]);
      }
    }
    return result;
  };

  const reduce = <U>(fn: (acc: U, val: T, idx?: number) => U, init: U) => {
    let acc = init;
    for (let i = 0; i < inner.len; i++) {
      acc = fn(acc, inner.data[i], i);
    }
    return acc;
  };

  const forEach = (fn: (val: T, idx?: number) => void) => {
    for (let i = 0; i < inner.len; i++) {
      fn(inner.data[i], i);
    }
  };

  const toArray = () => {
    return inner.data.slice(0, inner.len);
  };

  const api = {
    len,
    cap,
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

  return api;
};
