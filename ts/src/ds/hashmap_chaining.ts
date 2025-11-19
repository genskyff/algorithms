import type { LinkedList } from "@/ds";

type Pair<T> = {
  readonly key: string;
  value: T;
};

type Bucket<T> = LinkedList<Pair<T>>;
type Buckets<T> = Bucket<T>[];

type Inner<T> = {
  data: Buckets<T>;
  len: number;
  cap: number;
};

export type HashMap<T> = {
  len(): number;
  cap(): number;
  get(key: string): T | undefined;
  isEmpty(): boolean;
  clear(): void;
  insert(key: string, value: T): void;
  remove(key: string): T | undefined;
  keys(): string[];
  values(): T[];
  toArray(): [];
};

export const createHashMap = <T>(...vals: Pair<T>[]): HashMap<T> => {
  const INIT_CAP = 100;
  const SHRINK_CAP = 1000;
  const BUCKET_CAP = 10;
  const LOW_FACTOR = 0.25;
  const LOAD_FACTOR = 0.75;
  const GROWTH_FACTOR = 2;

  const _len = vals.length;
  const _cap =
    _len < INIT_CAP ? INIT_CAP : ((_len + INIT_CAP - 1) / INIT_CAP) * INIT_CAP;
  const _data = Array<T>(_cap);
  for (let i = 0; i < _len; i++) {
    _data[i] = vals[i];
  }
  const inner: Inner<T> = {
    data: _data,
    len: _len,
    cap: _cap,
  };

  const _migrate = (newCap: number) => {};

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
    return inner.data[idx];
  };

  const isEmpty = () => inner.len === 0;

  const clear = () => {
    inner.len = 0;
    _shrink();
  };

  const insert = (idx: number, val: T) => {
    _grow();

    for (let i = inner.len; i > idx; i--) {
      inner.data[i] = inner.data[i - 1];
    }

    inner.data[idx] = val;
    inner.len++;
  };

  const remove = (idx: number) => {
    const val = inner.data[idx];
    for (let i = idx; i < inner.len - 1; i++) {
      inner.data[i] = inner.data[i + 1];
    }
    inner.len--;
    _shrink();

    return val;
  };

  const keys = () => {};

  const values = () => {};

  const toArray = () => {
    return inner.data.slice(0, inner.len);
  };

  const api = {
    len,
    cap,
    get,
    isEmpty,
    clear,
    insert,
    remove,
    keys,
    values,
    toArray,
  };

  return api;
};
