"""simpleToDo URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/1.11/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  url(r'^$', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  url(r'^$', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.conf.urls import url, include
    2. Add a URL to urlpatterns:  url(r'^blog/', include('blog.urls'))
"""
from django.conf.urls import url, include
from django.contrib import admin
from views import todolist, addTodo, todofinish, todoback, updatetodo, tododelete

urlpatterns = [
    url(r'^$', todolist, name='todo'),
    url(r'^addtodo/', addTodo, name='add'),
    url(r'^todofinish/(?P<id>\d+)/$', todofinish, name='finish'),
    url(r'^todobackout/(?P<id>\d+)/$', todoback,  name='backout'),
    url(r'^updatetodo/(?P<id>\d+)/$', updatetodo, name='update'),
    url(r'^tododelete/(?P<id>\d+)/$', tododelete, name='delete'),
]
