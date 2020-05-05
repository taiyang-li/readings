《linux shell脚本攻略》笔记<br>
本项目为笔者在阅读《linux shell脚本攻略》过程中做的代码笔记，方便本人温故知新，也希望能够给linux shell的初学者带来一些帮助。  <br>

笔记按照命令分类，每个命令单独一个文件，方便大家快速查阅。<br>

1. 输出颜色字符 <br>

echo -e "\e[1:41m" 1表示背景色<br>

2.  echo 打印!需要注意 <br>

echo "hello, bash!"  会出错 <br>
需要改成 echo 'hello, bash!'<br>

3. printf可用于格式化输出 <br>

printf "format"  var1 var2 ...<br>

4.  echo <br>

echo -n  // 不添加换行符<br>
echo -e  // 使用转义序列  相当于 echo "XXXX"<br>
echo -e "\e[id1 XXXXXX"                 // <br>

echo 显示颜色   <br>
其中id用于设置字背景颜色<br>

5.  pgrep  <br>
pgrep 进程名  // 相当于ps -ef  <br>
cat /proc/$PID/environ // 查看进程运行过程中的环境变量<br>

6. (())<br>
c=$((a+b))  // 赋值方式1<br>
((c = a+b))  // 赋值方式2<br>

7. 重定向<br>
// 将标准输出定向到stdout.txt 将标准错误输出定向到stdout.txt <br>
sh mybash.sh 1>stdout.txt 2 > stdout.txt<br>

// 更简单的方案 注意&和>之间不能有空格 <br>
sh mybash.sh &> stdout.txt<br>

8. exec <br>
// 创建文件描述符<br>
exec 4 < log.txt<br>
exec 5 > log.txt<br>
exec 6 >> log.txt<br>

9. 哈希数组 <br>
// 声明<br>
declare -a map <br>

// 定义<br>
${map[key]}=value<br>

// 获取所有key<br>
${!map[@]}<br>
declare -a HTTP_RESPONSE=(<br>
        [200]="OK"<br>
        [400]="Bad Request"<br>
        [403]="Forbidden"<br>
        [404]="Not Found"<br>
        [405]="Method Not Allowed"<br>
        [500]="Internal Server Error"<br>
)<br>

10. date <br>
// 显示秒数<br>
date +%s <br>

// 将秒数转成字符串<br>
date  -d @秒数 <br>

11 tput <br>
// 设置光标位置<br>
tput cup 行号  列号<br>

// 保存光标位置<br>
tput sc <br>

// 回到保存的光标位置<br>
tput rc<br>

// 清除当前光标到行尾<br>
tput ed<br>

12. read <br>
// 设置不回显<br>
read -s<br>
// 设置超时时间 <br>
read -t <br>
// 设置读入字节数<br>
read -n 字节数<br>
// 设置提示<br>
read -p "please input passwd"<br>

13. cat <br>
// 删除多余的空行 <br>
cat -s file<br>

// 打印行号<br>
cat -n file <br>

// 打印出制表符<br>
cat -T file <br>

14. find <br>
// 打印<br>
find <path> -name XXX  -print <br>

// 执行命令 <br>
find  <path> -name XXX -exec rm -rf {} \;<br>

15. xargs <br>
// 常用用法<br>
cat file | xargs<br>

// 设定每行的字段数<br>
cat file | xargs -n 3 <br>

// 以null为换行符<br>
cat file | xargs -0<br>

// 代替命令中位置<br>
cat file | xargs -I{} rm -rf {}<br>

16. tr <br>
// 替换 <br>
tr  字符集1 字符集2 <br>

// 删除<br>
tr -d 字符集<br>

// 补集<br>
tr -d -c 要留下的字符集<br>

// 去除重复空格<br>
tr -s " "<br>

17. md5sum <br>
// 生成md5值<br>
md5sum file  > file.md5<br>

// 校验 <br>
md5sum -c file.md5<br>

18. sort <br>
// 按照字符串排序 <br>
cat file | sort <br>

//按照数字排序<br>
cat file | sort -n <br>

// 逆序排序<br>
cat file | sort -r<br>

// 按照某列排序 <br>
cat file | sort -k 列数 <br>

19. dd    生成文件  <br>
// 从/dev/zero生成文件 <br>
dd if=/dev/zero of=data.file bs=100k count=1 <br>

20. split  分割文件 <br>
split data.file -b 10k -a 3<br>

21. 字符串分割 <br>
// 获取文件后缀<br>
echo ${filename////*.}<br>

// 获取文件名<br>
echo ${filename%.*}<br>

22. 单词表<br>
cat /usr/share/dict/words<br>

23. 自动化交互式输入<br>
// 标准输入<br>
echo "XXX"  | sh interactive.sh<br>

// 文件输入<br>
sh interactive.sh < input.data<br>

// expect <br>
spawn  ./interactive.sh <br>
expect "XXXX"<br>
send "YYY\n"<br>

24. comm<br>
// 求差集a-b<br>
comm a.txt b.txt -1<br>

// 求a+b并集<br>
comm a.txt b.txt <br>

// 求ab交集<br>
comm a.txt b.txt -1 -2 <br>

25. 将文件设置为不可修改<br>
chattr +i file<br>
去除不可修改属性<br>
chattr -i file <br>

26. 寻找软连接<br>
ll -rt | grep -P "^l" | awk '{print $8}'<br>
find . -type l<br>

27. diff<br>
diff -u 1.txt 2.txt <br>
diff -u 1.txt 2.txt > 12.patch <br>

28. patch<br>
patch -p1 1.txt < 12.patch<br>
 <br>
29. pushd、popd、dirs<br>
// 常规用法<br>
pushd  directory<br>
popd <br>

// 指定目录<br>
dirs<br>
pushd +N<br>
popd +N<br>

30. grep <br>
// 显示颜色<br>
grep --color=auto <br>

// 统计匹配行数<br>
grep -c <br>

// 显示匹配行号<br>
grep -n <br>

// 显示匹配字符偏移量<br>
grep -o -b<br>

// 显示匹配文件列表<br>
grep -l  1.txt 2.txt<br>

// 使用文件匹配<br>
grep -f pattern.txt  file.txt<br>

// 静默模式<br>
grep -q <br>

// 定位代码<br>
grep -R -n <br>

// 忽略大小写<br>
grep -i <br>

// 匹配多个样式<br>
grep -e pattern1 -e pattern2<br>

// 显示匹配行之前N行<br>
grep -A <br>

// 显示匹配行之后N行<br>
grep -B <br>

// 显示匹配行之前之后N行<br>
grep -C <br>

30. sed <br>
// sed "s///" 替换<br>
echo  "hello wolrd" | sed "s/hello/goodbye/"<br>

// sed -i 替换文件内容<br>
sed -i 's/hello/goodbye/' 1.txt<br>

// sed 's///g' 替换所有匹配内容<br>
echo "thisthisthisthis" | sed 's/this/THIS/g'<br>

// sed 's///ng' 从第n处匹配开始替换<br>
echo "thisthisthisthis" | sed 's/this/THIS/2g'<br>

// sed '//d' 删除匹配行<br>
cat diff.sh | sed '/^$/d' <br>

// 匹配字符串标记<br>
echo this is an example | sed 's/\w\+/[&]/g'<br>

// 捕捉字符串<br>
echo "this is a digit 7 in a numbger" | sed 's/digit \([0-9]\)/\1/'<br>

31. paste<br>
// 按列合并文件<br>
paste file1 file2<br>
paste file1 file2 -d  ","<br>

32. rev<br>
// 字符串逆序<br>
echo "1234" | rev<br>

33. tac<br>
// 行逆序<br>
seq 1 10 | tac<br>

34. 设置命令行编辑模式<br>
set -o vi<br>
