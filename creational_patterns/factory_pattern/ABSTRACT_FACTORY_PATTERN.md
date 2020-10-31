# **Factory pattern**

Also known as *Kit*.

## **Intent**

Provide an interface for creating families of related or dependent objects without specifying their concrete classes.

## **Applicability**

Use the Abstract Factory pattern when:

- a system should be independent of how its products are created, composed and represented.
- a system should be configured with one of multiple families of products.
- a family of related product objects is designed to be used together, and you need to enforce this constraint.
- you want to provide a class library of products, and you want to reveal just their interfaces, not their implementations.

## **Description**

Family of factories which use polymorphism to allow you to call the different factories.

## **Related Patterns**

AbstractFactory classes are often implemented with factory methods (Factory Method), but they can also be implemented using Prototype.

A concrete factory is often a Singleton.
