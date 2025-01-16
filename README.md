# Tetris

## Project Overview

This project involves implementing the classic **Tetris** game, featuring both a console-based version and a graphical interface using Qt6. The goal is to learn best programming practices in C++20 while employing appropriate design patterns for each version.

The project is divided into three major milestones:

- Modeling the business logic.
- Implementing a console interface.
- Developing a graphical interface.

---

## Key Features

### Board

- **Dimensions**: By default, the board is 10 squares wide and 20 squares tall. These dimensions are configurable at launch.
- **Initial State**: Players can choose between an empty board or one partially filled randomly.

### Blocks

- **Types of Blocks**: 7 standard shapes (I, O, T, J, L, S, Z).

### Gameplay Mechanics

- **Movements** (common to both versions):
  - Move the current block left, right, or down. ( Q / D / S )
  - Rotate the block clockwise or counterclockwise. ( A / E )
  - "Drop": The block descends directly to its final position. ( F )
- **Score**:
  - Based on completed lines and the cells traversed during a "drop."
  - Points are multiplied based on the current level.
- **Speed and Levels**:
  - In the GUI version: Blocks automatically move down one square every second using a thread started at the game’s launch. Speed increases with each level.
  - In the console version: There is no real-time automatic movement; the game is turn-based.

### Endgame Conditions (common to both versions)

- **Victory**:
  - Achieving a target score.
  - Completing a predefined number of lines.
  - Playing for a specific time limit.
- **Defeat**: The board is full, and no new blocks can be generated.

---

## Software Structure and Development Phases

### Phase 1: Business Logic Modeling

- **Objective**: Design the business logic classes using diagrams and/or documented headers.
- **Required Design Patterns**:
  - Observer/Observable for interactions in the GUI version.
  - MVC (Model-View-Controller) for the console version.

### Phase 2: Console Implementation

- **Objective**: Develop a playable version of the game in a terminal.
- **Specific Characteristics**:
  - Turn-based mode without real-time simulation.
  - Exclusive use of the standard library.

### Phase 3: Graphical Interface Implementation

- **Objective**: Add a graphical interface using Qt6.
- **Guidelines**:
  - Use the QGraphicsView module to manage the display.
  - The block automatically moves down one square every second, with speed increasing per level.

---

## GUI-Specific Features

### Main Menu

- **Configurable Parameters at Launch**:
  - Board height and width.
  - Empty or pre-filled board (random).
  - Initial level.
- Once "Play" is selected, the game window appears.

### Game Window

- **Visible Elements**:
  - The main grid.
  - On the left: The next block to appear.
  - At the top: A dropdown menu with the following options:
    - Quit.
    - Start a new game.
- **End Screen**:
  - If the player loses, a pop-up window appears with two choices:
    - Start a new game.
    - Quit.

---

## Compilation and Execution

### Prerequisites

- **Compiler**: GCC/Clang (console) or Qt Creator (GUI).
- **Libraries**:
  - Standard C++20 (console).
  - Qt6 for the graphical interface.
- The working directory:
  - `GUI` is located at `\build-TETRIS-Desktop_Qt_6_6_1_MinGW_64_bit-Debug\gui`
  - `Console` is located at `\build-TETRIS-Desktop_Qt_6_6_1_MinGW_64_bit-Debug\Console`
