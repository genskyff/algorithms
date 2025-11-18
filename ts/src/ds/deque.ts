// [start, end)
type Inner<T> = {
  data: T[];
  start: number;
  end: number;
  len: number;
  cap: number;
};

export type Deque<T> = {
  len(): number;
  cap(): number;
  isEmpty(): boolean;
  clear(): void;
  unshift(...vals: T[]): void;
  shift(): T | undefined;
  push(...vals: T[]): void;
  pop(): T | undefined;
  first(): T | undefined;
  last(): T | undefined;
  toArray(): T[];
};

export const createDeque = <T>(...vals: T[]): Deque<T> => {
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
    start: 0,
    end: _len,
    len: _len,
    cap: _cap,
  };

  const _shrink = () => {
    if (inner.cap > SHRINK_CAP && inner.len < inner.cap * LOW_FACTOR) {
      const baseCap = Math.max(INIT_CAP, inner.len * GROWTH_FACTOR);
      const newCap = ((baseCap + INIT_CAP - 1) / INIT_CAP) * INIT_CAP;
      const newData = Array<T>(newCap);
      for (let i = 0; i < inner.len; i++) {
        newData[i] = inner.data[(i + inner.start) % inner.cap];
      }
      inner.data = newData;
      inner.start = 0;
      inner.end = inner.len;
      inner.cap = newCap;
    }
  };

  const _grow = () => {
    if (inner.len == inner.cap) {
      const newCap = inner.cap * GROWTH_FACTOR;
      const newData = Array<T>(newCap);
      for (let i = 0; i < inner.len; i++) {
        newData[i] = inner.data[(i + inner.start) % inner.cap];
      }
      inner.data = newData;
      inner.start = 0;
      inner.end = inner.len;
      inner.cap = newCap;
    }
  };

  const len = () => inner.len;
  const cap = () => inner.cap;
  const isEmpty = () => inner.len === 0;
  const clear = () => {
    inner.len = 0;
    inner.start = 0;
    inner.end = 0;
    _shrink();
  };
  const unshift = (...vals: T[]) => {
    for (const val of vals.reverse()) {
      _grow();
      inner.start = (inner.start - 1 + inner.cap) % inner.cap;
      inner.data[inner.start] = val;
      inner.len++;
    }
  };
  const shift = () => {
    if (inner.len === 0) return undefined;
    const val = inner.data[inner.start];
    inner.start = (inner.start + 1) % inner.cap;
    inner.len--;
    _shrink();
    return val;
  };
  const push = (...vals: T[]) => {
    for (const val of vals) {
      _grow();
      inner.data[inner.end] = val;
      inner.end = (inner.end + 1) % inner.cap;
      inner.len++;
    }
  };
  const pop = () => {
    if (inner.len === 0) return undefined;
    const val = inner.data[(inner.end - 1 + inner.cap) % inner.cap];
    inner.end = (inner.end - 1 + inner.cap) % inner.cap;
    inner.len--;
    _shrink();
    return val;
  };
  const first = () => {
    if (inner.len === 0) return undefined;
    return inner.data[inner.start];
  };
  const last = () => {
    if (inner.len === 0) return undefined;
    return inner.data[(inner.end - 1 + inner.cap) % inner.cap];
  };
  const toArray = () => {
    const result = Array<T>(inner.len);
    for (let i = 0; i < inner.len; i++) {
      result[i] = inner.data[(inner.start + i) % inner.cap];
    }
    return result;
  };

  const api = {
    len,
    cap,
    isEmpty,
    clear,
    unshift,
    shift,
    push,
    pop,
    first,
    last,
    toArray,
  };

  return api;
};
