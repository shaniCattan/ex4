# ex4
github line - https://github.com/shaniCattan/ex4/tree/dev

# Searching Algorithms Server
In this program we created a generic server, that may be used in several projects.

The server recieves a problem from the client, and returns the solution to the client.

The program is written in a generically, hence it is able to recieve and solve various problems.

## our problem - seeking for the shortest path in a matrix
In the program, the program finds the shortest path in a inputed matrix, and return the path with the cost of the vertices in the shortest path.

To solve this problem, we have used the following 4 algorethms:


### ALGORITHMS

* **Best first search** - a search algorithm which explores a graph by expanding the most promising node chosen according to a specified rule. 
[read more](https://en.wikipedia.org/wiki/Best-first_search) 

* **Breadth-first search** - an algorithm for traversing or searching tree or graph data structures. It starts at the tree root, and explores all of the neighbor vertices at the present depth prior to moving on to the vertices at the next depth level. [read more](https://en.wikipedia.org/wiki/Breadth-first_search)

* **Depth-first search** -  an algorithm for traversing or searching tree or graph data structures. The algorithm starts at the root node  and explores as far as possible along each branch before backtracking. [read more](https://en.wikipedia.org/wiki/Depth-first_search)

* **A-star** - an informed search algorithm, starting from a specific starting vertex of a graph, it aims to find a path to the given goal vertex having the smallest cost . It does this by maintaining a tree of paths originating at the start node and extending those paths one edge at a time until its termination criterion is satisfied. [read more](https://en.wikipedia.org/wiki/A*_search_algorithm)

we executed an experiment and choose the most effective algorithm.

### Design Patterns in C++

In the following program we used some design patterns, for exemple:

* Single responsibility principle - A class should only have one responsibility.

* Open/closed principle - The systems we built should be open for extension, but closed for modification. 

* bridge - A mechanism that decouples an interface (interface hierarchy) from an implementation (implementation hierarchy).

* etc.

### Test the program

You can test the program by runnig the following command:

```
python3 auto_client.py -vv
```
it runs [python code](https://github.com/adi-cohen/part2/blob/master/auto_client.py) that will be the client.
the client sends [this](https://github.com/adi-cohen/part2/blob/master/matrix_test_in.txt) matrix for the server.

 *Note that* - first run the program and then the and after that the python code, this way the server will listen and wait for the client.

## Authors

Shani Cattan,
Mevaseret David

Bar Ilan university
