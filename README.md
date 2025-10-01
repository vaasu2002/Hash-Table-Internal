# Hash Tables Internals:

Hashtables are used as building blocks of language runtimes.
For example, when we define a class with members and functions and call something like box.put(), the language runtime needs to figure out:
- which object box refers to,
- which method put is being invoked,
- and then execute that function for the object.
In many languages, classes themselves are implemented using hashtables.

Similarly, when we declare a variable like int a = 10; and later use a, the runtime needs to know where a is stored — this is called variable lookup.

So, hashtables are not just used in business applications but also play a crucial role in the internal workings of programming languages themselves.
