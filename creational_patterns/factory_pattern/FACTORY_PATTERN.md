## **Factory pattern**

Also known as *Virtual Constructor*.

### **Intent**
Define an interface for creating an object, but let subclasses decide which class to instantiate. Factory Method lets a class defer instantiation to subclasses.

### **Applicability**
Use the Factory Method pattern when:
 - Object creation logic becomes too convoluted
 - Constructor is not descriptive:
    - Name mandated by name of containing type
    - Cannot overload with same sets of arguments with different names
    - Can turn into 'optional parameter hell'
 - Object creation (non-piecewise, unlike Builder) can be outsourced to:
    - A separate Function (Factory Method)
    - That may exist in a separate class (Factory)
    - Can Create hierarchy of factories with Abstract Factory

### **Description**
1. A component responsible solely for the wholesale (not piecewise) creation of objects.
In other words, it's a static method that creates objects.
2.  factory can take care of object creation.
3. A factory can be external or reside inside the object as an inner class.
4. Hierarchies of factories can be used to create related objects.

### **Related Patterns**
Abstract Factory is often implemented with factory methods.

Factory methods are usually called within Template Methods.

Prototypes don't require sub-classing Creator. However, they often require an Initialize operation on the Product class. Creator uses Initialize to initialize the object. Factory Method doesn't require such an operation.
