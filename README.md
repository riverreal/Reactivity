# Reactivity

Reactivity is a simple reactive library in *C++11*. It provides a simple interface which makes it easier to create callbacks (reactions) with filter operations, greatly resembling [Reactive eXtensions](http://reactivex.io/) (Rx) but without asynchronous and streaming functionality.

### Features

  - Filter-able subscription of actions
  - Header-only library
  - Cross platform simple API
  
***It is in development and there are many missing features**

### Usage
#### Reactive Variable
After adding the library into the additional include directories.
This example creates a reactive variable of type int which prints it's content every time the value is changed.
The reactive variable can be treated like a regular variable, in this case 'int'.
```cpp
#include <iostream>
#include <Reactivity/Reactivity.h>
...
//Create a reactive variable of type int and initialize it with 0
Reactivity::ReactiveVariable<int> printableInt(0);

//Add a reaction (callback) to the reactive variable
printableInt.React([](auto& value){
    std::cout << value << "\n";
});

//Change values
printableInt = 1;
printableInt += 9;
printableInt *= 10;

//Assing to a normal int
int tmp = printableInt;
std::cout << tmp << "\n";
```
Output:
```
1
10
100
100
```
Notice the variable initialization `printableInt(0)` is not being printed.
#### Filter Operations
You can filter the callback to control it's behaviour. Using the previous example instead of printing every time the value is changed, it can be filtered sequentially and only print in the desired cases.
```cpp
printableInt
    .While([](auto& value){
        return value == 10;
    })
    .Until(3)
    .React([](auto& value){
        std::cout << value << "\n";
});

printableInt = 1;
for(int i = 0; i < 5; ++i)
{
    printableInt = 10;
}
```
Output:
```
10
10
10
```
This time the reaction is filtered by `While` and `Until` sequentially. 
`While` takes a bool returning lambda to filter out the cases it returns false. In this example every variable that is **not** 10 will be discarded.
`Until` takes an integer which represents the number of times the filter should pass. In this example the filter will pass only `3` times.
Notice how `Until` ignores the values already filtered by `While`, making the filters sequential.

## License
----

MIT License
