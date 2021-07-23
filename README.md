# Advance-Dictionary


The implementation is backed by a 'trie', commonly referred to as a 'digital tree' or a 'prefix tree'. The word, meaning information is fetched from a text file via file handling.

Unlike a binary tree which simply has two child nodes, in this each node has a maximum of 26 child nodes which account for each letter in the alphabet (0-25 = a-z).

Each child node then has a string value assigned to it, which would be the description of the word if it has been added, and its own set of child nodes.

Using this method for traversal allows us to operate in an O(m) timeframe where m is the length of the word. This leads to linear performance given the length of the word to search for. This performance will be incredibly valuable for largely populated dictionaries as the amount of words within the dictionary will have no effect on the timeframe that it can be traversed in.

An example of the tries hierarchy is shown below:

![diagram](https://user-images.githubusercontent.com/68197328/126761523-d4784782-dd0b-43c4-9eea-2bdc9f3f01fa.png)


## Functons of project are:

• Insert, search and delete words in the dictionary.

• Printing the words in an alphabetical manner.

• Prefix searching i.e. all words with the entered prefix will be displayed.

• Nearest neighbor search i.e. shows suggested words if the word you are looking for is not found and we can also use it as a spell checker.
  


