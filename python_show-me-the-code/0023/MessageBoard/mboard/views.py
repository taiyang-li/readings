# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.shortcuts import render, redirect
from django.http import HttpResponse, HttpResponseRedirect
from django.template.context_processors import csrf
from django.views.decorators.csrf import csrf_protect
from models import Message

# Create your views here.

# @csrf_protect
def index(request):
    context ={}
    context.update(csrf(request))
    if request.method == 'POST':
        name = request.POST.get("name")
        email = request.POST.get("email")
        address = request.POST.get("address")
        message = request.POST.get("address")
        item = Message(name=name, email=email, address=address, message=message)
        item.save()

    message_list = Message.objects.all()
    context["message_list"] = message_list
    return render(request, 'home.html', context=context)

"""
# @csrf_protect
def create(request):
    return render(request, 'create.html')

# @csrf_protect
def save(request):
    ctx ={}
    ctx.update(csrf(request))

    if request.POST:
        name = request.POST.get("name")
        email = request.POST.get("email")
        address = request.POST.get("address")
        message = request.POST.get("address")
        item = Message(name=name, email=email, address=address, message=message)
        item.save()
    # return HttpResponseRedirect('/mboard/index/', ctx)
    return redirect('/mboard/index/')
    # return render(request, 'create.html', ctx)
"""

