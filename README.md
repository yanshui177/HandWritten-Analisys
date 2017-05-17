# HWCV
手写体笔迹鉴别程序，包含几个不同的部分

首先，是C语言vs2013写的主程序，生成名为HWCV-exe.exe的可执行文件（无界面运行），
其次，是C语言VC6.0写成的服务程序，常驻内存，名为：serve.exe
最后，是一个测试程序，all-test.exe，测试所有的笔迹图像是否为同一个人写的，并输出鉴定日志到文件log.csv

注：这是个商业化应用的0.1版本，程序需要使用到的环境为：
  windows server 2008R2
  oracle client32
  opencv2.4.13
