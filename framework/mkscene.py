import random

R=random.Random(42)



print("camera      0 0 5    0 0 0       0 1 0  45")
print("light       0 10 5")
for i in range(1000):
    red=R.randrange(100)/100
    green = R.randrange(100)/100
    blue = R.randrange(100)/100
    alpha = 1
    refl = 0
    cx = R.randrange(-100,100)/10
    cy = R.randrange(-100,100)/10
    cz = -R.randrange(40,100)/10
    radius = R.randrange(1,10)/10
    print("sphere",red,green,blue,"   ",alpha,"   ",refl,"   ",cx,cy,cz,"   ",radius)
    
