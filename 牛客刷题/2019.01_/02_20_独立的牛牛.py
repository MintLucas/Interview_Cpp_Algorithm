import sys

class Solution:
    def live(self, x, d, f, p):
        if d < x:
            return 0
        if d <= f*x:
            return int(d/x)
        left = d - f*x
        return int(f + left/(p+x))



if __name__ == '__main__':
    s = Solution()
    #租金x,钱包d,水果f个,单价p元
    for line in sys.stdin:
        a = line.split()
    #case通过率百分之40
    for line in sys.stdin:
        a = line.split()
        result = s.live(int(a[0]), int(a[1], int(a[2], int(a[3])
        print(result)

    #result = s.live(2, 30, 5, 2)
    #print(result)