## **Builder pattern**
When piecewise object construction is complicated, provide and API for doing it uccinctly.

Some objects are simple and can be created in a single constructor call. Other objects require a lot of ceremony to create. Havin an object with (e.g.) 10 constructor arguments is not productive. Instead, opt for piecewise construction.

The Builder pattern provides an API for constructing an object step-by-step.
