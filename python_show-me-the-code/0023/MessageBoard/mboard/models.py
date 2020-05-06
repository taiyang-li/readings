# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models

# Create your models here.

class Message(models.Model):
    name = models.CharField(max_length=200, verbose_name=u'用户名')
    email = models.EmailField(verbose_name=u'邮箱')
    address = models.CharField(max_length=200, verbose_name=u'地址')
    message = models.CharField(max_length=1000, verbose_name=u'留言') 

    class Meta:
        verbose_name = u'用户留言信息'
        verbose_name_plural = verbose_name

