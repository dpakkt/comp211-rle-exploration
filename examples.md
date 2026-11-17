# RLE Examples

These are some of the examples I used while exploring Run-Length Encoding and testing my implementation.

## 1. Basic Encoding

Original input:

`AAAABBCC`

Encoded output:

`04 41 02 42 02 43`

Each pair represents a count followed by a byte value:

- `04 41` = four A's
- `02 42` = two B's
- `02 43` = two C's

The decoder reads each pair and expands it back into the original input.

## 2. When RLE Makes Data Larger

Original input:

`ABCDEFGH`

Encoded output:

`01 41 01 42 01 43 01 44 01 45 01 46 01 47 01 48`

Since none of the characters repeat, each character needs its own two-byte pair.

The original input is 8 bytes, while the encoded output is 16 bytes. This showed me that RLE does not always reduce the size of data.

## 3. Binary Data and Zero Bytes

Original input:

`00 00 00 41`

Encoded output:

`03 00 01 41`

This represents three zero bytes followed by one A.

This example helped demonstrate why the encoded output needs to be treated as binary data instead of a normal C string. A zero byte can be part of the actual data and does not mean the input has ended.

## 4. The Maximum Run Length

The count is stored in one byte, so its maximum value is 255.

For 255 repeated A's:

`FF 41`

For 256 repeated A's:

`FF 41 01 41`

The encoder splits the run into two pairs because 256 cannot fit into a single count byte.

For 300 repeated A's:

`FF 41 2D 41`

This represents 255 A's followed by another 45 A's.

## 5. Testing Invalid Input

I also tested how the decoder handles invalid encoded data.

Examples included:

- An input with an odd number of bytes, which cannot form complete pairs.
- A count of zero, which is invalid in this format.
- A NULL input pointer with a nonzero length.
- A NULL output-length pointer.

These tests helped me understand why validating input before accessing memory is important.

## 6. Bugs Found During Testing

I explored two examples of off-by-one errors.

**Decoder bug:**

Changing `k < count` to `k <= count` causes the inner loop to write
