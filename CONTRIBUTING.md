# Contributing to Othello (Terminal Game)

This started as a university course project (Fundamentals of Programming) and I'm not actively adding new features myself. That said, it's open source, so if you'd like to fork it, fix something, or build on it — contributions are still welcome! 🎉

## How to Contribute

1. Fork the repository
2. Create a branch for your change:
   ```bash
   git checkout -b feature/your-feature-name
   ```
3. Make your changes
4. Confirm the project still compiles cleanly:
   ```bash
   gcc othello-v1.c -o othello -Wall -Wextra
   ```
5. Commit with a clear, descriptive message
6. Push to your fork and open a Pull Request describing what changed and why

## Ideas If You Want to Fork or Extend It

- Single-player mode with a simple AI opponent (even a greedy heuristic is a great start)
- Save / load game state to a file
- Undo last move
- Better cross-platform color support (plain Windows CMD without ANSI enabled)
- Splitting the single file into modules (`board.c`/`.h`, `game.c`/`.h`, `ui.c`/`.h`)
- Basic automated tests for `isValidMove()` / `flipDiscs()`
- Replacing `scanf`-based input with more robust parsing

## Code Style

- Match the existing style: camelCase function/variable names, short focused functions, comments above non-obvious logic
- Keep the terminal UI consistent with the existing box-drawing / color scheme
- Test manually (start a game, make a few moves, trigger a pass, finish a game) before submitting

## Reporting Bugs

Please open an issue including:
- Steps to reproduce
- Expected vs. actual behavior
- Your OS and terminal (this matters a lot for ANSI color rendering issues)
