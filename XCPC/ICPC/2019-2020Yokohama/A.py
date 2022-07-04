from re import X


n = int(input())
x, t = 1, 0
while n > 0 :
    n -= x
    t += 1
    if n + 1 >= (x * 9 - 1) / 2 :
        x *= 3
    elif n + 1 < (x * 3 - 1) / 2 : 
        x /= 3
print(t)