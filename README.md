# Hash Tables Internals:

Hashtables are used as building blocks of language runtimes.
For example, when we define a class with members and functions and call something like box.put(), the language runtime needs to figure out:
- which object box refers to,
- which method put is being invoked,
- and then execute that function for the object.
In many languages, classes themselves are implemented using hashtables.

Similarly, when we declare a variable like int a = 10; and later use a, the runtime needs to know where a is stored — this is called variable lookup.

So, hashtables are not just used in business applications but also play a crucial role in the internal workings of programming languages themselves.

**Goal:** store key–value pairs with (amortized) near constant-time O(1) insert, lookup, and delete.

For this hash-tables rely on two ideas:

### 1. **Map an application key to a large integer range [0, N):**
    The main idea for this is that which ever key user wants to put in hash-table language cannot restruct you.
    Language should be able to store whatever data strcuture user wants to use a key be allowed. So there should
    be an mechanism to map incomming key to a wide range of integer.

   - The large integer range is called hashkey which is generared using a hash function.
   - This is the hash function: hash(key) -> [0, N).
   - Keys can be any type (string, numbers, tuples, user-defined classes).
   - The hash must be:
     - Deterministic (same key → same hash every time)
     - Fast
     - Well-distributed (minimize collisions)
     - Ideally uses only immutable key data.
     
### 2. **Map that large integer to a smaller range (table index) [0, m).:**
      If the range was not big, then we could just make an array and store value in hashvalue index,
      For N=10, we need 4*10 = 40B; For N=100, we need 400B; For N=1000, we need near 4KB; For N=1m, we need
      near 4MB. For N = integer range(2^32), we will need near 16GB.
      Using 16GB just to hold this array is impartical
      Challanges:
      - Finding this big chunk of memory is tough.
      - Lots of slots will be empty.

   - If we are planning to store some K keys, in an array of size M rather than 2^32.
     We are doing this then M ∈ O(K) i.e. M should be in order of K. Like it should be just big enough to store K keys,
     not too big and not too small, just big enough to efficiently helps us to put keys we want. Its all about finding to sweet stop.
   - So length of the array(which is called bin) should be function of number of keys we are storing.
   - We don’t initially know how many keys we will need. So the language doesn’t fix the size of the bins upfront. As you keep adding keys, the hash table automatically adjusts the size of its internal array (bins/buckets). If more space is needed, the table is resized — in many implementations, the capacity is doubled (M → 2×M). When this happens, the hash table reallocates a larger array and reindexes all existing keys into the new bins. This can cause a brief pause, but resizing is done infrequently — only when the current capacity is exhausted — so the average insertion time remains near constant.

Because of the first step (hashing the application key), we simplify the problem: any key is converted into an integer, often in the range 0 to 2³². Now the hash table only needs to handle integers and map them into a smaller range efficiently. How it stores these integers, chooses the bucket range, and decides when and how to resize the table directly affects how efficient the hash table is.

The first step (hashing the application key) makes the second step type-agnostic. Once the key is converted to an integer (the hash value), the hash table doesn’t need to know or care whether the original key was a string, number, object, etc. The second step just takes that integer and maps it into the current table size range [0, m).





