# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models

# Create your models here.
from django.db import models
from django.contrib.auth.models import User

class Todo(models.Model):
    user = models.ForeignKey(User)
    todo = models.CharField(max_length=50)
    flag = models.CharField(max_length=2, default='1')
    priority = models.CharField(max_length=2, default='0')
    pubtime = models.DateTimeField(auto_now_add=True)

    def __unicode__(self):
        return u'%d %s %s' % (self.id, self.todo, self.flag)

    class Meta:
        ordering = ['priority', 'pubtime']
