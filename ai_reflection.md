AI Exploration Reflection
How I Started
When I first started this exploration, I wanted to learn more about Run-Length Encoding and how it could be implemented in C. I understood the general idea of compression, but I hadn't really thought about how the data would actually be stored or how the encoder and decoder would work behind the scenes.
I started by asking basic questions about how RLE works and what the encoded output looks like. As I understood more, I started asking questions that were more specific to my implementation.
How My Questions Changed
At first, most of my questions were about understanding the format itself. I wanted to know how repeated characters were represented and how the decoder knew what to do with each byte.
After that, I started focusing more on the C side of the implementation. I explored how much memory the encoder and decoder needed, why the decoder required two passes, and what could happen if a count went past the maximum value of 255.
One of the most helpful parts was looking at code that had mistakes in it. Instead of only seeing the correct version, I got to work through what would happen if I changed a loop condition or used memory after freeing it.
How I Used AI
I mainly used AI as a way to work through problems and check whether I actually understood what was happening.
I asked it to explain concepts in simpler terms, walk through examples one step at a time, and give me questions that tested my understanding. I also tried answering those questions myself before getting feedback.
Some of the discussions that helped me most were about unsigned integer overflow, memory allocation, and off-by-one errors. For example, I initially made a mistake when tracing one of the encoder bugs because I didn't account for the final loop iteration. Going back through each step helped me understand where my reasoning went wrong.
I also used AI to help test my implementation and think about edge cases, especially inputs involving 255, 256, and 300 repeated bytes. This made me realize that code can appear to work with normal inputs while still having problems at its boundaries.
What I Learned
The biggest thing I learned was that implementing an algorithm in C involves a lot more than just understanding the basic logic.
Before this exploration, I probably would have thought of RLE as simply counting repeated characters. But working through the implementation made me think about binary data, pointers, memory allocation, integer limits, and what happens when something goes wrong.
I also learned that it's important to actually trace code and test different cases instead of assuming that something works just because it compiles.
If I were doing this exploration again, I would probably start testing edge cases earlier instead of focusing so much on getting the basic implementation working first. I also would spend more time trying to explain the concepts without looking at the code, since that is a good way to tell whether I really understand them.
AI Conversation
Claude conversation:https://claude.ai/share/b2a34681-f5f3-40f1-ad87-f043a85be59f 

