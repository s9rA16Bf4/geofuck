# Geofuck
The cousin to brainfuck.

Just like brainfuck, you can make the code simple or unnecessary hard depending on how much you hate yourself.

## Grid/Map
Compared to good old brainfuck where you hade a horizontal layout consisting of 30k cells, we choice to up it by quite a bit.<br/>
This was done by expanding the layout to a fully scaled grid 30kx30k system.

![image](https://user-images.githubusercontent.com/14398606/206286738-512f678f-bcdf-471d-b074-64bd129cdf99.png)

## Features

#### Simpel code generation
The `-c` flag can be used to convert a provided string into a simple geofuck equivalent

<b>Note:</b> The code generated is in the simplest form possible, meaning that there are multiple ways to generate the same string and this is just one of them.
```
./gf -c "Hello, World!"

>> [~] +***+***.e+*+***+**+.e+*+**+*+**.e+*+**+*+**.e+*+**+*+*+*+.e+**+*+**.e+*****.e+**+**+*+*+.e+*+**+*+*+*+.e+*+*+***+*.e+*+**+*+**.e+*+***+**.e+*****+.
```

#### Interpretation
The interpreter supports interpretation from string inputs and through a file.
Take a look at the following examples for how they are used.
```
./gf -i "+***+***.e+*+***+**+.e+*+**+*+**.e+*+**+*+**.e+*+**+*+*+*+.e+**+*+**.e+*****.e+**+**+*+*+.e+*+**+*+*+*+.e+*+*+***+*.e+*+**+*+**.e+*+***+**.e+*****+.

>> Hello, World!
```

```
./gf -f examples/hello_world.gf

>> Hello, World!
```
#### Views
Two different kinds of views are currently supported.

##### Detailed view
Detailed view show cases essentially every cell in the grid, it's limited to only showing five cells at once before asking for a user input.
<b>Note:</b> The view is shown after execution of the provided script/string
```
./gf -f examples/hello_world.gf -dv
```

![image](https://user-images.githubusercontent.com/14398606/206399488-634d88b0-83e7-46e0-b993-af7ac965a7f4.png)

#### Step-by-step view
Step-by-step view shows what the current cell contains after each command.

```
./gf -f examples/hello_world.gf -sv
```

![image](https://user-images.githubusercontent.com/14398606/206398733-aef5fcad-bc6c-4b76-b88d-519d3a47803e.png)

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
* : - Prints the current cells value with a newline at the end
* ; - Takes a char input from the user and prints it with a newline at the end
```


#### Loops
```
* [ - Enter the while loop if the current cell's value isn't zero, else jump over the while statement
* ] - Exits the while loop if the current cell's value is zero, else jump to the start of the while statement
* { - Enters the do-while, does nothing special as we must execute the coming code atleast once
* } - Exits the do-while loop if the current cell's value is zero, else jump to the start of the do-while statement
``` 
All loops must start and end on the same line, meaning that we don't support multiline versions.<br/>
On top of that, we also dont support the same type of loops inside of each other.

#### Control flow
```
* ( - Enters the If-statement if the current cell's value isn't zero, else jumps over the if statement
* ) - Exits the If-statement.
```

#### Comments
Compared to brainfuck we can't allow "normal" text to be allowed within a script file, this as we utilizes some of the
most common characters for our navigation. <br/><br/>
Because of this all comments must start with a `§` character and can't appear on the same line as any code <br/>
In general it's best to utilize the first rows of each file to explain what the file in question peforms.<br/>

## Code examples

#### Hello World!
The good old `Hello World!` in brainfuck *can* look something like this
```
++++++++++[>+>+++>+++++++>++++++++++<<<<-]>>>++.>+.+++++++..+++.<<++.>+++++++++++++++.>.+++.------.--------.<<+.<.
```

And now how it *can* look in geofuck!
```
+++++++++e+++[-w*e]w.e+++e+++[w*e-]w+e++[w*e-]w+.e+++***+**e++**[w+e-]w.
e+++***+**e++**[w+e-]w.e+++***+**e++*+*[w+e-]w+.e++*+*+**.
e++*e++[w*e-]w*.e++*+**+*+*+.e+++***+**e++*+*[w+e-]w+.e+++***+**e++*+*[w+e-]w++++.
e+++***+**e++**[w+e-]w.e+++***+**.e++*e++[w*e-]w*+.
```

#### Simpel Art

You can to some extent create ascii art, this can be simply solved by using `./gf -c "<ascii art>"`<br/>
An example is shown below.

```
+*****.e+*****.e+*****.e+*****.e+*****.e+*****.e+*****.e+*****.e+*****.e+*****.e+*****.e+*****.e+*****.e+*****.e+*****.e+**+*+*+*+*+.e+**+*+*+*+*+:
e+*****.e+*****.e+*****.e+*****.e+*****.e+*****.e+*****.e+*****.e+*****.e+*****.e+*****.e+*****.e+*****.e+*****.e+**+*+*+*+.e+*****.e+**+*+*+*+*+.e+**+***+:
e+*****.e+*****.e+*****.e+*****.e+*****.e+**+*+*+*+*+.e+**+*+*+*.e+**+*+**+.e+**+*+**+.e+**+*+**+.e+**+*+**+.e+**+*+*+*.e+**+*+*+*+*+.e+**+*+*+*+.e+*****.e+**+*+*+*+:
e+*****.e+*****.e+*****.e+*****.e+**+*+*+*+.e+*****.e+*****.e+*****.e+*****.e+*****.e+*****.e+*****.e+*****.e+*****.e+**+*+*+*+:
e+*****.e+**+*+*+*+*+.e+**+*+*+*+*+.e+**+*+*+*+.e+*****.e+**+***.e+*****.e+*****.e+*+*+*+*+**.e+*****.e+**+***.e+*****.e+*****.e+*+*+*+*+**:
e+**+*+*+*+.e+**+*+*+*+*+.e+**+*+*+*+*+.e+**+*+*+*.e+**+*+**+.e+***+*+*+.e+*+*+*+*+**.e+**+*+*+*+*+.e+*+*+*+*+**.e+**+*+**+.e+**+*+**+.e+*+*+*+*+**.e+**+*+*+*+*+.e+*+*+*+*+**:
```

The result from the geofuck code above is
```
               __
              / _)
     _.----._/ /
    /         /
 __/ (  | (  |
/__.-'|_|--|_
```