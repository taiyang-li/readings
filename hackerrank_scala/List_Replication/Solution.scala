object Solution {
    def f(num:Int,arr:List[Int]):List[Int] = {
        var ret : List[Int] = List()
        for (x <- arr) {
            for (y <- 1 to num) {
                ret = ret :+ x
            }
        }
        return ret
    }

    def main(args: Array[String]) {
        var ret = f(3, List(1,2,3,4))
        for (x <- ret) {
            println(x)
        }
    }
}
