from cs50 import get_int
height = 0
stop = False
while (not stop):
    height = get_int("Height: ")
    if height > 0 and height < 9:
        stop = True


def print_hash(i):
    for k in range(i, 0, -1):
        print("#", end='')


for i in range(1, height+1):
    for j in range(height-i, 0, -1):
        print(" ", end='')
    print_hash(i)
    print("  ", end='')
    print_hash(i)
    print()

# print_hash(height)
