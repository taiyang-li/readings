object Solution {
    def f(delim:Int,arr:List[Int]):List[Int] = {
        return arr.filter(_  < delim)
    }

    def main(args: Array[String]) {
        var ret = f(3, List.range(1,10))
        for (x <- ret) {
            println(x)
        }
    }
}
