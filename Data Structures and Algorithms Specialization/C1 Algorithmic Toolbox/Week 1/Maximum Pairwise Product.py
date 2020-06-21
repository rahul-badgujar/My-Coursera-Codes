def mproduct(arr):
    arr.sort(reverse=True)
    return arr[0] * arr[1]

n = int(input())
arr = [int(x) for x in input().split()]
print(mproduct(arr))