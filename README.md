# Geofuck
The cousin to brainfuck.

Just like brainfuck, you can make the code simple or unnecessary hard depending on how much you hate yourself.

## Grid/Map
Compared to good old brainfuck where you hade a horizontel layout consisting of 30k cells, we choice to up it by quite a bit.<br/>
This was done by expanding the layout to a fully scaled grid 30kx30k system.

![image](https://user-images.githubusercontent.com/14398606/206286369-d8ebd9b2-4d53-4fbf-a956-974060b3fbdd.png)

## Rule set

#### To move around in the matrix
```
* n - Moves one cell up
* e - Moves one cell to the right
* w - Moves one cell to the left
* s - Moves one cell down
```

#### Mathematical operators
```
* + - Increases the current cell's value by one
* - - Decreases the current cell's value by one
* * - Multiplies the current cell's value by two
* / - Divides the current cell's value by two
* ^ - Increases the current cell's value by the power of two
* % - Peforms a module two on the current cell's value
```

#### I/O
```
* . - Prints the value in the current cell, per default we will always try to print it in char form over integer
* , - Takes a char input from the user
```


#### Loops
```
* [ - Enter the while loop if the current cell's value isn't zero, else jump over the while statement
* ] - Exits the while loop if the current cell's value is zero, else jump to the start of the while statement
* { - Enters the while-do, does nothing special as we must execute the coming code atleast once
* } - Exits the while-do loop if the current cell's value is zero, else jump to the start of the while-do statement
``` 
All loops must start and end on the same line, meaning that we don't support multiline versions.<br/>
On top of that, we also dont support the same type of loops inside of each other.

#### Control flow
```
* ( - Enters the If-statement if the current cell's value isn't zero, else jumps over the if statement
* ) - Exits the If-statement if the current cell's value is zero, else jump to the start of the if-statement
```

## Code examples

#### Hello World!
The good old `Hello World!` in brainfuck
```
++++++++++[>+>+++>+++++++>++++++++++<<<<-]>>>++.>+.+++++++..+++.<<++.>+++++++++++++++.>.+++.------.--------.<<+.<.
```

And now how it *can* look in geofuck!
```
```

#### Simpel Art
