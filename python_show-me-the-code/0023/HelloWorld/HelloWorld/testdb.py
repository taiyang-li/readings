#!/usr/bin/env python
# coding: utf-8

from django.http import HttpResponse
from django.shortcuts import render
from TestModel.models import Test


# 数据库操作
def testdb(request):
    """
    test1 = Test(name='w3cschool.cn')
    test1.save()
    """
    test1 = Test.objects.get(id=1)
    test1.name = 'w3cschoolW3Cschool教程'
    test1.save()
    return HttpResponse("<p>数据修改成功！</p>")
