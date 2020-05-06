object Solution {
    def f(arr:List[Int]):List[Int] = arr.reverse

    def main(args: Array[String]) {
        var ret = f(List.range(1,10))
        for (x <- ret) {
            println(x)
        }
    }
}
