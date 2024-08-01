from cs50 import get_float

change = -1

while change < 0:
    change = 100 * (get_float("Change: "))

# print(change)
coins = 0


def get_change(change, coin):
    coins = 0
    while change >= coin:
        coins += (int)(change / coin)
        change = (int)(change % coin)
    return coins, change


for i in [25, 10, 5, 1]:
    new_coins, change = get_change(change, i)
    coins += new_coins

print(coins)
