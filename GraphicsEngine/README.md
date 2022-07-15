# 3D Graphics Engine

---

## FOV (Field of View)

Aspect Ratio -> *height / width* -> (h/w) -> a<br>
Function for proper scaling according to FOV angle -> (1/tan(θ/2)) -> f <br>
[ x, y, z ] ->  [ (h/w)fx, fy, z ] <br>
<br>
Scaling *z* -> Z_FAR / (Z_FAR - Z_NEAR) -> p
Offsetting Z_NEAR -> -(Z_FAR * Z_NEAR) / (Z_FAR - Z_NEAR) -> p \* Z_NEAR
<br>
Increased depth makes objects appear smaller. \\
x' = x/z  <-> y' = y/z <br>

<br>

[ x, y, z ] -> [ (afx)/z , (fy)/z , zp - Z_NEAR\*p ] <br>
<br>
Matrix multiplication for the vector -> 
[ afx/z , fy/z , zp - Z_NEAR\*p] -> requires a fourth element
for matrix multiplication, a 1 which also introduces a fourth column.
<br>
-Z_NEAR \* p -> q

## Projection matrix

`[ x, y, z, 1 ]` \* [[   af   0   0   0   ]<br>
\tab\tab\tab		 [   0    f   0   0   ]<br>
\tab\tab\tab		 [   0    0   p   1   ]<br>
\tab\tab\tab		 [   0    0   q   0   ]]<br>
<br>
