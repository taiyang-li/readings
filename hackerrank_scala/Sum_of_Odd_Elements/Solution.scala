object Solution {
    def f(arr:List[Int]):Int = {
        var sum = 0
        for (x <- arr) {
            if (x % 2 != 0)
                sum += x
        }
        return sum
    }


    def main(args: Array[String]) {
        var ret = f(List(11, 25, 18, -1, 26, -20, -19, 23, -24, -8))
        println(ret)
    }
}
