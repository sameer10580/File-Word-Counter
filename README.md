# File Word Counter

A C implementation of a text file analysis tool for a Data Structures and Algorithms course project. This program demonstrates practical applications of fundamental data structures and algorithms concepts by analyzing and presenting statistics about text files.

## Features

- **Basic Text Statistics**
  - Character count
  - Word count
  - Line count
  - Unique word count

- **Word Frequency Analysis**
  - Identifies and counts each unique word
  - Displays the most frequently used words
  - Calculates word frequency distribution

- **Text Processing**
  - Case normalization (converts all text to lowercase)
  - Punctuation and special character handling
  - Consistent word tokenization

## Data Structures Used

- Arrays to store word data
- Custom structures (`WordFrequency`) to pair words with their counts
- String manipulation for text processing

## Algorithms Implemented

- Linear search for word matching
- Bubble sort for ranking words by frequency
- Frequency distribution calculation
- Word tokenization and normalization

## How to Compile and Run

```bash
# Compile the program
gcc word_counter.c -o word_counter

# Run the program
./word_counter
```

Upon running, the program will prompt you for a filename to analyze.

## Sample Output

```
=== File Analysis Results ===
Characters: 2584
Words: 517
Lines: 45
Unique words: 243

Top 10 most frequent words:
WORD                 FREQUENCY
-------------------------
the                  34
and                  23
of                   21
to                   18
a                    17
in                   12
is                   9
for                  8
that                 7
are                  6

Word Statistics:
Average word occurrence: 2.13

Frequency Distribution:
Words appearing once: 153 (63.0%)
Words appearing 2-5 times: 79 (32.5%)
Words appearing 6-10 times: 6 (2.5%)
Words appearing more than 10 times: 5 (2.1%)
```

## Project Structure

- `word_counter.c` - Main source code file containing all functionality

## Potential Enhancements

Future improvements that could be made to extend the project:
- Implement a hash table for more efficient word lookup
- Add support for analyzing multiple files at once
- Create more efficient sorting algorithms
- Add visualization features for word frequency data
- Support for exporting results to different formats (CSV, JSON)
- Add more advanced text analysis (sentence length, reading level, etc.)

## Course Information

- **Course**: Data Structures and Algorithms
- **Institution**: UIC, Chandigarh University
- **Semester**: 2nd Semester
- **Student**: Sameer Bhagwana
- **UID**: 24BCA10580
