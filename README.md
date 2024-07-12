# Pi-Estimation-Parallel-Calculator

This reposity mainly focused on the estimation of `Pi` using parallel libraries such as `POSIX thread`, `OpenMP`, `MPI` and the `Monte-Carlo` technique.

Suppose we throw darts at a square target whose sides are 2 meters long, centered at
target to be the origin point (0, 0) of the coordinate system. Also assume that in this
square target is inscribed a circle. The radius of the circle is 1 meter and its area is p
square meters. If the points where the arrows end are evenly distributed (and the arrows
always hit the square target), then the number of arrows hitting the inside of the circle will
must, approximately, satisfy the equation:
$$\frac{number\_of\_darts\_inside\_the\_circle}{number\_of\_throws}=\frac{\pi}{4}$$

since the ratio of the area of ​​the circle to the area of ​​the square is `π/4`.

We can use this equation to calculate an estimate for the value of `π` through a
random number generator:

```
arrows_in_circle = 0;
for (throw = 0; throw < count_of_throws; throw++) {
    x = random double between −1 and 1;
    y = random double between −1 and 1;
    square_of_the_distance = x * x + y * y;
    if (square*distance <= 1)
        arrows_in_circle++;
    }
    estimate_pi = 4 * arrows_in_circle / ((double) count_of_throws);
```

This method is called "Monte Carlo" because it uses random variables (the throws of the darts).

We developed and compared 4 versions of the above pseudo-code:

1. Serial
2. Posix Thread
3. OpenMP
4. MPI
