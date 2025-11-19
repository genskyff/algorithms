import { createLinkedList, type LinkedList } from "@/ds";

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
  toArray(): Pair<T>[];
};

export const createHashMap = <T>(...vals: Pair<T>[]): HashMap<T> => {
  const INIT_CAP = 100;
  const SHRINK_CAP = 1000;
  const BUCKET_CAP = 10;
  const LOW_FACTOR = 0.25;
  const LOAD_FACTOR = 0.75;
  const GROWTH_FACTOR = 2;

  const _hash = (key: string, cap: number): number => {
    const PRIME = 16777619;
    const OFFSET_BASIS = 2166136261;
    let hash = OFFSET_BASIS;

    for (let i = 0; i < key.length; i++) {
      hash ^= key.charCodeAt(i);
      hash = Math.imul(hash, PRIME);
    }

    return (hash >>> 0) % cap;
  };

  const _initBuckets = (cap: number): Buckets<T> => {
    const buckets: Buckets<T> = new Array(cap);
    for (let i = 0; i < cap; i++) {
      buckets[i] = createLinkedList<Pair<T>>();
    }
    return buckets;
  };

  const inner: Inner<T> = {
    data: _initBuckets(INIT_CAP),
    len: 0,
    cap: INIT_CAP,
  };

  const _migrate = (newCap: number) => {
    const newBuckets = _initBuckets(newCap);

    for (const bucket of inner.data) {
      bucket.forEach((pair) => {
        const idx = _hash(pair.key, newCap);
        newBuckets[idx].push(pair);
      });
    }

    inner.data = newBuckets;
    inner.cap = newCap;
  };

  const _shrink = () => {
    if (inner.cap > SHRINK_CAP && inner.len / inner.cap < LOW_FACTOR) {
      _migrate(Math.floor(inner.cap / GROWTH_FACTOR));
    }
  };

  const _grow = () => {
    _migrate(inner.cap * GROWTH_FACTOR);
  };

  const len = () => inner.len;
  const cap = () => inner.cap;
  const isEmpty = () => inner.len === 0;

  const get = (key: string): T | undefined => {
    const idx = _hash(key, inner.cap);
    const bucket = inner.data[idx];
    return bucket.reduce<T | undefined>((acc, pair) => {
      if (acc !== undefined) return acc;
      if (pair.key === key) return pair.value;
      return undefined;
    }, undefined);
  };

  const clear = () => {
    inner.data = _initBuckets(INIT_CAP);
    inner.len = 0;
    inner.cap = INIT_CAP;
  };

  const insert = (key: string, value: T) => {
    const idx = _hash(key, inner.cap);
    const bucket = inner.data[idx];

    let found = false;
    bucket.forEach((pair) => {
      if (!found && pair.key === key) {
        pair.value = value;
        found = true;
      }
    });

    if (!found) {
      bucket.push({ key, value });
      inner.len++;
      if (inner.len / inner.cap > LOAD_FACTOR || bucket.len() > BUCKET_CAP) {
        _grow();
      }
    }
  };

  const remove = (key: string): T | undefined => {
    const idx = _hash(key, inner.cap);
    const bucket = inner.data[idx];

    let removeIdx = -1;
    let val: T | undefined = undefined;

    bucket.forEach((pair, i) => {
      if (removeIdx === -1 && pair.key === key) {
        removeIdx = i!;
        val = pair.value;
      }
    });

    if (removeIdx !== -1) {
      bucket.remove(removeIdx);
      inner.len--;
      _shrink();
      return val;
    }
    return undefined;
  };

  const keys = (): string[] => {
    const res: string[] = [];
    for (const bucket of inner.data) {
      bucket.forEach((pair) => res.push(pair.key));
    }
    return res;
  };

  const values = (): T[] => {
    const res: T[] = [];
    for (const bucket of inner.data) {
      bucket.forEach((pair) => res.push(pair.value));
    }
    return res;
  };

  const toArray = (): Pair<T>[] => {
    const res: Pair<T>[] = [];
    for (const bucket of inner.data) {
      bucket.forEach((pair) => res.push(pair));
    }
    return res;
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

  for (const val of vals) {
    insert(val.key, val.value);
  }

  return api;
};
