object Solution {
    def f(arr:List[Int]):List[Int] = {
        return arr.zipWithIndex.filter(x => (x._2 % 2 == 1)).unzip._1
    }

    def main(args: Array[String]) {
        var ret = f(List.range(1,10))
        for (x <- ret) {
            println(x)
        }
    }
}
