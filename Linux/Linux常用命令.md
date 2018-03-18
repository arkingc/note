>参考：[linw7的github](https://github.com/linw7/Skill-Tree/blob/master/Linux%E5%B7%A5%E5%85%B7.md)

<br>

<!-- GFM-TOC -->
* [开发及调试](#开发及调试)
    * [编辑器：vim](#编辑器vim)
    * [编译器：gcc和g++](#编译器gcc和g++)
    * [调试工具：gdb](#调试工具gdb)
    * [查看依赖库：ldd](#查看依赖库ldd)
    * [二进制文件分析：objdump](#二进制文件分析objdump)
    * [ELF文件格式分析：readelf](#elf文件格式分析readelf)
    * [跟踪进程中系统调用：strace](#跟踪进程中系统调用strace)
    * [跟踪进程栈：pstack](#跟踪进程栈pstack)
    * [进程内存映射：pmap](#进程内存映射pmap)
* [文件处理](#文件处理)
    * [文件查找：find](#文件查找find)
    * [文本查找：grep](#文本查找grep)
    * [排序：sort](#排序sort)
    * [转换：tr](#转换tr)
    * [切分文本：cut](#切分文本cut)
    * [拼接文本：paste](#拼接文本paste)
    * [统计：wc](#统计wc)
    * [文本替换：sed](#文本替换sed)
    * [数据流处理：awk](#数据流处理awk)
* [性能分析](#性能分析)
    * [进程查询：ps](#进程查询ps)
    * [进程监控：top](#进程监控top)
    * [打开文件查询：lsof](#打开文件查询lsof)
    * [内存使用量：free](#内存使用量free)
    * [监控性能指标：sar](#监控性能指标sar)
* [网络工具](#网络工具)
    * [网卡配置：ifconfig](#网卡配置ifconfig)
    * [查看当前网络连接：netstat](#查看当前网络连接netstat)
    * [查看路由表：route](#查看路由表route)
    * [检查网络连通性：ping](#检查网络连通性ping)
    * [转发路径：traceroute](#转发路径traceroute)
    * [网络Debug分析：nc](#网络debug分析nc)
    * [命令行抓包：tcpdump](#命令行抓包tcpdump)
    * [域名解析工具：dig](#域名解析工具dig)
    * [网络请求：curl](#网络请求curl)
* [其他](#其他)
    * [终止进程：kill](#终止进程kill)
    * [修改文件权限：chmod](#修改文件权限chmod)
    * [创建链接：ln](#创建链接ln)
    * [显示文件尾：tail](#显示文件尾tail)
    * [版本控制：git](#版本控制git)
    * [设置别名：alias](#设置别名alias)
<!-- GFM-TOC -->

<br>

# 开发及调试

## 编辑器：vim

## 编译器：gcc和g++

## 调试工具：gdb

## 查看依赖库：ldd

## 二进制文件分析：objdump

## ELF文件格式分析：readelf

## 跟踪进程中系统调用：strace

## 跟踪进程栈：pstack

## 进程内存映射：pmap

# 文件处理

## 文件查找：find

#### (显示行号)查看文件：nl

行号计算不包括空行

#### 使用方法

```bash
find [查找目录] [查找条件]

查找目录：
    .：在当前目录及子目录下查找（默认）
    A：在目录A及A的子目录下查找
查找条件：
    -name：根据文件名查找
    -regex：使用正则表达式匹配
    -type：按类型查找（f:文件，d:目录，l:链接...）
    -atime：按访问时间查找（n:n天前的一天内，+n:n天前(不含n天本身)，-n:n天内(不含n天)）
    -mtime：按修改时间查找（n:n天前的一天内，+n:n天前(不含n天本身)，-n:n天内(不含n天)）
    -size：按大小查找（单位k，+nk:"比nk更大"，-nk:"比nk更小"）
    -perm：按权限查找（644：权限等于644的文件）
    -user/-nouser：用户名等于/用户名不等于
    -group/-nogroup：组名等于/组名不等于
```

#### 实例

```bash
#1.在当前目录及子目录下查找后缀为cpp的文件
find . -name *.cpp

#2.使用正则表达式查找
find -regex ".*.cpp$"
```

## 文本查找：grep

#### 使用方法

```bash
输出 | grep [选项] 模式串
grep [选项] 模式串 文件

选项
    -e：使用多个模式串
    -i：忽略大小写
    -n：打印行号
    -c：统计次数（一行算一次）
```

#### 实例

```bash
#1.在test.c中搜索包含字符串”printf“或”count“的行
grep -e "printf" -e "count" test.c
```

## 排序：sort

#### 使用方法

```bash
输出 | sort [选项]
sort [选项] 文件

选项
    -d：按字典序排序（默认）
    -n：按数字排序
    -k："-k n"表示按各行第n列进行排序
    -r：反序
```

## 转换：tr

#### 使用方法

```bash
#set1、set2为字符集，可以是单个字符，也可以是字符串
输出 | tr [选项] set1 set2

选项：
    -d：删除字符
    -s：字符压缩
```

#### 实例

```bash
#1.删除字符':'
cat /etc/passwd | tr -d ':'

#2.将小写字母替换成大写字母
last | tr '[a-z]'  'A-Z'

#3.将'a'、'b'、'c'替换成'z'
#cat test | tr “abc” 'z'

#4.将连续的'a'压缩成'b'（单个或连续出现的多个‘a’会压缩成一个‘b’）
cat test | tr -s 'a' 'b'
```

## 切分文本：cut

#### 使用方法

```bash
输出 | cut [选项]
cut [选项] 文件

选项：
    -d：分隔符（-d ':' 以’:‘为分隔符）
    -f：选择域（-f 1,2 输出分隔后第1列和第2列）
    -c：字符范围（-c n-m 输出第n到m个字符。如果没有m，输出到末尾）
```

#### 实例

```bash
#1.按’:‘分隔$PATH，输出第3个和第5个
echo $PATH | cut -d ':' -f 3,5

#2.输出export运行结果每行的第12-20个字符
export | cut -c 12-20
```

## 拼接文本：paste

#### 使用方法

```bash
paste [选项] file1 file2

选项：
    -d：指定拼接时使用的分隔符（默认使用tab作为分隔符）
```

## 统计：wc

#### 使用方法

```bash
wc [选项] 文件
输出 | wc [选项]

选项：
    -c：统计字符数
    -w：统计单词数
    -l：统计行数
```

## 文本替换：sed

## 数据流处理：awk

# 性能分析

## 进程查询：ps

##进程监控：top

## 打开文件查询：lsof

## 内存使用量：free

## 监控性能指标：sar

# 网络工具

## 网卡配置：ifconfig

## 查看当前网络连接：netstat

## 查看路由表：route

## 检查网络连通性：ping

## 转发路径：traceroute

## 网络Debug分析：nc

## 命令行抓包：tcpdump

## 域名解析工具：dig

## 网络请求：curl

# 其他

## 终止进程：kill

## 修改文件权限：chmod

## 创建链接：ln

## 显示文件尾：tail

## 版本控制：git

## 设置别名：alias
