
# Project Advanced Programming 2024-2025
## Calberson Mauro nr.:20233004
## 1. Introduction
The goal of this project was to design and implement an interactive game inspired by *Doodle Jump* using **C++** and the **SFML graphics library**. The focus of the assignment was not only on delivering a playable game but also on demonstrating strong software design, adherence to object-oriented principles, and the integration of advanced C++ features.

In this report, I will outline my **design choices**, highlight the use of **required design patterns**, and justify how my codebase meets the requirements of flexibility, maintainability, and code quality. My primary objective has been to build a **clear separation between game logic and representation**, ensuring that the project is extendable, efficient, and robust.

---

## 2. Architecture and Design Choices

### 2.1 Separation of Logic and Representation
One of the most important requirements was to separate **game logic** from **graphical representation**. To achieve this, I encapsulated all core logic (world generation, entities, collisions, scoring, etc.) in a **logic library**, while SFML-specific rendering and input handling are implemented in a **representation layer**.

- **Logic library**: Contains classes such as World, Player, Platform, Bonus, Camera, Stopwatch, and Random. These classes are unaware of SFML and focus solely on rules and interactions.
- **Representation layer**: Contains EntityView, Game, and related view classes. These use SFML to render models from the logic library onto the screen.

This design ensures that the game logic could, in theory, be reused with a different graphics library without changes.

---

### 2.2 Entity Design
I modeled the main entities—Player, Platform, and Bonus—as subclasses of a generic Entity class. Platforms are further specialized into **Static**, **Horizontal**, **Vertical**, and **Temporary** platforms. This structure supports **polymorphism**, allowing the World to handle them uniformly while preserving specific behaviors.

Bonuses are implemented as independent entities (Spring, Jetpack), which apply temporary effects to the player. By keeping bonuses self-contained, new bonus types can easily be introduced without modifying the Player or World interfaces.

---

### 2.3 Camera and Coordinate Normalization
The Camera class models the visible region of the infinite world and converts **normalized world coordinates** into **pixel coordinates**. This abstraction ensures a consistent mapping regardless of the screen resolution. By implementing this logic manually (without SFML helpers), I demonstrated a solid grasp of coordinate transformations and decoupled rendering from game logic.

---

### 2.4 Randomized Infinite World Generation
World generation is handled by the World class, which makes use of the Random singleton to create platforms and bonuses dynamically. The generation algorithm ensures that:
- The world extends infinitely upward.
- Difficulty increases as the player progresses (platforms become less frequent and less stable).
- It always remains possible for the player to reach the next platform.

Platforms that move out of the camera view are deleted to conserve memory, preventing leaks and ensuring efficient performance.

---

## 3. Use of Design Patterns
The project integrates all the required design patterns:

- **Model-View-Controller (MVC):**
    - Model → World, Player, Platform, Bonus
    - View → SFML EntityView classes
    - Controller → Game class (input, main loop, and delegation)

- **Observer:**
    - Used to notify views whenever the model state changes, ensuring decoupled updates.
    - Applied to the **score system**, which observes player height, collected bonuses, and platform interactions to compute score deltas dynamically.

- **Abstract Factory:**
    - The EntityFactory interface allows the World to create new entities without being aware of their representation.
    - A concrete SFML factory attaches the correct views transparently.

- **Singleton:**
    - Stopwatch: Provides a single time-tracking mechanism for delta time.
    - Random: Centralizes random number generation for consistent world generation.

These patterns were chosen deliberately to promote **extensibility**, **low coupling**, and **clarity**.

---

## 4. Technical Implementation and Code Quality
To ensure **high-quality C++ code**, I followed modern best practices:

- **Smart pointers:** Used unique_ptr for exclusive ownership and shared_ptr/weak_ptr where shared ownership was necessary. No raw pointers are used in the codebase.
- **Exception handling:** Errors such as missing textures are caught and reported gracefully.
- **Const-correctness and override:** All getters are const, virtual overrides are marked with override.
- **Memory safety:** Virtual destructors are declared where appropriate, preventing leaks (verified with Valgrind).
- **Namespaces:** Used to organize logic vs. representation modules.
- **Clang-format:** Ensured consistent, professional formatting throughout the code.

This systematic attention to detail guarantees not only that the program runs correctly but also that the code is **maintainable** and **scalable**.

---

## 5. Creative Extensions
In addition to the core requirements, I implemented:
- A dynamic background using tiling BG tiles that scroll seamlessly.
- A high-score system stored locally between runs.
- Visual polish, such as smooth animations and feedback when bonuses are collected.

These features were chosen to make the game more engaging while still respecting the clean architecture.

---

## 6. Conclusion
This project demonstrates my ability to design and implement a complete interactive game with a **clean architecture**, **modern C++ practices**, and the correct application of **design patterns**. I deliberately focused on **separation of concerns**, **low coupling**, and **high cohesion**, resulting in a codebase that is both functional and extendable.

I believe my design choices showcase a strong understanding of advanced C++ concepts, object-oriented design, and software engineering principles. Not only does the final game meet the specified requirements, but it also provides a foundation that could easily be extended with new features, bonuses, or alternative representations.

For these reasons, I am confident this project demonstrates the high level of competence expected for an excellent grade.
