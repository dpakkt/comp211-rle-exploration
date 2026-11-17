# Run-Length Encoding (RLE) Exploration

## About

For my COMP 211 Checkoff 3, I decided to explore Run-Length Encoding (RLE), which is a basic compression technique that represents repeated values using counts instead of storing every value separately.

For example, instead of storing `AAAABBCC`, RLE stores it as:

`04 41 02 42 02 43`

Each pair represents how many times a byte repeats, followed by the byte itself.

I wanted to understand how this works in C, so I worked on implementing both an encoder and a decoder. As I worked through the code, I also explored some of the problems that can come up with memory allocation, binary data, and edge cases.

## What I Learned

### 1. A byte's meaning depends on where it is in the format

One thing I found interesting was that a byte doesn't always have one obvious meaning. In my RLE format, the decoder uses the position of each byte to decide whether it represents a count or a data value.

This also helped me understand why the encoded output can't just be treated like a regular C string. Binary data can contain zero bytes, so I needed to keep track of the length separately instead of relying on functions like `strlen`.

### 2. The encoder and decoder handle memory differently

I initially thought the encoder and decoder would allocate memory in pretty similar ways, but they actually have different requirements.

The encoder can allocate up to twice the input size because every byte could end up being its own run. The decoder doesn't know the exact output size until it looks at the count values in the encoded input.

Because of this, my decoder uses two passes. The first pass calculates how much memory is needed, and the second pass actually expands the data.

### 3. Small mistakes with loop conditions can cause bigger problems

I also experimented with intentionally changing parts of my code to see what would happen. One example was changing `<` to `<=` in a loop, which caused the decoder to write more bytes than it was supposed to.

Another issue came from the maximum run length. Since the count is stored in one byte, it can only hold values from 1 to 255. Testing 255, 256, and 300 repeated characters helped me understand why these boundary cases matter.

These examples showed me how a small mistake in C can lead to incorrect output or memory errors.

## Files

- `rle.c` – My encoder and decoder implementation.
- `test_rle.c` – Tests I used to check different inputs and edge cases.
- `examples.md` – Examples showing how different inputs are encoded.
- `resources.md` – Resources I referred to during the exploration.
- `ai-reflection.md` – My reflection on using AI during this project.
- `presentation.pdf` – My Checkoff 3 presentation.

## How to Run

To compile the code and tests:

    gcc -Wall -Wextra -g rle.c test_rle.c -o test_rle

To run the tests:

    ./test_rle

I also used AddressSanitizer and UndefinedBehaviorSanitizer to help catch memory errors:

    gcc -Wall -Wextra -g -fsanitize=address,undefined rle.c test_rle.c -o test_rle

    ./test_rle

## Final Takeaway

I started this project thinking RLE would mostly be about counting repeated characters. But actually implementing it in C made me pay much more attention to how bytes are represented, how memory is allocated, and what happens when values reach their limits.

I think the biggest thing I took away was that understanding how an algorithm works is only part of implementing it correctly. You also have to think about the details of the language and how your code handles unusual inputs.
