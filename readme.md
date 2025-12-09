# Design Patterns in Modern C++

This repository contains implementations and examples of **classic design patterns** in C++ (C++11/14/17).  
It is intended as a **learning resource** and reference for developers who want to understand and apply design principles in real-world projects.

---

## Getting Started

### Prerequisites
You need a **C++ compiler** that supports modern standards (C++17 recommended).  
We’ll use **GNU g++** for both Linux and Windows.

---

### Install g++ on Linux
Most Linux distributions include g++ in their package manager:

```bash
# Ubuntu/Debian
sudo apt update
sudo apt install build-essential

# Fedora
sudo dnf install gcc-c++

# Arch Linux
sudo pacman -S gcc

# Verify installation:
g++ --version

```

### Install g++ on Windows (MSYS2 MINGW64)
1. 	Download and install [MSYS2](https://www.msys2.org/).
2. 	Open the MSYS2 MINGW64 terminal.
3. 	Update packages:

```bash
pacman -Syu

# Install g++
pacman -S mingw-w64-x86_64-gcc

# - Verify installation:
g++ --version
```

## Repository Content

Each design pattern is implemented in incremental examples with clear documentation and comments.
Patterns are organized into categories:
### Creational Patterns
* Builder – Step-by-step construction of complex objects.
* Factory Method – Delegates instantiation to subclasses.
*	Abstract Factory – Creates families of related objects.
*	Prototype – Clones existing objects.
*	Singleton – Ensures a single instance globally.
### Structural Patterns
* 	Adapter – Converts one interface into another.
* 	Bridge – Decouples abstraction from implementation.
* 	Façade – Simplifies complex subsystems with a unified interface.
* 	Proxy – Provides a placeholder to control access. Can change the behavior of the object while keeping the same interface.
* 	Decorator – Dynamically adds responsibilities to objects.
* 	Flyweight – Shares common state efficiently across many objects.

### Behavioral Patterns
*   Chain of responsability - Sequence of handlers processing an event one after another.
* 	Observer – Notifies multiple objects of state changes.
* 	Strategy – Encapsulates interchangeable algorithms.
* 	Command – Encapsulates requests as objects.
* 	State – Allows objects to change behavior based on internal state.
*   Interpreter -  Allows process of sequences in two stages: lexing and parsing.
* 	Iterator – Provides sequential access to collections.
*   Mediator - Facilitates communication between different components.
*   Memento - Used to store and revert the state of the system to a specific point in time. 
    Can provide Undo and Redo functionality to the system. 
### Principles
* 	SOLID Principles – Examples demonstrating Single Responsibility, Open/Closed, Liskov Substitution, Interface Segregation, and Dependency Inversion.

### Compilation & Execution

```bash
g++ -std=c++17 pattern_example.cpp -o pattern_example
./pattern_example
```
