

## Recursion / Introduction

### countdown()

Take a look at this pseudocode. Don't worry if you don't understand it yet!

```c++
countdown(int n) {
  if (n > 0) {
    print(n)
    countdown(n - 1) // recursion!
  }
}

countdown(1) // prints "1"
countdown(2) // prints "2 1"
countdown(3) // prints "3 2 1"

countdown(0) // does nothing
```

This function might look strange. Let's look at what exactly happens when `countdown(3)` is called:
1) `countdown(3)` prints `3`, then calls `countdown(2)`
2) `countdown(2)` prints `2`, then calls `countdown(1)`
3) `countdown(1)` prints `1`, then calls `countdown(0)`
4) `countdown(0)` just terminates, thanks to the if statement

Taken as a whole, `countdown(3)` prints `3 2 1`. This diagram may be easier to understand:

```c++
countdown(3) {
  print(3)
  countdown(2) {
    print(2)
    countdown (1) {
      print(1)
      countdown(0) // does nothing
    }
  }
}
```

### countup()
Now let's make everything way more complicated with one small change:

```c++
countup(int n) {
  if (n > 0) {
    countup(n - 1) // recursion!
    print(n)
  }
}

countup(1) // prints "1"
countup(2) // prints "1 2"
countup(3) // prints "1 2 3"

countup(0) // still does nothing
```

If we move the print after the recursive call, we print the numbers in increasing order, rather than decreasing. There are two things things to understand here that may not be obvious.

First, when we call a function, we wait for that function to completely terminate before doing anything else. `countup(2)` waits for `countup(1)` to terminate before it prints `2`. That's why `1` is printed before `2`.

Second, when we call a function, it is given a copy of the parameters that are passed into it. In `countup(1)`, n is 1, so it prints `1`. However, that does not affect the value of n in `countup(2)`, so it still prints `2` there. The same logic holds for `countup(3)`, which prints `3`. You can think of every recursive call as its own little world, with its own value of n. When we come back to that world, it's exactly how we left it.

Here's what happens when we call `countup(3)`:

```c++
countup(3) { // n = 3
  countup(2) { // n = 2
    countup(1) { // n = 1
      countup(0) // does nothing
      print(1)
    }
    print(2) // n is still 2 out here
  }
  print(3) // n is still 3 out here
}
// we've printed "1 2 3"
```

Don't worry if this doesn't make perfect sense yet.

### Defining Recursion

Every recursive function has two cases:

1) A recursive case, in which it calls itself
2) A base case, in which it doesn't call itself

Without the recursive case, well, it wouldn't be recursive. Without the base case, it would always call itself, so it would never terminate. 

Also, ==every recursive call must bring us closer to the base case==. We must be working toward terminating; otherwise the function will fail or run forever.

In the previous examples, the recursive case is `n > 0`, and the base case is `n <= 0`. Every call decreases n by 1, bringing us closer to our base case.

Recursive functions can be divided into two groups:
- A *linear* recursive function calls itself only a single time (or zero times, in the base case). These functions can often be easily written non-recursively, such as with a for loop. The examples we've covered so far are linear.
- An *exponential* recursive function calls itself more than once at each recursive step. A *binary* recursive function calls itself twice. Quicksort and merge sort use binary recursion (don't worry if you're not familiar with them).

### factorial()

Recursion can be useful to solve a given problem if we can express the solution to that problem in terms of the answer to one or more *easier subproblems*. That's a mess of a sentence, so here's an example.

Imagine you want to make a function that, given `n`, calculates `n!` (AKA n factorial). If you don't know what a factorial is, (I'll add a link here).

We can get from one factorial to the next by simply multiplying by `n`. In more formal terms, `n! = n * (n-1)!`. Calculating `(n-1)!` is an *easier subproblem*, and we can use it to build a recursive function.

```c++
int factorial(int n) {
  if (n <= 1)
    return 1; // base case
  else
    return n * factorial(n - 1); // look familiar?
}
factorial(1) // returns 1
factorial(2) // returns 2   (2 * factorial(1))
factorial(3) // returns 6   (3 * factorial(2))
factorial(4) // returns 24  (4 * factorial(3))
```

### even_count()

Here's one last intimidating example, in which we use recursion to iterate over a vector:

```c++

// this is the helper function
int even_count(vector<int> v, int i) {
  
  if (i < 0) // base case - we've gone through the whole vector
    return 0; // why 0?
  
  if (v[i] % 2 == 0)
    return 1 + even_count(v, i - 1); // even, count it and move on
  else
    return even_count(v, i - 1); // odd, just move on
  
}

int even_count(vector<int> v) {
  return even_count(v, v.size() - 1); // just call the helper function
}

even_count({ 1, 2, 3, 4, 5, 6, 7 }) // returns 3
```

The first function here is a *helper function*. We're using recursion to iterate backwards over this vector, so we want `i` to start at `v.size() - 1` (and count down to 0). The function we're actually calling doesn't do anything except call the helper function, but it conveniently initializes `i` to the right value.

So how does this function actually work? Consider the input `v = { 2, 3, 4, 6, 5 }`.

`even_count(v, i)` is the number of even numbers in `v` at index `i` or earlier.
`even_count(v,-1) = 0`: Base case. No elements appear at or before index -1
`even_count(v, 0) = 1`: 2, the first element of `v`, is even
`even_count(v, 1) = 1`: 3 isn't even, but there's 1 even number before it
`even_count(v, 2) = 2`: 4 is even, and there's 1 even number before it
`even_count(v, 3) = 3`: 6 is even, and there are 2 even numbers before it
`even_count(v, 4) = 3`: 5 is odd, but there are 3 even numbers before it
Here we're looking at the `even_count` of the first 5 elements of a 5-element vector. Therefore, `even_count(v, 4)` is the `even_count` of `v`.

We look at the current element `v[i]`, and the number of evens that come before it, to get `even_count(v, i)`.
- When `v[i]` is odd, `even_count(v, i) = even_count(v, i - 1)`. We ignore the odd number, and simply return the number of evens that come before it.
- When `v[i]` is even, `even_count(v, i) = 1 + even_count(v, i - 1)`. We increase the returned count by 1 to account for the even number at index `i`.

<!--
As a final note, you can make this 
If you want to make this kind of function more elegant, you can omit the second function entirely, and make `i` default to 0, like so:
```c++
int even_count(vector<int> v, int i = 0) {
  // same body as above
}
even_count({ 1, 2, 3 }) // don't need to pass in i
```
-->

### Why Recursion?

After seeing all these examples, there's one question you may be asking: why not just use a loop? The answer is that these are simple, linear examples. There are *many* places where recursion is genuinely useful, and understanding these simple cases will help you understand the more practical ones.

### Practice
- Write a simple recursive function `int sum_squares(int n)` that returns the sum of the first n squares. For example, `sum_squares(3)` should return 1<sup>2</sup> + 2<sup>2</sup> + 3<sup>2</sup> = 14
- Write a recursive function that returns the first odd number in a vector.
- Need more

<!--
- Write a recursive function `int vector_product(vector<int> v)` that returns the product of every value in the vector.
-->



<!--
```
int fibonacci() {
  
  if (n == 0)
    return 0;
  if (n == 1)
    return 1;
  
  return fibonacci(n - 1) + fibonacci(n - 2);
  
}
```
-->

<!--
> Advanced Tip: Many exponentially recursive functions can be improved with dynamic programming.
-->

<!--
*Tail recursion* occurs when the last thing the function does is a single recursive call. They are generally easy to write non-recursively. `countdown` is an example of tail recursion, while `countup` is not.
-->