# -*- coding: utf-8 -*-
# @Time    : 2018/11/15 下午 06:47
# @Author  : AlexJean
# demo for using Cpp Extension

import Cpp
if __name__ == '__main__':
    print("----- module Cpp ---- function list -----")
    items=dir(Cpp)
    for s in items:
        if s[0] != '_':
            print(s)
    print("-----------------------------------------------")
    Cpp.system("dir")
    print("-----------------------------------------------")
    Cpp.test()
    print("-----------------------------------------------")
    print("\n\nResult fac(5)=", Cpp.fac(5))

