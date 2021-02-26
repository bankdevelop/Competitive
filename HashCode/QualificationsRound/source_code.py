# A – An example 2,000 points
# B – By the ocean 4,562,858 points
# C – Checkmate 1,195,330 points
# D – Daily commute 969,685 points
# E – Etoile 661,797 points
# F – Forever jammed 455,737 points
# Total score 7,847,407 points

#input
f = open('in/f.txt')
streets = []
cars = []

D, I, S, V, F = [int(i) for i in f.readline().strip().split()]
for x in range(S):
    tmp = f.readline().strip().split()
    tmp[0]=int(tmp[0])
    tmp[1]=int(tmp[1])
    tmp[3]=int(tmp[3])
    streets.append(tmp)
for x in range(V):
    car = f.readline().strip().split()
    car[0] = int(car[0])
    cars.append(car)
f.close()

#solve problem
import random

print(I)
for x in range(I):
    print(x)
    tmp = []
    for y in streets:
        if y[1] == x:
            tmp.append([y[2], random.randint(1,2)])
    print(len(tmp))
    for k in tmp:
        print(k[0], k[1])