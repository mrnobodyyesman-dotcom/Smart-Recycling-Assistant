# Smart Recycling Assistant

A simple C console program that suggests the correct recycling category for an object we describe.

The program reads a list of waste categories and their associated keywords from `categories.txt`, asks the user to type a short description of an object, counts how many keywords from each category appear in that description, and prints the category with the highest match. The query and the suggested category are appended to `log.txt`.

---

## What it does

1. Loads categories and keywords from `categories.txt` (one line per category, format: `Name: word1, word2, word3`).
2. Asks the user to describe an object.
3. Scores every category by counting how many of its keywords appear inside the user's text.
4. Prints the best-matching category and its score.
5. Appends a line to `log.txt` with the input and the chosen category.

---

## Project files

| File | Purpose |
|---|---|
| `smart_recycling_assistant.c` | The C source code (this is the only file you compile) |
| `categories.txt` | The knowledge base — categories and their keywords |

---

## How to build

You need a C compiler. On Windows, open `cmd`, go to the project folder, and run:

```cmd
- go to the file directory using 'cd' command
- then run -> gcc "smart_recycling_assistant.c" -o smart_recycling_assistant
```

note that gcc must be installed and added to the PATH

---

## How to run

From the same `cmd` window, run:

```cmd
smart_recycling_assistant.exe
```

The program will prompt you:

```
Loaded 9 categories.
Describe an object:
```

Type a description of the object (for example `banana peel`) and press **Enter**. The program will print the score for each category, suggest the best one, and exit. Run the program again any time you want to classify another object.

---
