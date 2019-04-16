# partition_merge

An simple implement of K partition merge sorting algorithm.

**BUILT WITH Bazel**

## 大致思路

算法使用了败者树来进行K分区归并排序，使得总的时间复杂度在O(nlogn)的前提下，占用的额外内存和比较次数尽可能少。

在Partition类的设计中，对外有get_next与add_number两个public的方法。这是为了使得数据块不管是存在内存里，还是硬盘里或者分布式存储当中，总是能够用这两个方法来获取下一个需要的数以及往分区里加入一个数（不必保证有序）。

该算法占用内存和比较次数都很优秀，主要的瓶颈在于获取下一个数以及写入一个数的速度。该速度取决于数据存放的位置，根据位置不同受访存速度，磁盘IO速度，网络带宽等的影响。当然实际使用中可以一次读入一个DataBlock在内存里缓存，攒够一个DataBlock再写入到硬盘或者分布式存储中，以此提高效率。

```
bool Partition::get_next(int &x);
void Partition::add_number(int x);
```

在test.cpp文件中对该算法进行了简单的测试。

