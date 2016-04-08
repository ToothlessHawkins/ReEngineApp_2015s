Justin John
Lauren-Alexandra Stapleford

I was having some trouble where the program was throwing an error on the Render() calls, but I don't know if that will be an issue for you.

We have all the getters and setters set up and working. We orignally were overhtinking it and made it more complicated than it should have been, but it's good now.
The Move methods work perfectly, and are bound properly: W = forward, S = back, A = left, D = right, Q = up, E = down.

We tried to get the orientation methods to work, but we couldn't figure it out. Quaternions are my weakpoint. Regardless, all the controls are bound and in place.
Holding right mouse will lock the mouse and would normally change pitch and yaw, but like I said, those arent working.
We chose to bind changeRoll to the R and T keys, rolling left and right, respectively.