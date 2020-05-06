object Solution {
    def f(arr:List[Int]):List[Int] = arr.map(math.abs(_))

    def main(args: Array[String]) {
        var ret = f(List(-1, -2, -3, -4))
        for (x <- ret) {
            println(x)
        }
    }
}
