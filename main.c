/**
 * File Word Counter
 * A C program that counts words, characters, and lines in text files
 * Uses basic data structures to track word frequencies
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_FILENAME 100
#define MAX_WORD_LENGTH 50
#define MAX_UNIQUE_WORDS 1000

// Structure to store word frequency
typedef struct {
    char word[MAX_WORD_LENGTH];
    int count;
} WordFrequency;

// Function prototypes
void countStats(FILE *file, int *charCount, int *wordCount, int *lineCount);
void countWordFrequencies(FILE *file, WordFrequency *wordFreqs, int *uniqueWordCount);
void sortWordFrequencies(WordFrequency *wordFreqs, int uniqueWordCount);
void printResults(int charCount, int wordCount, int lineCount, WordFrequency *wordFreqs, int uniqueWordCount, int topN);
int findWord(WordFrequency *wordFreqs, int count, char *targetWord);
void toLowercase(char *word);
void removeNonAlphanumeric(char *word);

int main() {
    char filename[MAX_FILENAME];
    FILE *file;
    int charCount = 0, wordCount = 0, lineCount = 0;
    WordFrequency wordFreqs[MAX_UNIQUE_WORDS];
    int uniqueWordCount = 0;
    int topN = 10; // Number of top frequent words to display
    
    printf("=== File Word Counter ===\n\n");
    
    // Get filename from user
    printf("Enter the filename to analyze: ");
    scanf("%s", filename);
    
    // Open the file
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file '%s'.\n", filename);
        return 1;
    }
    
    // Count basic statistics (chars, words, lines)
    countStats(file, &charCount, &wordCount, &lineCount);
    
    // Rewind file to start from beginning
    rewind(file);
    
    // Count word frequencies
    countWordFrequencies(file, wordFreqs, &uniqueWordCount);
    
    // Sort words by frequency (descending)
    sortWordFrequencies(wordFreqs, uniqueWordCount);
    
    // Print the results
    printResults(charCount, wordCount, lineCount, wordFreqs, uniqueWordCount, topN);
    
    // Close the file
    fclose(file);
    
    return 0;
}

// Count characters, words, and lines in the file
void countStats(FILE *file, int *charCount, int *wordCount, int *lineCount) {
    int c;
    int inWord = 0; // Flag to track if we're inside a word
    
    *charCount = 0;
    *wordCount = 0;
    *lineCount = 0;
    
    while ((c = fgetc(file)) != EOF) {
        (*charCount)++;
        
        // Count lines
        if (c == '\n') {
            (*lineCount)++;
        }
        
        // Count words
        if (isspace(c)) {
            inWord = 0;
        } else if (inWord == 0) {
            inWord = 1;
            (*wordCount)++;
        }
    }
    
    // If the file doesn't end with a newline, increment line count
    if (*charCount > 0 && c != '\n') {
        (*lineCount)++;
    }
}

// Count frequency of each unique word
void countWordFrequencies(FILE *file, WordFrequency *wordFreqs, int *uniqueWordCount) {
    char word[MAX_WORD_LENGTH];
    int index;
    
    *uniqueWordCount = 0;
    
    // Read words from file
    while (fscanf(file, "%s", word) == 1) {
        // Convert to lowercase and remove punctuation
        toLowercase(word);
        removeNonAlphanumeric(word);
        
        // Skip empty strings or strings with only punctuation
        if (strlen(word) == 0) {
            continue;
        }
        
        // Check if word already exists in our array
        index = findWord(wordFreqs, *uniqueWordCount, word);
        
        if (index != -1) {
            // Increment count of existing word
            wordFreqs[index].count++;
        } else if (*uniqueWordCount < MAX_UNIQUE_WORDS) {
            // Add new word
            strcpy(wordFreqs[*uniqueWordCount].word, word);
            wordFreqs[*uniqueWordCount].count = 1;
            (*uniqueWordCount)++;
        } else {
            printf("Warning: Reached maximum unique word limit. Some words may not be counted.\n");
        }
    }
}

// Find a word in the word frequency array
int findWord(WordFrequency *wordFreqs, int count, char *targetWord) {
    for (int i = 0; i < count; i++) {
        if (strcmp(wordFreqs[i].word, targetWord) == 0) {
            return i;
        }
    }
    return -1; // Word not found
}

// Convert a string to lowercase
void toLowercase(char *word) {
    for (int i = 0; word[i]; i++) {
        word[i] = tolower(word[i]);
    }
}

// Remove non-alphanumeric characters from a string
void removeNonAlphanumeric(char *word) {
    int i, j = 0;
    
    for (i = 0; word[i]; i++) {
        if (isalnum(word[i])) {
            word[j++] = word[i];
        }
    }
    word[j] = '\0';
}

// Sort word frequencies in descending order
void sortWordFrequencies(WordFrequency *wordFreqs, int uniqueWordCount) {
    WordFrequency temp;
    
    // Simple bubble sort
    for (int i = 0; i < uniqueWordCount - 1; i++) {
        for (int j = 0; j < uniqueWordCount - i - 1; j++) {
            if (wordFreqs[j].count < wordFreqs[j + 1].count) {
                // Swap
                temp = wordFreqs[j];
                wordFreqs[j] = wordFreqs[j + 1];
                wordFreqs[j + 1] = temp;
            }
        }
    }
}

// Print analysis results
void printResults(int charCount, int wordCount, int lineCount, WordFrequency *wordFreqs, int uniqueWordCount, int topN) {
    printf("\n=== File Analysis Results ===\n");
    printf("Characters: %d\n", charCount);
    printf("Words: %d\n", wordCount);
    printf("Lines: %d\n", lineCount);
    printf("Unique words: %d\n", uniqueWordCount);
    
    // Print top N most frequent words
    printf("\nTop %d most frequent words:\n", topN);
    printf("%-20s %s\n", "WORD", "FREQUENCY");
    printf("-------------------------\n");
    
    int numToPrint = uniqueWordCount < topN ? uniqueWordCount : topN;
    
    for (int i = 0; i < numToPrint; i++) {
        printf("%-20s %d\n", wordFreqs[i].word, wordFreqs[i].count);
    }
    
    // Calculate and print word frequency statistics
    float avgOccurrence = 0;
    if (uniqueWordCount > 0) {
        avgOccurrence = (float)wordCount / uniqueWordCount;
    }
    
    printf("\nWord Statistics:\n");
    printf("Average word occurrence: %.2f\n", avgOccurrence);
    
    // Print frequency distribution
    printf("\nFrequency Distribution:\n");
    int freq1 = 0, freq2to5 = 0, freq6to10 = 0, freqMore = 0;
    
    for (int i = 0; i < uniqueWordCount; i++) {
        if (wordFreqs[i].count == 1) freq1++;
        else if (wordFreqs[i].count >= 2 && wordFreqs[i].count <= 5) freq2to5++;
        else if (wordFreqs[i].count >= 6 && wordFreqs[i].count <= 10) freq6to10++;
        else freqMore++;
    }
    
    printf("Words appearing once: %d (%.1f%%)\n", freq1, freq1 * 100.0 / uniqueWordCount);
    printf("Words appearing 2-5 times: %d (%.1f%%)\n", freq2to5, freq2to5 * 100.0 / uniqueWordCount);
    printf("Words appearing 6-10 times: %d (%.1f%%)\n", freq6to10, freq6to10 * 100.0 / uniqueWordCount);
    printf("Words appearing more than 10 times: %d (%.1f%%)\n", freqMore, freqMore * 100.0 / uniqueWordCount);
}
