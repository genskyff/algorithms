type Bitset = {
  size(): number;
  arrayLen(): number;
  get(idx: number): boolean;
  set(idx?: number): void;
  reset(idx?: number): void;
  toArray(): boolean[];
};

export const createBitset = (size: number): Bitset => {
  if (size <= 0) {
    throw new Error("Size must be a positive integer");
  }

  const arrayLen = Math.ceil(size / 64);
  const bitmap = Array(arrayLen).fill(0n);

  const _checkIdx = (idx: number) => {
    if (idx < 0 || idx >= size) {
      throw new Error(`Index out of bounds: ${idx}`);
    }
  };

  const get = (idx: number): boolean => {
    _checkIdx(idx);
    const arrayIdx = Math.floor(idx / 64);
    const bitIdx = BigInt(idx % 64);
    return (bitmap[arrayIdx] & (1n << bitIdx)) !== 0n;
  };

  const set = (idx?: number): void => {
    if (idx !== undefined) {
      _checkIdx(idx);
      const arrayIdx = Math.floor(idx / 64);
      const bitIdx = BigInt(idx % 64);
      bitmap[arrayIdx] |= 1n << bitIdx;
    } else {
      bitmap.fill(~0n);
    }
  };

  const reset = (idx?: number) => {
    if (idx !== undefined) {
      _checkIdx(idx);
      const arrayIdx = Math.floor(idx / 64);
      const bitIdx = BigInt(idx % 64);
      bitmap[arrayIdx] &= ~(1n << bitIdx);
    } else {
      bitmap.fill(0n);
    }
  };

  const toArray = () => {
    return Array.from({ length: size }, (_, idx) => get(idx));
  };

  const api = {
    size: () => size,
    arrayLen: () => arrayLen,
    get,
    set,
    reset,
    toArray,
  };

  return api;
};
