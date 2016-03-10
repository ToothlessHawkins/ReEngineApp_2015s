This project went kinda stragely.

I know there must be a more elegant way to do it than the million if statements I used, but I couldn't come up with one.

I was also having issues with the Render() method. I went into more detail in the comments in the display method, but long story short,
the waypoints that are supposed to be red spheres, don't show up. Well, they might. Right now, the display method has a crucial line commented out, and there's a small chance that
if you uncomment it, the render method will actually work. My reasoning is that you might be in the correct version of the engine, and if that's really the issue then that should solve it, right?

Also the model moves, but it doesn't restart the cycle after reaching waypoint 1 again. I tried to make it so that it would, which is why I ended up with a million MapValue's.

I'm going to try to commit this now, and from my little experience with source control, that means I'll have to sacrifice a goat and it still won't work. 