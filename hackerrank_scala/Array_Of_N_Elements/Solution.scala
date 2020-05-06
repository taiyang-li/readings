object Solution{

    def f(num:Int) : List[Int] = {
        val list = List.fill(num)(1)
        return list
    } 

    def main(args: Array[String]) {
        var ret = f(readInt)
        for (x <- ret) {
            println(x)
        }
    }
}
