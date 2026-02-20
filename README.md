[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/E8F7BbGS)
# Tweakst

Welcome to **Tweakst**, a terminal-based board game implementation featuring automatic linking and win detection.

## Features

*   **Autolinking**: Automatically handles connections between game elements.
*   **Cross Detection**: Detects and handles crossing lines or invalid placements.
*   **Link Printing**: Visualizes the links on the board for better clarity.
*   **Win Detection**: Automatically checks the board state to declare a winner.

## Getting Started

### Compilation

To compile the project, navigate to the root directory and run:

```bash
make
```

To clean up build artifacts:

```bash
make clean
```

## Usage

Run the game executable:

```bash
./project
```

### Important Usage Notes

*   **Input Format**: You must type a **space** after every command you enter.
*   **Display**:
    *   If playing with **large board sizes**, please **decrease your terminal font size** to prevent text wrapping and visual glitches.
    *   This program uses ANSI escape characters and system commands (like `cls`). It works best in standard Linux terminals or modern Windows terminals. Some IDE terminals may not render the output correctly.

## Known Issues

*   None currently reported.
