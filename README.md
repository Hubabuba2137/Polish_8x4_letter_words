I'm trying to solve a similar problem as Stand-up Maths did in this video: Stand-up Maths video.

To run the program, first, unpack the wordlist called "slowa.zip." Then, open list_creation.cpp and choose the desired word length. 
To do something similar to what was done in the video, you should select either 4 or 8. The reason for this will be explained later.
After the word list is created, run main_algorithm.cpp (make sure the filenames are correct). That’s all!

The Polish alphabet has 32 letters (technically 35, but the letters "x," "q," and "v" are only used in foreign words).
If you want to create words with unique letters of the same length, you can either have 4 words that are 8 letters long or 8 words that are 4 letters long.
It is useful to represent each letter with a specific bit in a 32-bit unsigned integer. By doing a bitwise OR operation between two integer values and then calculating the Hamming weight,
we can check how many letters are the same. If the Hamming weight equals the number of letters times the number of words, then every character is unique. That’s the main idea.

If my algorithm is correct (though I’m bad at coding), then it should be impossible to have four or eight words with entirely unique characters, which I find interesting.
