###
 # @Date: 2023-02-07 18:56:50
 # @LastEditors: Juan Jiang
 # @LastEditTime: 2023-02-07 19:14:53
 # @FilePath: /dr-cu/benchmark/get18.sh
### 
mkdir ispd2018
cd ispd2018
wget http://www.ispd.cc/contests/18/ispd18_sample.tgz
wget http://www.ispd.cc/contests/18/ispd18_sample2.tgz
wget http://www.ispd.cc/contests/18/ispd18_sample3.tgz
wget http://www.ispd.cc/contests/18/ispd18_test1.tgz
wget http://www.ispd.cc/contests/18/ispd18_test2.tgz
wget http://www.ispd.cc/contests/18/ispd18_test3.tgz
wget http://www.ispd.cc/contests/18/ispd18_test4.tgz
wget http://www.ispd.cc/contests/18/ispd18_test5.tgz
wget http://www.ispd.cc/contests/18/ispd18_test6.tgz
wget http://www.ispd.cc/contests/18/ispd18_test7.tgz
wget http://www.ispd.cc/contests/18/ispd18_test8.tgz
wget http://www.ispd.cc/contests/18/ispd18_test9.tgz
wget http://www.ispd.cc/contests/18/ispd18_test10.tgz
mkdir ispd18_sample
mkdir ispd18_sample2
mkdir ispd18_sample3
mkdir ispd18_test1
mkdir ispd18_test2
mkdir ispd18_test3
mkdir ispd18_test4
mkdir ispd18_test5
mkdir ispd18_test6
mkdir ispd18_test7
mkdir ispd18_test8
mkdir ispd18_test9
mkdir ispd18_test10
tar zxvf ispd18_sample.tgz -C ispd18_sample
tar zxvf ispd18_sample2.tgz -C ispd18_sample2
tar zxvf ispd18_sample3.tgz -C ispd18_sample3
tar zxvf ispd18_test1.tgz -C ispd18_test1
tar zxvf ispd18_test2.tgz -C ispd18_test2
tar zxvf ispd18_test3.tgz -C ispd18_test3
tar zxvf ispd18_test4.tgz -C ispd18_test4
tar zxvf ispd18_test5.tgz -C ispd18_test5
tar zxvf ispd18_test6.tgz -C ispd18_test6
tar zxvf ispd18_test7.tgz -C ispd18_test7
tar zxvf ispd18_test8.tgz -C ispd18_test8
tar zxvf ispd18_test9.tgz -C ispd18_test9
tar zxvf ispd18_test10.tgz -C ispd18_test10

rm *.tgz